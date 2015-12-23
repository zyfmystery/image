/**
*
*/

#include "config.h"


void process_image(const void *p, int size) 
{

	// fwrite(p, size, 1, srcfp);

	// printf("process_image start size=%d\n", size);

	YUV422TOGray(destbuffer, (unsigned char*)p, IMAGE_WIDTH, IMAGE_HEIGHT);

	fwrite(destbuffer, FRAMESIZE, 1, grayfp);
	
}


// void YUV422TO420(unsigned char* dest, 
// 	const unsigned char* src, 
// 	int width, int height)
// {

// 	unsigned int ynum = width * height;

//     int i, j, k = 0;

//     //得到Y分量
//     for(i = 0; i < ynum; i++) {

//        dest[i] = src[i * 2];
//     }


//     //得到U分量
//     for(i = 0; i < height; i++) {

//        if((i % 2) != 0){
//             continue;
//        }

//        for(j = 0; j < (width / 2); j++) {

//            if((4 * j + 1) > (2 * width)){
//                 break;
//            }

//            dest[ynum + k * 2 * width / 4 + j] = src[i * 2 * width + 4 * j + 1];
                   
//         }

//         k++;
//     }


//     k=0;

//     //得到V分量
//     for(i = 0; i < height; i++) {

//        if((i % 2) == 0){
//             continue;
//        }

//        for(j = 0; j < (width / 2); j++) {

//            if((4 * j + 3) > (2 * width)){
//                 break;
//            }

//            dest[ynum + ynum / 4 + k * 2 * width / 4 + j] = 
//                                 src[i * 2 * width + 4 * j + 3];
          
//        }

//         k++;
//     }
       
//     return;

// }


void YUV422TO420(unsigned char* dest, 
 const unsigned char* src, int width, int height) {

  


}


void YUV422TOGray(unsigned char* dest, 
	const unsigned char* src, 
	int width, int height)
{

	// printf("YUV422TOGray start\n");

	unsigned int frame = width * height;
	printf("YUV422TOGray frame=%d\n", frame);

    int i;

    for (i = 0; i < frame; ++i) {
    	// printf("YUV422TOGray %d\n", i);

        dest[i] = src[i * 2];
    }

    // printf("YUV422TOGray done\n");
    return ;


}

