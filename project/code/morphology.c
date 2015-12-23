/*************************************************************************
	> File Name: morphology.c
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 15时42分06秒
 ************************************************************************/

#include "config.h"

int structure[] = {0, 1, 0, 1, 1, 1, 0, 1, 0};


static void dilation(unsigned char* input, unsigned char* dest,
    int width, int height);
static void erosion(unsigned char* input, unsigned char* dest,
    int width, int height);


void morphology(unsigned char* input, unsigned char* dest,
    int width, int height) {

    dilation(input, dest, width, height);
    erosion(input, dest, width, height);
}



void dilation(unsigned char* input, unsigned char* dest,
    int width, int height) {

	int i, j;

	int c01, c10, c11, c12, c21;

	if (input == NULL) {
		
		printf("App Error-> input memory is NULL\n");

		return;
	}


	if(width <= 0 || height <= 0) {

		printf("App Error-> image width * height is error\n");

		return;
	}

	for (i = 0; i < height; ++i)
	{

        for (j = 0; j < width; ++j) 
        {

        	if (i - 1 < 0 || i - 1 >= height) {
        		c01 = 0;
        	} else {
        		c01 = input[(i - 1) * width + j];
        	}


        	if (j - 1 < 0 || j - 1 >= width) {
        		c10 = 0;
        	} else {
        		c10 = input[i * width + j - 1];
        	}


        	if (j + 1 < 0 || j + 1 >= width) {
        		c12 = 0;
        	} else {
        		c12 = input[i * width + j + 1];
        	}


        	if (i + 1 < 0 || i + 1 >= height) {
        		c21 = 0;
        	} else {
        		c21 = input[(i + 1) * width + j];
        	}

        	c11 = input[i * width + j];

            if (c01 == 0 && c10 == 0 && c11 == 0 
                && c12 == 0 && c21 == 0) {

           		dest[i * width + j] = 0; 
            } else {

            	dest[i * width + j] = 255;
            }
        }
    }

    return;

}


void erosion(unsigned char* input, unsigned char* dest,
    int width, int height) {

	int i, j;

	int c01, c10, c11, c12, c21;

	if (input == NULL) {
		
		printf("App Error-> input memory is NULL\n");

		return;
	}


	if(width <= 0 || height <= 0) {

		printf("App Error-> image width * height is error\n");

		return;
	}

	for (i = 0; i < height; ++i)
	{

        for (j = 0; j < width; ++j) 
        {

        	if (i - 1 < 0 || i - 1 >= height) {
        		c01 = 0;
        	} else {
        		c01 = input[(i - 1) * width + j];
        	}


        	if (j - 1 < 0 || j - 1 >= width) {
        		c10 = 0;
        	} else {
        		c10 = input[i * width + j - 1];
        	}


        	if (j + 1 < 0 || j + 1 >= width) {
        		c12 = 0;
        	} else {
        		c12 = input[i * width + j + 1];
        	}


        	if (i + 1 < 0 || i + 1 >= height) {
        		c21 = 0;
        	} else {
        		c21 = input[(i + 1) * width + j];
        	}

        	c11 = input[i * width + j];

            if (c01 == 255 && c10 == 255 && c11 == 255 
                && c12 == 255 && c21 == 255) {

           		dest[i * width + j] = 255; 
            } else {

            	dest[i * width + j] = 0;
            }
        }
    }

    return;

}

