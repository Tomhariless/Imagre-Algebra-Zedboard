#include "hls_video.h"
#include "ap_axi_sdata.h"
#include <stdio.h>
#include <hls_math.h>
#include <ap_int.h>
#include <stdlib.h>
#include <ap_fixed.h>

#define IMAGE_I			512
#define IMAGE_J			512
#define KERNEL_DIM		3
#define IMAGE_BIT		8
#define IMAGE_MAX_VAL	256
#define IMAGE_BORDER	0

typedef ap_axiu<IMAGE_BIT,2,5,6> uint_side_channel;
typedef ap_axis<IMAGE_BIT,2,5,6> int_side_channel;

//function prototypes
void Image_algebra_N_Loop(hls::stream<uint_side_channel> &inStream,hls::stream<uint_side_channel> &outStream,int op1,char kernel[KERNEL_DIM*KERNEL_DIM],int op2,int op3,int op3Val,unsigned int loops, unsigned int K_rotate, int Neighbour_TDEST);
//operation 1:
//op1: 1:* 2:+ 3:and 4:or 5:convolution
void op11(int window[KERNEL_DIM][KERNEL_DIM], char kernel[KERNEL_DIM*KERNEL_DIM],int L,unsigned int K_rotate);
void op12(int window[KERNEL_DIM][KERNEL_DIM], char kernel[KERNEL_DIM*KERNEL_DIM],int L,unsigned int K_rotate);
void op13(int window[KERNEL_DIM][KERNEL_DIM], char kernel[KERNEL_DIM*KERNEL_DIM],int L,unsigned int K_rotate);
void op14(int window[KERNEL_DIM][KERNEL_DIM], char kernel[KERNEL_DIM*KERNEL_DIM],int L,unsigned int K_rotate);
short op15(int window[KERNEL_DIM][KERNEL_DIM], char kernel[KERNEL_DIM*KERNEL_DIM],int L,unsigned int K_rotate);
void op16(int window[KERNEL_DIM][KERNEL_DIM],char kernel[KERNEL_DIM*KERNEL_DIM],unsigned int label_counter[1]);
//operation 2:
//op2: 0: nothing, 1: sum, 2:min, 3:max 4: sum abs
short op20(int window[KERNEL_DIM][KERNEL_DIM]);
short op21(int window[KERNEL_DIM][KERNEL_DIM]);
short op22(int window[KERNEL_DIM][KERNEL_DIM]);
short op23(int window[KERNEL_DIM][KERNEL_DIM]);
short op24(int window[KERNEL_DIM][KERNEL_DIM]);

//operation 3:
//op3: 0: nothing, 1: thresholding 2:count pixels equal 3: count pixels above 4: count pixels less
unsigned char op31(ap_uint<IMAGE_BIT> inpix, unsigned char value);
unsigned int op32(ap_uint<IMAGE_BIT> inpix, unsigned char value, unsigned int currentVal);
unsigned int op33(ap_uint<IMAGE_BIT> inpix, unsigned char value, unsigned int currentVal);
unsigned int op34(ap_uint<IMAGE_BIT> inpix, unsigned char value, unsigned int currentVal);
