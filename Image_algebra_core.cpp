#include "Image_algebra_core.h"

void Image_algebraDMA(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &outStream,int op1,char kernel[KERNEL_DIM*KERNEL_DIM],int op2,int op3,int op3Val,int Neighbour_TDEST_2){
#pragma HLS INTERFACE s_axilite port=Neighbour_TDEST_2 bundle=OP_BUS name=N_TDEST
#pragma HLS INTERFACE s_axilite port=kernel bundle=KERNEL_BUS name=KERNEL_BUS
#pragma HLS INTERFACE s_axilite port=op3Val bundle=OP_BUS name=OP3_Val
#pragma HLS INTERFACE s_axilite port=op3 bundle=OP_BUS name=OP3
#pragma HLS INTERFACE s_axilite port=op2 bundle=OP_BUS name=OP2
#pragma HLS INTERFACE s_axilite port=op1 bundle=OP_BUS name=OP1
#pragma HLS INTERFACE axis register both port=outStream
#pragma HLS INTERFACE axis register both port=inStream
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS name=CRTL_BUS
//define the window and the line buffer
	hls::LineBuffer<KERNEL_DIM,IMAGE_J,unsigned char> linebuff;
	//hls::Window<KERNEL_DIM,KERNEL_DIM,int> window;
	int idxCol = 0;
	int idxRow = 0;
	int pixConvolved = 0;
	int waitTicks = (IMAGE_J*(KERNEL_DIM-1)+KERNEL_DIM)/2;
	int countWait = 0;
	int sentPixels = 0;
	ap_uint<IMAGE_BIT> valOutput;
	int newWindow[KERNEL_DIM][KERNEL_DIM];
	ap_uint<IMAGE_BIT> pixelIn;
	uint_side_channel dataOutSideChannel;
	uint_side_channel currentPixelSideChannel;
	unsigned int op3CurrentVal;

	for (int idxPixel=0;idxPixel<(IMAGE_I*IMAGE_J);idxPixel++){
#pragma HLS PIPELINE
		currentPixelSideChannel = inStream.read();
		pixelIn = currentPixelSideChannel.data;
		//put data into the line buffer
		linebuff.shift_up(idxCol);
		linebuff.insert_top(pixelIn,idxCol);

		for (int idxWinRow=0;idxWinRow<KERNEL_DIM;idxWinRow++){
			for (int idxWinCol=0;idxWinCol<KERNEL_DIM;idxWinCol++){
				ap_uint<IMAGE_BIT> val = linebuff.getval(idxWinRow,idxWinCol+pixConvolved);
				//window.insert(val,idxWinRow,idxWinCol);
				newWindow[idxWinRow][idxWinCol] = val;
			}
		}
		if ( (idxRow>=KERNEL_DIM-1)&&(idxCol>=KERNEL_DIM-1) ){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (op1==1){
				op11(newWindow,kernel);
			}
			if (op1==2){
				op12(newWindow,kernel);
			}
			if (op1==3){
				op13(newWindow,kernel);
			}
			if (op1==4){
				op14(newWindow,kernel);
			}
			//operation 2:
			//op2: 0: nothing, 1: sum, 2:min, 3:max 4: sum abs
			if (op2==0){
			}
			if (op2==1){
				valOutput = op21(newWindow);
			}
			if (op2==2){
				valOutput = op22(newWindow);
			}
			if (op2==3){
				valOutput = op23(newWindow);
			}
			if (op2==4){
				valOutput = op24(newWindow);
			}
			//operation 3:
			//op3: 0: nothing, 1: thresholding 2:count pixels equal 3: count pixels above 4: count pixels less
			if (op3==0){
			}
			if (op3==1){
				valOutput = op31(valOutput,op3Val);
			}
			if (op3==2){
				op3CurrentVal = op32(valOutput,op3Val,op3CurrentVal);
			}
			if (op3==3){
				op3CurrentVal = op33(valOutput,op3Val,op3CurrentVal);
			}
			if (op3==4){
				op3CurrentVal = op34(valOutput,op3Val,op3CurrentVal);
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			pixConvolved++;
		}
		if (idxCol<IMAGE_J-1){
			idxCol++;
		}
		else{
			//new line
			idxCol = 0;
			idxRow++;
			pixConvolved = 0;
		}
		countWait++;
		if (countWait>waitTicks){
			dataOutSideChannel.data = valOutput;
			dataOutSideChannel.keep = currentPixelSideChannel.keep;
			dataOutSideChannel.strb = currentPixelSideChannel.strb;
			dataOutSideChannel.user = currentPixelSideChannel.user;
			dataOutSideChannel.last = 0;
			dataOutSideChannel.id = currentPixelSideChannel.id;
			dataOutSideChannel.dest = currentPixelSideChannel.dest;
			// Send to the stream (Block if the FIFO receiver is full)
			outStream.write(dataOutSideChannel);
			sentPixels++;
		}
	}
	for (countWait = 0; countWait < waitTicks; countWait++)
	{
		dataOutSideChannel.data = IMAGE_BORDER;
		dataOutSideChannel.keep = currentPixelSideChannel.keep;
		dataOutSideChannel.strb = currentPixelSideChannel.strb;
		dataOutSideChannel.user = currentPixelSideChannel.user;
		// Send last on the last item
		if (countWait < waitTicks - 1)
			dataOutSideChannel.last = 0;
		else
			dataOutSideChannel.last = 1;
		dataOutSideChannel.id = currentPixelSideChannel.id;
		dataOutSideChannel.dest = currentPixelSideChannel.dest;
		// Send to the stream (Block if the FIFO receiver is full)
		outStream.write(dataOutSideChannel);
	}
}
