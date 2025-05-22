/*****************************************************************************************************
 * @file        ILI9341.h
 * @author      RegLucis
 * @version     V1.0
 * @date        2023-08-09
 * @brief       驱动控制器配置
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @details 	
 * @warning		偷懒，未进行验证😝
 * 		
 ***************************************************************************************************
 * @bug 		
 ***************************************************************************************************/
#include "./Device/Screen/Configuration.h"
#include "stm32f4xx_hal.h"

#ifndef __ILI9341__
#define __ILI9341__

#define screen_init	Init_ILI9341
static void Init_ILI9341(void)
{
	dbi_write_cmd(0x36);
	#if  (SCREEN_ROTATION == 0)    
		dbi_write_data16(0x08 | 1 << 6);
	#elif(SCREEN_ROTATION == 1)    
		dbi_write_data16(0xC8);
	#elif(SCREEN_ROTATION == 2)    
		dbi_write_data16(0x78);
	#else    
		dbi_write_data16(0xA8);
	#endif


	//Power control B
    dbi_write_cmd(0xCF);
    dbi_write_data16(0x00);
    dbi_write_data16(0xC1);
    dbi_write_data16(0x30);
	//Power on sequence control
    dbi_write_cmd(0xED);
    dbi_write_data16(0x64);
    dbi_write_data16(0x03);
    dbi_write_data16(0x12);
    dbi_write_data16(0x81);
	//Driver timing control A
    dbi_write_cmd(0xE8);
    dbi_write_data16(0x85);
    dbi_write_data16(0x10);
    dbi_write_data16(0x7A);
	//Power control A
    dbi_write_cmd(0xCB);
    dbi_write_data16(0x39);
    dbi_write_data16(0x2C);
    dbi_write_data16(0x00);
    dbi_write_data16(0x34);
    dbi_write_data16(0x02);
	//Pump ratio control 
    dbi_write_cmd(0xF7);
    dbi_write_data16(0x20);
	//Driver timing control B
    dbi_write_cmd(0xEA);
    dbi_write_data16(0x00);
    dbi_write_data16(0x00);
	//Power control 1
    dbi_write_cmd(0xC0);
    dbi_write_data16(0x1B);
	//Power control 2
    dbi_write_cmd(0xC1);
    dbi_write_data16(0x01);
	//VCOM Control 1
    dbi_write_cmd(0xC5);
    dbi_write_data16(0x30);
    dbi_write_data16(0x30);
	//VCOM Control 2
    dbi_write_cmd(0xC7);
    dbi_write_data16(0xB7);
	//COLMOD: Pixel Format Set
    dbi_write_cmd(0x3A);
    dbi_write_data16(0x55);
	//Frame Rate Control
    dbi_write_cmd(0xB1);
    dbi_write_data16(0x00);
    dbi_write_data16(0x1A);
	//Display Function Control
    dbi_write_cmd(0xB6);
    dbi_write_data16(0x0A);
    dbi_write_data16(0xA2);
	//Enable 3G 
    dbi_write_cmd(0xF2);
    dbi_write_data16(0x00);
	//Gamma Set
    dbi_write_cmd(0x26);
    dbi_write_data16(0x01);
	//Positive Gamma Correction
    dbi_write_cmd(0xE0);
    dbi_write_data16(0x0F);
    dbi_write_data16(0x2A);
    dbi_write_data16(0x28);
    dbi_write_data16(0x08);
    dbi_write_data16(0x0E);
    dbi_write_data16(0x08);
    dbi_write_data16(0x54);
    dbi_write_data16(0xA9);
    dbi_write_data16(0x43);
    dbi_write_data16(0x0A);
    dbi_write_data16(0x0F);
    dbi_write_data16(0x00);
    dbi_write_data16(0x00);
    dbi_write_data16(0x00);
    dbi_write_data16(0x00);
	//Negative Gamma Correction
    dbi_write_cmd(0xE1);
    dbi_write_data16(0x00);
    dbi_write_data16(0x15);
    dbi_write_data16(0x17);
    dbi_write_data16(0x07);
    dbi_write_data16(0x11);
    dbi_write_data16(0x06);
    dbi_write_data16(0x2B);
    dbi_write_data16(0x56);
    dbi_write_data16(0x3C);
    dbi_write_data16(0x05);
    dbi_write_data16(0x10);
    dbi_write_data16(0x0F);
    dbi_write_data16(0x3F);
    dbi_write_data16(0x3F);
    dbi_write_data16(0x0F);

	// 需要设置打开背光
	// HAL_TIM_PWM_Start(HTIM_BLK, CHANNEL_BLK);
    // __HAL_TIM_SetCompare(HTIM_BLK, CHANNEL_BLK, 1000);
	
	Reverse_color(0);
	Sleep(0);
	Enter_NormalMode();
	Display(1);
	HAL_Delay(50);
}


static inline void Set_region(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	//Column Address Set(2Ah)
	dbi_write_cmd(0x2A);
	dbi_write_data16_by8(x0);
	dbi_write_data16_by8(x1);
	//Row Address Set(2Bh)
	dbi_write_cmd(0x2b);
	dbi_write_data16_by8(y0);
	dbi_write_data16_by8(y1);

	//Memory Write	
	// -> 该命令用来开始接收数据，并保存至帧内存区；发送任何命令结束帧内存写入
	// -> 当接受该命令时，列寄存器和页寄存器被复位
	dbi_write_cmd(0x2c);
}

#endif
