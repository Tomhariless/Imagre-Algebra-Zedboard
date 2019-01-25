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

void Global_OP(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &outStream,int op,bool mode,int Result[256],int Global_TDEST);
//op0 histogram, op1 global max op2 global min, op3 global total op4 global sum/x*y

