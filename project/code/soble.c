/*************************************************************************
	> File Name: soble.c
	> Author: 
	> Mail: 
	> Created Time: 2015年12月14日 星期一 10时51分57秒
 ************************************************************************/

#include "config.h"


const char Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
const char Gy[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};


/**
*/
void soble(const unsigned char* input, 
	unsigned char* edge, int width, int height) {

	int i, j, m;
    int gx, gy, g;

    int gxy1_1, gxy10, gxy11, gxy_1_1, gxy_10, gxy_11;

    int cxy_1_1, cxy0_1, cxy1_1, cxy_11, cxy01, cxy11;

    m = 0;


	for (i = 0; i < height; ++i) {

        for (j = 0; j < width; ++j) {

            // printf("i = %d, j= %d\n", i, j);

            if (i + 1 < 0 || i + 1 >= height || j - 1 < 0 || j - 1 >= width) {
                gxy1_1 = 0;
                cxy1_1 = 0;
            } else {
                gxy1_1 = input[(i + 1) * width + j - 1];
                cxy1_1 = input[(i + 1) * width + j - 1];
            }

            if (i + 1 < 0 || i + 1 >= height || j < 0 || j >= width) {
               gxy10 = 0;
            } else {
                gxy10 = input[(i + 1) * width + j];
            }

            if (i + 1 < 0 || i + 1 >= height || j + 1 < 0 || j + 1 >= width) {
                gxy11 = 0;
                cxy11 = 0;
            } else {
                gxy11 = input[(i + 1) * width + j + 1];
                cxy11 = input[(i + 1) * width + j + 1];
            }


            if (i - 1 < 0 || i - 1 >= height || j - 1 < 0 || j - 1 >= width) {
                gxy_1_1 = 0;
                cxy_1_1 = 0;
            } else {
                gxy_1_1 = input[(i - 1) * width + j - 1];
                cxy_1_1 = input[(i - 1) * width + j - 1];
            }

            if (i - 1 < 0 || i - 1 >= height || j < 0 || j >= width) {
                gxy_10 = 0;
            } else {
                gxy_10 = input[(i - 1) * width + j];
            }

            if (i - 1 < 0 || i - 1 >= height || j + 1 < 0 || j + 1 >= width) {
                gxy_11 = 0;
                cxy_11 = 0;
            } else {
                gxy_11 = input[(i - 1) * width + j + 1];
                gxy_11 = input[(i - 1) * width + j + 1];
            }

            if (i < 0 || i  >= height || j + 1 < 0 || j + 1 >= width) {
                cxy01 = 0;
            } else {
                cxy01 = input[(i) * width + j + 1];
            }

            if (i < 0 || i >= height || j - 1 < 0 || j - 1 >= width) {
                cxy0_1 = 0;
            } else {
                cxy0_1 = input[(i) * width + j - 1];
            }

            gx = gxy1_1 + 2 * gxy10 + gxy11 - (gxy_1_1 + 2 * gxy_10 + gxy_11);
            gy = cxy_1_1 + 2 * cxy0_1 + cxy1_1 - (cxy_11 + 2 * cxy01 + cxy11);
            
            g = abs(gx) + abs(gy);
            
            // printf("gVal = %d\n", g);

            edge[m++] = g % 256;
        }
    }

    printf("soble completed\n");
    
	return ;

}


