/*************************************************************************
	> File Name: filter_test.c
	> Author:zyfmystery 
	> Mail: 
    > Description:
        高斯滤波：一种线性平滑滤波，适用于滤除高斯白噪声

	> Created Time: 2015年11月18日 星期三 15时18分00秒
 ************************************************************************/

#include "config.h"

#define PI      3.14159


// static void makeguass(double simg, double* pdKernal, int* length);

static void guass(unsigned char* dest, unsigned char *src, 
    int width, int height, double sigma);
/**
*
*/
void filter(unsigned char* dest, unsigned char *src, 
    int width, int height) {

    printf("filter start\n");
    guass(dest, src, width, height, sigma);

}

/**
* 
*/
void guass(unsigned char* dest, unsigned char *src, 
    int width, int height, double sigma) {

    int x, y;
    int i, j;
    int nCenter; //窗口长度的1/2
    double dDotMul; //高斯系数与图像数据的点乘
    double dWeightSum; //高斯滤波系统的总和

    int guassLen; //高斯滤波器数组长度
    double *pdKernal; //一维高斯滤波器
    double dDis; //某一个点到数组中心点的距离
    double dValue;//中间变量
    double dSum = 0;

    //数组长度，根据概率论的知识,选取[-3*sigma, 3*sigma]以内的数据
    guassLen = 1 + 2 * ceil(3 * sigma);
    nCenter = guassLen / 2;

    pdKernal = (double *)malloc(guassLen * sizeof(double));
    // printf("pdKernal %x\n", (int)(pdKernal));
    // free(pdKernal);
   
    memset(pdKernal, 0, guassLen);

    for (i = 0; i < guassLen; ++i)
    {
        dDis = (double)(i - nCenter);

        dValue = ((1 / (sigma * sqrt(2 * PI))) * 
            (exp(-(dDis * dDis) / (2 * sigma * sigma))));

        pdKernal[i] = dValue;
        dSum += dValue;
    }

    //归一化
    for (i = 0; i < guassLen; ++i)
    {
        pdKernal[i] = pdKernal[i] / dSum;
    }


    //MakeGauss返回窗口的长度，利用此变量计算窗口的半长
    
    // printf("guassLen %d\n", guassLen);
    // printf("nCenter %d\n", nCenter);

    printf("guass filter start\n");

    int count = height * width;


    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            dDotMul = 0.0;
            dWeightSum = 0.0;
            
            for(x = (-nCenter); x <= nCenter; x++)
            {
                for(y = (-nCenter); y <= nCenter; y++)
                {
                    if((j + x) >= 0 && (j + x) < width &&
                       (i + y) >= 0 && (i + y) < height){
                        
                           if((i + y) * width + j + x < count){

                                double imageData =
                                   (double)(src[(i + y) * width + j + x]);

                                dDotMul += imageData * 
                                            pdKernal[(y + nCenter) * guassLen
                                                   + x + nCenter];
                                dWeightSum += pdKernal[(y + nCenter) * guassLen
                                                + x + nCenter];
                           }
                          
                       }
                }
            }

            dest[i * width + j] = dDotMul / dWeightSum;
        }
    }

    // printf("guass filter done\n");
    // printf("pdKernal %x\n", (int)(pdKernal));

    free(pdKernal);

    printf("guass filter done\n");


    // //x方向滤波
    // for (y = 0; y < height; ++y)
    // {

    //     for (x = 0; x < width; ++x)
    //     {
    //         dDotMul = 0;
    //         dWeightSum = 0;

    //         for (i = (-nHalfLen); i <= nHalfLen; i++)
    //         {
    //             if((i + x >= 0 && i + x < width) && (y * width + i + x < count)) {

    //                 dDotMul += 
    //                     src[y * width + i + x] * pdKernal[nHalfLen + i];

    //                 dWeightSum += pdKernal[nHalfLen + i];
    //             }
    //         }

    //         pdtmp[y * width + x] = dDotMul / dWeightSum;

    //     }
    // }

    // printf("guass filter y\n");
    // //y方向滤波   
    // for (x = 0; x < width; ++x)
    // {

    //     for (y = 0; y < height; ++y)
    //     {
    //         dDotMul = 0;
    //         dWeightSum = 0;

    //         for (i = (-nHalfLen); i <= nHalfLen; i++)
    //         {
    //             if(i + y >= 0 && i + y < height) {

    //                 dDotMul += 
    //                     pdtmp[(y + i) * width + x] * pdKernal[nHalfLen + i];

    //                 dWeightSum += pdKernal[nHalfLen + i];
    //             }
    //         }

    //         dest[y * width + x] = (unsigned char)(int)(dDotMul / dWeightSum);

    //     }
    // }

    // free(pdtmp);
    // free(pdKernal);
    // pdKernal = NULL;
    // pdtmp = NULL;
    return;
}


