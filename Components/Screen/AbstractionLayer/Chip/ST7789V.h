#ifndef __IPS114_ST7789V__
#define __IPS114_ST7789V__

#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "FONT.h"

// #define int8_t  char
// #define int16_t short
// #define int32_t int
// #define uint8_t  unsigned char
// #define uint16_t unsigned short
// #define uint32_t unsigned int

//DMA启用控制
#define DMA_ENABLE 1
#define FILED_IT 0

//定义写字笔的颜色
#define IPS114_PENCOLOR     YELLOW

//定义背景颜色
#define IPS114_BGCOLOR      RED

//定义分辨率
#define IPS114_W   240
#define IPS114_H   170

//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define ST7789_ROTATION 3

#if	  ( ST7789_ROTATION == 0 )
	#define	ST7789_W	IPS114_H
	#define ST7789_H	IPS114_W
	#define X_OFFSET 		52
	#define Y_OFFSET 		40

#elif ( ST7789_ROTATION == 1 )
	#define	ST7789_W	IPS114_H
	#define ST7789_H	IPS114_W
	#define X_OFFSET 		53
	#define Y_OFFSET 		40

#elif ( ST7789_ROTATION == 2 )
	#define	ST7789_W	IPS114_W
	#define ST7789_H	IPS114_H
	#define X_OFFSET 		40
	#define Y_OFFSET 		53

#else
	#define	ST7789_W	IPS114_W
	#define ST7789_H	IPS114_H   
	#define X_OFFSET 		40
	#define Y_OFFSET 		52
#endif

//定义工作区大小(图像缓冲区)
#define BUFFER_W   100
#define BUFFER_H   50

//定义工作区位置(图像缓冲区)
#define BUFFER_X ( ST7789_WIDTH - BUFFER_W ) / 2
#define BUFFER_Y ( ST7789_HEIGHT - BUFFER_H ) / 2

void ST7789_test();


#endif
