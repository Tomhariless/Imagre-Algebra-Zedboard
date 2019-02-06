#include "Global_OP.h"

void Global_OP(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &outStream,int op,bool mode,int Result[256],int Global_TDEST){
#pragma HLS INTERFACE s_axilite port=Global_TDEST bundle=OP_BUS name=G_TDEST
#pragma HLS INTERFACE bram port=Result
#pragma HLS INTERFACE s_axilite port=op bundle=OP_BUS name=OP_CTRL
#pragma HLS INTERFACE s_axilite port=mode bundle=OP_BUS name=MODE_CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS name=IP_CTRL
#pragma HLS INTERFACE axis register both port=outStream
#pragma HLS INTERFACE axis register both port=inStream
	ap_uint<IMAGE_BIT> valOutput;
	ap_uint<IMAGE_BIT> pixelIn;
	uint_side_channel dataOutSideChannel;
	uint_side_channel currentPixelSideChannel;
	int max=0;
	int min=255;
	int global_total=0;
	double average=0;
	for (int idxResult=0;idxResult<256;idxResult++){
		Result[idxResult] = 0;
	}
	for (int idxPixel=0;idxPixel<(IMAGE_I*IMAGE_J);idxPixel++){
#pragma HLS PIPELINE
		currentPixelSideChannel = inStream.read();
		pixelIn = currentPixelSideChannel.data;
		//put the operations here
		//op0 histogram, op1 global max op2 global min, op3 global total op4 global sum/x*y
		if (op==0){
			Result[pixelIn] = Result[pixelIn] + 1;
		}
		if (op==1){
			if (pixelIn>max){
				max = pixelIn;
			}
		}
		if (op==2){
			if (pixelIn<min){
				min = pixelIn;
			}
		}
		if (op==3){
			global_total = global_total + pixelIn;
		}
		if (op==4){
			global_total = global_total + pixelIn;
		}
		valOutput = pixelIn;
		dataOutSideChannel.data = valOutput;
		dataOutSideChannel.keep = currentPixelSideChannel.keep;
		dataOutSideChannel.strb = currentPixelSideChannel.strb;
		dataOutSideChannel.user = currentPixelSideChannel.user;
		dataOutSideChannel.last = currentPixelSideChannel.last;
		dataOutSideChannel.id = currentPixelSideChannel.id;
		dataOutSideChannel.dest = Global_TDEST;
		outStream.write(dataOutSideChannel);
	}
	if (op==1){
		Result[0] = max;
	}
	if (op==2){
		Result[0] = min;
	}
	if (op==3){
		Result[0] = global_total;
	}
	if (op==4){
		Result[0] = (double)(global_total/(IMAGE_I*IMAGE_J));
	}
}
