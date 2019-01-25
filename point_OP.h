#include "hls_video.h"
#include "ap_axi_sdata.h"
#include <stdio.h>
#include <hls_math.h>
#include <ap_int.h>
#include <stdlib.h>
#include <ap_fixed.h>

#define IMAGE_I			256
#define IMAGE_J			256
#define KERNEL_DIM		3
#define IMAGE_BIT		8
#define IMAGE_MAX_VAL	256
#define IMAGE_BORDER	0

typedef ap_axiu<IMAGE_BIT,2,5,6> uint_side_channel;
typedef ap_axis<IMAGE_BIT,2,5,6> int_side_channel;
//function prototypes
void Point_OP(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &inStream2,hls::stream<uint_side_channel> &outStream,int op,int value,bool ImAmount,int Point_TDEST);
unsigned char op01(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op02(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op03(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op04(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op05(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op06(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op07(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op08(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op09(ap_uint<IMAGE_BIT> pixIn,int value);
unsigned char op010(ap_uint<IMAGE_BIT> pixIn,int value);

