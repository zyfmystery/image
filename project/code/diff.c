/*************************************************************************
	> File Name: diff.c
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 15时40分40秒
 ************************************************************************/

#include "config.h"



void diff(const unsigned char *first, 
	const unsigned char* second,
	const unsigned char* third,
    int width, int height)
{

	int i, count;
	int tmp1, tmp2;

	printf("diff\n");

	if ((first == NULL) || (second == NULL) ||
		(third == NULL) ) {

		printf("App Error-> image memory is NULL\n");

		return;
	}

	if (height <= 0 || width <= 0) {
		
		printf("App Error-> image width * height is error\n");

		return;

	}

	count = width * height;
    
    memset(destbuffer, 0 ,FRAMESIZE);
	for (i = 0; i < count; ++i)
	{
		
		tmp1 = abs(second[i] - first[i]);

		tmp2 = abs(second[i] - third[i]);

        destbuffer[i] = tmp2 | tmp1;

	}


	return;

}