// void makeguass(double sigma, double* pdKernal, int* length) {

//     int i; //循环控制变量
//     int nCenter; //数组中心点
//     double dDis; //某一个点到数组中心点的距离
//     double dValue;//中间变量
//     double dSum = 0;

//     //数组长度，根据概率论的知识,选取[-3*sigma, 3*sigma]以内的数据
//     *length = 1 + 2 * ceil(3 * sigma);
//     nCenter = *length >> 1;

//     pdKernal = (double *)malloc(*length);
//     memset(pdKernal, 0, *length);

//     for (i = 0; i < *length; ++i)
//     {
//         dDis = (double)(i - nCenter);

//         dValue = ((1 / (sigma * sqrt(2 * PI))) * 
//             (exp(-(dDis * dDis) / (2 * sigma * sigma))));

//         pdKernal[i] = dValue;
//         dSum += dValue;
//     }

//     //归一化
//     for (i = 0; i < *length; ++i)
//     {
//         pdKernal[i] = pdKernal[i] / dSum;
//     }

// }

/**
 * 高斯滤波
 */
// void guassFilter(char* input, char* result, 
//                  unsigned int width,unsigned int height, 
//                 double dSigma)
// {

//     /**
//      *input:待处理图像
//      *result:保存滤波结果
//      *width：图像的宽度
//      *height：图像的高度
//      *dSigma:高斯滤波参数，方差
//      **/

//     int count = width * height;

//     int nWidth = (int)(1 + 2 * ceil(3 * dSigma));
//     int nCenter = nWidth / 2;
    
//     // 生存二维高斯滤波系数
//     double* pdKernal = (double*)calloc(nWidth * nWidth, sizeof(double));
//     double dSum = 0.0;
    
//     // 二维高斯函数
//     int i, j;
//     for(i = 0; i < nWidth; i++)
//     {
//         for(j = 0; j < nWidth; j++)
//         {
//             int nDis_x = i - nCenter;
//             int nDis_y = j - nCenter;

//             pdKernal[i + j * nWidth] = exp(-1 * (nDis_x * nDis_x +
//                      nDis_y * nDis_y) / (2 * dSigma * dSigma)) /
//             (2 * PI * dSigma * dSigma);

//             dSum += pdKernal[i + j * nWidth];
//         }
//     }

//     // 进行归一化
//     for(i = 0; i < nWidth; i++)
//     {
//         for(j = 0; j < nWidth; j++)
//         {
//             pdKernal[i + j * nWidth] /= dSum;
//         }
//     }

//     int x, y;

    // for(i = 0; i < height; i++)
    // {
    //     for(j = 0; j < width; j++)
    //     {
    //         double dFilter = 0.0;
    //         double sum = 0.0;
            
    //         for(x = (-nCenter); x <= nCenter; x++)
    //         {
    //             for(y = (-nCenter); y <= nCenter; y++)
    //             {
    //                 if((j + x) >= 0 && (j + x) < width &&
    //                    (i + y) >= 0 && (i + y) < height){
                        
    //                        if((i + y) * width + j + x < count){
    //                             double imageData =
    //                                (double)(input[(i + y) * width + j + x]);
    //                             dFilter += imageData * 
    //                                         pdKernal[(y + nCenter) * nWidth
    //                                                + x + nCenter];
    //                             sum += pdKernal[(y + nCenter) * nWidth
    //                                             + x + nCenter];
    //                        }
                          
    //                    }
    //             }
    //         }

    //         result[i * width + j] = dFilter / sum;
    //     }
    // }

    // free(pdKernal);

    // return;
        
// }








