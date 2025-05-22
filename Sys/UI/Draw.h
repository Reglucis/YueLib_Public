/*****************************************************************************************************
 * @file        Draw.h
 * @author      RegLucis
 * @version     V1.0
 * @date        2023-08-09
 * @brief       绘制参数
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @details 	
 * 					
 ***************************************************************************************************
 * @bug 		
 ***************************************************************************************************/
#ifndef __Draw__
#define __Draw__

#include <stdint.h>

//定义写字笔的颜色
#define PEN_COLOR     YELLOW

//定义背景颜色
#define BG_COLOR      RED

//函数声明
void Draw_Init(void);
void Draw_clear(uint16_t color);
void Draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void Draw_point(uint16_t x, uint16_t y, uint16_t color);
void Draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Draw_soildTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void Draw_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Draw_soildRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void Draw_solidCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void Draw_char(uint16_t x, uint16_t y, const char data);
void Draw_str(uint16_t x, uint16_t y, const char data[]);
void Draw_int(uint16_t x, uint16_t y, int32_t data);
void Draw_float(uint16_t x, uint16_t y, float data);
void Draw_image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *data);

void Draw_test(void);

#endif
