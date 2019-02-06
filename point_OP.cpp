#include "point_OP.h"

void Point_OP(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &inStream2,hls::stream<uint_side_channel> &outStream,int op,int value,bool ImAmount,int Point_TDEST){
#pragma HLS INTERFACE s_axilite port=Point_TDEST bundle=CTRL_BUS name=P_TDEST
#pragma HLS INTERFACE s_axilite port=ImAmount bundle=CTRL_BUS name=IMAMOUNT
#pragma HLS INTERFACE axis register both port=inStream2
#pragma HLS INTERFACE s_axilite port=value bundle=CTRL_BUS name=VAL
#pragma HLS INTERFACE s_axilite port=op bundle=CTRL_BUS name=OP
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS name=CTRL
#pragma HLS INTERFACE axis register both port=outStream
#pragma HLS INTERFACE axis register both port=inStream
	int idxCol = 0;
	int idxRow = 0;
	int pixRead = 0;
	ap_uint<IMAGE_BIT> valOutput;
	ap_uint<IMAGE_BIT> pixelIn1;
	ap_uint<IMAGE_BIT> pixelIn2;

	uint_side_channel dataOutSideChannel;
	uint_side_channel currentPixelSideChannel1;
	uint_side_channel currentPixelSideChannel2;
	if(ImAmount==0){
		for (int idxPixel=0;idxPixel<(IMAGE_I*IMAGE_J);idxPixel++){
	#pragma HLS PIPELINE
			currentPixelSideChannel1 = inStream.read();
			pixelIn1 = currentPixelSideChannel1.data;
			if (op==0){valOutput=op01(pixelIn1,value);}
			if (op==1){valOutput=op02(pixelIn1,value);}
			if (op==2){valOutput=op03(pixelIn1,value);}
			if (op==3){valOutput=op04(pixelIn1,value);}
			if (op==4){valOutput=op05(pixelIn1,value);}
			if (op==5){valOutput=op06(pixelIn1,value);}
			if (op==6){valOutput=op07(pixelIn1,value);}
			if (op==7){valOutput=op08(pixelIn1,value);}
			dataOutSideChannel.data = valOutput;
			dataOutSideChannel.keep = currentPixelSideChannel1.keep;
			dataOutSideChannel.strb = currentPixelSideChannel1.strb;
			dataOutSideChannel.user = currentPixelSideChannel1.user;
			dataOutSideChannel.last = currentPixelSideChannel1.last;
			dataOutSideChannel.id = currentPixelSideChannel1.id;
			dataOutSideChannel.dest = Point_TDEST;
			outStream.write(dataOutSideChannel);
		}
	}
	if(ImAmount==1){
		for (int idxPixel=0;idxPixel<(IMAGE_I*IMAGE_J);idxPixel++){
#pragma HLS PIPELINE
			currentPixelSideChannel1 = inStream.read();
			currentPixelSideChannel2 = inStream2.read();
			pixelIn1 = currentPixelSideChannel1.data;
			pixelIn2 = currentPixelSideChannel2.data;
			value = pixelIn2;
			if (op==0){valOutput=op01(pixelIn1,value);}
			if (op==1){valOutput=op02(pixelIn1,value);}
			if (op==2){valOutput=op03(pixelIn1,value);}
			if (op==3){valOutput=op04(pixelIn1,value);}
			if (op==4){valOutput=op05(pixelIn1,value);}
			if (op==5){valOutput=op06(pixelIn1,value);}
			if (op==6){valOutput=op07(pixelIn1,value);}
			if (op==7){valOutput=op08(pixelIn1,value);}
			if (op==8){valOutput=op09(pixelIn1,value);}
			if (op==9){valOutput=op010(pixelIn1,value);}
			dataOutSideChannel.data = valOutput;
			dataOutSideChannel.keep = currentPixelSideChannel1.keep;
			dataOutSideChannel.strb = currentPixelSideChannel1.strb;
			dataOutSideChannel.user = currentPixelSideChannel1.user;
			dataOutSideChannel.last = currentPixelSideChannel1.last;
			dataOutSideChannel.id = currentPixelSideChannel1.id;
			dataOutSideChannel.dest = Point_TDEST;
			outStream.write(dataOutSideChannel);
		}
	}
}
