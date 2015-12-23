

#include "config.h"


int 			fd = -1; //
char  			*dev_name = NULL; //
unsigned int 	frame_count = 1; //
int 			force_format = 0; //

const char 		*srcfile = "src.yuv";
const char		*grayfile = "gray.yuv";
const char		*edgefile = "edge.yuv";
const char 		*outfile = "out.yuv";
//  char 			*yuv420file = "yuv420.yuv";
//  char 			*diffile = "diff.yuv";
FILE 			*srcfp = NULL;
FILE 			*grayfp = NULL;
FILE 			*edgefp = NULL;
FILE 			*outfp = NULL;

unsigned char* 	firstframe = NULL;
unsigned char* 	secondframe = NULL;
unsigned char* 	thirdframe = NULL;
unsigned char* 	destbuffer = NULL;
unsigned char*  filterbuffer = NULL;
unsigned char*  morbuffer = NULL;
double          sigma = 1.4;


enum   io_method io = IO_METHOD_MMAP;
struct buffer *buffers;
unsigned int n_buffers;


static const char* usage = "%s: video-device-name\n";


int main(int argc, char *argv[])
{

	int flag; 
	int i;
    // int k;
	int count = 100;
	// unsigned char* tmp;


	if (argc == 2){

	    dev_name = argv[1];

    }else{

    	fprintf(stderr, usage, argv[0]);
        exit(1);
    }


    if((srcfp = fopen(srcfile, "wb")) == NULL) {
        
        printf("App-> ERROR: file open error\n");
        goto end;
    }

    if((grayfp = fopen(grayfile, "wb")) == NULL) {

        printf("App-> ERROR: file open error\n");
        goto end;
    }

    if((edgefp = fopen(edgefile, "wb")) == NULL) {
        
        printf("App-> ERROR: file open error\n");
        goto end;
    }

    if((outfp = fopen(outfile, "wb")) == NULL) {

        printf("App-> ERROR: file open error\n");
        goto end;
    }


    firstframe = (unsigned char*)malloc(FRAMESIZE);
    secondframe = (unsigned char*)malloc(FRAMESIZE);
    thirdframe = (unsigned char*)malloc(FRAMESIZE);
    destbuffer = (unsigned char*)malloc(FRAMESIZE);
    filterbuffer = (unsigned char*)malloc(FRAMESIZE);
    morbuffer = (unsigned char*)malloc(FRAMESIZE);

    if ((firstframe == NULL) ||(secondframe == NULL) || 
    	(thirdframe == NULL) || (morbuffer == NULL)||
    	(destbuffer == NULL) || (filterbuffer == NULL)) {
    	
    	printf("App-> ERROR: malloc memory error\n");
        goto end;
    }

    memset(firstframe, 0, FRAMESIZE);
    memset(secondframe, 0, FRAMESIZE);
    memset(thirdframe, 0, FRAMESIZE);

    
    if ((flag = video()) == -1) {
    	
    	printf("App-> ERROR: video init error\n");
        goto end;
    }


    // first = (Frame*)calloc(1, sizeof(*first));
    // second = (Frame*)calloc(1, sizeof(*second));
    // third = (Frame*)calloc(1, sizeof(*second));

    // if (first == NULL || second == NULL || third == NULL) {
    	
    // 	printf("App-> ERROR: frame calloc error\n");
    //     goto end;
    // }



    for (i = 0; i < count; ++i)
    {

        printf("frame = %d\n", i);
        memset(destbuffer, 0, FRAMESIZE);
        memset(filterbuffer, 0, FRAMESIZE);

        mainloop();

        filter(filterbuffer, destbuffer, IMAGE_WIDTH, IMAGE_HEIGHT);
        fwrite(filterbuffer, FRAMESIZE, 1, srcfp);

        if (i == 0)
        {
            soble(filterbuffer, firstframe, 
             IMAGE_WIDTH, IMAGE_HEIGHT);
            fwrite(firstframe, FRAMESIZE, 1, edgefp);
        }

        if (i == 1)
        {
            soble(filterbuffer, secondframe, 
             IMAGE_WIDTH, IMAGE_HEIGHT);
            fwrite(secondframe, FRAMESIZE, 1, edgefp);
        }

        if (i >= 2)
        {
            soble(filterbuffer, thirdframe, 
             IMAGE_WIDTH, IMAGE_HEIGHT);
            fwrite(thirdframe, FRAMESIZE, 1, edgefp);

            memset(destbuffer, 0, FRAMESIZE);
            memset(morbuffer, 0, FRAMESIZE);
            
            diff(firstframe, secondframe, thirdframe, IMAGE_WIDTH, IMAGE_HEIGHT);
            binary(destbuffer, IMAGE_WIDTH, IMAGE_HEIGHT);
            morphology(destbuffer, morbuffer, IMAGE_WIDTH, IMAGE_HEIGHT);
            fwrite(morbuffer, FRAMESIZE, 1, outfp);

            memcpy(firstframe, secondframe, FRAMESIZE);
            memcpy(secondframe, thirdframe, FRAMESIZE);
            memset(thirdframe, 0 ,FRAMESIZE);
        }

    }

end:
    
    if (flag)
    {
        unvideo();
    }

    /**
    */
    if(srcfp) {
        fclose(srcfp);
    }

    if(grayfp) {
        fclose(grayfp);
    } 

    if(edgefp) {
        fclose(edgefp);
    }

    if(outfp) {
        fclose(outfp);
    } 

    printf("fp closed\n");

    if (firstframe) {
    	free(firstframe);
    }

    if (secondframe) {
    	free(secondframe);
    }
    
    if (thirdframe) {
    	free(thirdframe);
    }

    if (destbuffer) {
    	free(destbuffer);
    }

    if (filterbuffer) {
        free(filterbuffer);
    }

    if (morbuffer) {
        free(morbuffer);
    }

    printf("fp closed\n");



    printf("app done\n");

	return 0;
}

