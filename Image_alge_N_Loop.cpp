#include "core.h"

void Image_algebra_N_Loop(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &outStream,int op1,char kernel[KERNEL_DIM*KERNEL_DIM],int op2,int op3,int op3Val,unsigned int loops, unsigned int K_rotate, int Neighbour_TDEST){
#pragma HLS INTERFACE s_axilite port=Neighbour_TDEST bundle=OP_BUS name=N_TDEST
#pragma HLS INTERFACE s_axilite port=K_rotate bundle=KERNEL_BUS name=KERNEL_ROT
#pragma HLS INTERFACE s_axilite port=loops bundle=OP_BUS name=loops
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
	int op2_ValOut = 0;
	unsigned int lable_counter[1] = {0};
	ap_uint<IMAGE_BIT> valOutput;
	int newWindow[KERNEL_DIM][KERNEL_DIM];
	int Window[KERNEL_DIM][KERNEL_DIM];
	ap_uint<IMAGE_BIT> pixelIn;
	uint_side_channel dataOutSideChannel;
	uint_side_channel currentPixelSideChannel;
	unsigned int op3CurrentVal;
	int Debug_point = 0;
	for (int idxPixel=0;idxPixel<(IMAGE_I*IMAGE_J);idxPixel++){
#pragma HLS PIPELINE
		if(idxPixel==2297){
			Debug_point = 1;
		}
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
				Window[idxWinRow][idxWinCol] = val;
			}
		}
		if ( (idxRow>=KERNEL_DIM-1)&&(idxCol>=KERNEL_DIM-1) ){
			op2_ValOut = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i=0;i<loops;i++){
				if (op1==1){
					op11(newWindow,kernel,i,K_rotate);
				}
				if (op1==2){
					op12(newWindow,kernel,i,K_rotate);
				}
				if (op1==3){
					op13(newWindow,kernel,i,K_rotate);
				}
				if (op1==4){
					op14(newWindow,kernel,i,K_rotate);
				}
				if (op1==6){
					op16(newWindow,kernel,lable_counter);
				}
				//operation 2:
				//op2: 0: nothing, 1: sum, 2:min, 3:max 4: sum abs
				if (op2==0){
					op2_ValOut = op20(newWindow);
				}
				if (op2==1){
					op2_ValOut += op21(newWindow);
					for (int i=0;i<KERNEL_DIM;i++){
						for (int j=0;j<KERNEL_DIM;j++){
							newWindow[i][j] = Window[i][j];
						}
					}
				}
				if (op2==2){
					op2_ValOut += op22(newWindow);
					for (int i=0;i<KERNEL_DIM;i++){
						for (int j=0;j<KERNEL_DIM;j++){
							newWindow[i][j] = Window[i][j];
						}
					}
				}
				if (op2==3){
					op2_ValOut += op23(newWindow);
					for (int i=0;i<KERNEL_DIM;i++){
						for (int j=0;j<KERNEL_DIM;j++){
							newWindow[i][j] = Window[i][j];
						}
					}
				}
				if (op2==4){
					op2_ValOut += op24(newWindow);
					for (int i=0;i<KERNEL_DIM;i++){
						for (int j=0;j<KERNEL_DIM;j++){
							newWindow[i][j] = Window[i][j];
						}
					}
				}
				if (op2_ValOut>=255){
					valOutput = 255;
				}
				else{
					valOutput = op2_ValOut;
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
