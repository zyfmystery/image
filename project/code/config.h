

#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>


/** macro define */
#define FRAMENUM		100
#define BUFFERSIZE		1024
#define FRAMESIZE       101376
#define IMAGE_WIDTH		352
#define IMAGE_HEIGHT 	288

#define CLEAR(x) 	memset(&(x), 0, sizeof(x))


/** video capture method*/
enum io_method {
        IO_METHOD_READ,
        IO_METHOD_MMAP,
        IO_METHOD_USERPTR,
};

/** a frame image struct */
struct buffer {
        void   *start;
        size_t  length;
};


/** global variable */
extern enum   io_method io; //video capture method
extern struct buffer *buffers; //frame buffer
extern unsigned int n_buffers; //buffer index

extern int 				fd ; // video文件描述符
extern char  			*dev_name ; // video name
extern unsigned int 	frame_count; // capture frame/pre
extern int 				force_format; 

extern const char 		*srcfile; //原始视频保存文件，YUYV
extern const char		*grayfile; //灰度化视频保存文件
extern const char		*edgefile; //图像边缘化后保存文件
extern const char 		*outfile; //运动目标检测保存图像
extern FILE 			*srcfp;
extern FILE 			*grayfp;
extern FILE 			*edgefp;
extern FILE 			*outfp;

extern unsigned char* 	firstframe; //第k帧视频
extern unsigned char* 	secondframe; //第k+1帧视频
extern unsigned char* 	thirdframe; //第k+2帧视频
extern unsigned char* 	destbuffer; //中间结果保存缓冲区
extern unsigned char* 	filterbuffer; 
extern unsigned char* 	morbuffer; 
extern double 			sigma;


/** function */
extern void start_capturing(void); //video capture start
extern void stop_capturing(void); 
extern void init_device(void);
extern void uninit_device(void);
extern void open_device(void);
extern void close_device(void);
extern int video(void); 
extern void unvideo(void);
extern void mainloop(void);

/** */
extern void process_image(const void *p, int size);
extern void YUV422TO420(unsigned char* dest, 
	const unsigned char* src, 
	int width, int height); //
extern void YUV422TOGray(unsigned char* dest, 
	const unsigned char* src, 
	int width, int height); //


extern void filter(unsigned char* dest, 
	unsigned char *src, 
	int width, int height);

extern void soble(const unsigned char* input, 
	unsigned char* edge, 
	int width, int height); 

extern int threshold(const unsigned char* input, 
	int width, int height);

extern void diff(const unsigned char *first, 
	const unsigned char* second,
	const unsigned char* third, 
	int width, int height);

extern int binary(unsigned char* input, 
	int width, int height);


extern void morphology(unsigned char* input, 
	unsigned char* dest,
    int width, int height);

#endif
