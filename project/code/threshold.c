/*************************************************************************
	> File Name: threshold.c
	> Author: 
	> Mail: 
	> Created Time: 2015年12月02日 星期三 16时26分33秒
 ************************************************************************/

#include "config.h"




int threshold(const unsigned char* input, 
 int width, int height) {

	int count = width * height;

	int i;

	int thInit = 0;

	// printf("a frame size is %d\n", count);

	for (i = 0; i < count; ++i) {
		
		thInit += input[i];
	}

	

	thInit = thInit / count;
	// printf("threshold init = %d\n", thInit);
	int g1 = 0, g2 = 0, m = 0, n = 0;
	int m1, m2, tmp = 0;

	int cnt = 0;

	while(1) {	

		if (cnt != 0) {
			
			thInit = tmp;
		}

		if (abs(thInit - tmp ) <= 0) {
			break;
		}

		for (i = 0; i < count; ++i) {
			
			if (input[i] >= thInit) {
				g1 += input[i];
				m++;
			} else {
				g2 += input[i];
				n++;
			}
		}

		m1 = g1 / m;
		m2 = g2 / n;

		tmp = (m1 + m2) / 2;

		m = 0;
		n = 0;
		g1 = 0;
		g2 = 0;

		cnt++;
	}

	// printf("iterator %d\n", cnt);
	printf("threshold is val = %d\n", thInit);

	return thInit;

}
