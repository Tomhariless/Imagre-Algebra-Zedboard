#include "point_OP.h"

//Operations:
//1 for >
unsigned char op01(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	if (pixIn>value){
		pixOut = IMAGE_MAX_VAL-1;
	}
	return pixOut;
}
/*
unsigned char op11(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut=0;
	if (pixIn1>pixIn2){
		pixOut = IMAGE_MAX_VAL-1;
	}
	return pixOut;
}*/
//2 for <,
unsigned char op02(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	if (pixIn<value){
		pixOut = IMAGE_MAX_VAL-1;
	}
	return pixOut;
}
/*unsigned char op12(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut=0;
	if (pixIn1<pixIn2){
		pixOut = IMAGE_MAX_VAL-1;
	}
	return pixOut;
}*/
//3 for ==,
unsigned char op03(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	if (pixIn==value){
		pixOut = IMAGE_MAX_VAL-1;
	}
	return pixOut;
}
/*unsigned char op13(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut=0;
	if (pixIn1==pixIn2){
		pixOut = IMAGE_MAX_VAL-1;
	}
	return pixOut;
}*/
//4 for +,
unsigned char op04(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	temp = pixIn + value;
	if (temp>255){
		temp = 255;
	}
	pixOut = temp;
	return pixOut;
}
/*unsigned char op14(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp=0;
	temp = pixIn1 + pixIn2;
	if (temp>255){
		temp = 255;
	}
	pixOut = temp;
	return pixOut;
}*/
//5 for -,
unsigned char op05(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	temp = pixIn - value;
	if (temp<0){
		temp = 0;
	}
	pixOut = temp;
	return pixOut;
}
/*unsigned char op15(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp=0;
	temp = pixIn1 - pixIn2;
	if (temp<0){
		temp = 0;
	}
	pixOut = temp;
	return pixOut;
}*/
//6 for *,
unsigned char op06(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	temp = pixIn * value;
	if (temp>255){
		temp = 255;
	}
	if (temp<0){
		temp = 0;
	}
	pixOut = temp;
	return pixOut;
}
/*unsigned char op16(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp=0;
	temp = pixIn1 * pixIn2;
	if (temp>255){
		temp = 255;
	}
	pixOut = temp;
	return pixOut;
}*/
//7 for /,
unsigned char op07(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	temp = pixIn / value;
	if (temp>255){
		temp = 255;
	}
	if (temp<0){
		temp = 0;
	}
	pixOut = temp;
	return pixOut;
}
/*unsigned char op17(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp=0;
	temp = pixIn1 / pixIn2;
	if (temp>255){
		temp = 255;
	}
	if (temp<0){
		temp = 0;
	}
	pixOut = temp;
	return pixOut;
}*/
//8 for and,
unsigned char op08(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	int pix;
	pix = pixIn;
	temp = 255 * ((pix) && (value));
	pixOut = temp;
	return pixOut;
}
/*unsigned char op18(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp = 0;
	int pix1,pix2;
	pix1 = pixIn1;
	pix2 = pixIn2;
	temp = 255* (pixIn1&&pixIn2);
	pixOut = temp;
	return pixOut;
}*/
//9 for or,
unsigned char op09(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	int pix;
	pix = pixIn;
	temp = 255 * ((pix) || (value));
	pixOut = temp;
	return pixOut;
}
/*unsigned char op19(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp = 0;
	int pix1,pix2;
	pix1 = pixIn1;
	pix2 = pixIn2;
	temp = 255* (pixIn1||pixIn2);
	pixOut = temp;
	return pixOut;
}*/
//10 for not
unsigned char op010(ap_uint<IMAGE_BIT> pixIn,int value){
	unsigned char pixOut=0;
	int temp=0;
	int pix;
	pix = pixIn;
	temp = 255 * ((pix)!=(value));
	pixOut = temp;
	return pixOut;
}
/*unsigned char op110(ap_uint<IMAGE_BIT> pixIn1,ap_uint<IMAGE_BIT> pixIn2){
	unsigned char pixOut = 0;
	int temp = 0;
	int pix1,pix2;
	pix1 = pixIn1;
	pix2 = pixIn2;
	temp = 255* (pixIn1!=pixIn2);
	pixOut = temp;
	return pixOut;
}*/
