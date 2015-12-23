/*************************************************************************
	> File Name: binary.c
	> Author: 
	> Mail: 
	> Created Time: 2015年12月14日 星期一 14时39分16秒
 ************************************************************************/


#include "config.h"



int binary(unsigned char* input, 
	int width, int height) {

	int i;
	int count = width * height;

	int thre = threshold(input, width, height);

	

	for (i = 0; i < count; ++i)
	{
		input[i] = (unsigned char)(input[i] >= thre? 255 : 0);
	}

	return 0;

}

