#include "test.h"

using namespace std;

int main(){
	FILE *fp;
	fp = fopen("C:\\Users\\40148119\\TextureFeature\\HLS_Project\\Image_algebra\\Point_OP\\result\\ImageA_out.txt","w+");
	hls::stream<uint_side_channel> inStream;
	hls::stream<uint_side_channel> inStream2;
	hls::stream<uint_side_channel> outStream;
	uint_side_channel valIn;
	uint_side_channel result;
	int op=1;
	int value=128;
	bool imAmount=0;
	int result_data;
	for (int idx=0;idx<(IMAGE_I*IMAGE_J);idx++){
		valIn.data = lena[idx];
		valIn.keep = 1; valIn.strb = 1; valIn.user = 1; valIn.id = 0; valIn.dest = 0;
		inStream<<valIn;
	}
	for (int idx=0;idx<(IMAGE_I*IMAGE_J);idx++){
		valIn.data = lena[idx];
		valIn.keep = 1; valIn.strb = 1; valIn.user = 1; valIn.id = 0; valIn.dest = 0;
		inStream2<<valIn;
	}
	Point_OP(inStream,inStream2,outStream,op,value,imAmount);
	for (int idx=0;idx<(IMAGE_I*IMAGE_J);idx++){
		outStream.read(result);
		result_data = result.data;
		fprintf(fp,"%d \n",result_data);
	}
	fclose(fp);
}
