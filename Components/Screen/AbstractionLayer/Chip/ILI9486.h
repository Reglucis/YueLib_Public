/*****************************************************************************************************
 * @file        ILI9486.h
 * @author      RegLucis
 * @version     V1.0
 * @date        2023-08-09
 * @brief       驱动控制器
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @details 	
 * 		
 ***************************************************************************************************
 * @bug 		
 ***************************************************************************************************/
#include "./User/Device/Screen/Configuration.h"
#include "stm32f4xx_hal.h"

#ifndef __ILI9486__
#define __ILI9486__

#define screen_init	Init_ILI9486
static void Init_ILI9486(void)
{
	#if  (SCREEN_ROTATION == 0)    
		dbi_write_cmd_data8(0x36, 0x08 | VERTICAL_MIRRORING << 7 | HORIZONTAL_MIRRORING << 6 | ROW_COLUMN_EXCHANGE << 5);
	#elif(SCREEN_ROTATION == 1)    
		dbi_write_cmd_data8(0x36, 0xC8);
	#elif(SCREEN_ROTATION == 2)    
		dbi_write_cmd_data8(0x36, 0x78);
	#else    
		dbi_write_cmd_data8(0x36, 0xA8);
	#endif


	dbi_write_cmd_data8(0x3A, 0x05);
	
	dbi_write_cmd_data8(0xB4, 0x00);
	dbi_write_cmd_data8(0xC1, 0x41);


	dbi_write_cmd(0xC5); 
	dbi_write_data16(0x00); 
	dbi_write_data16(0x18); 


	dbi_write_cmd(0xE0); 
	dbi_write_data16(0x0F); 
	dbi_write_data16(0x1B); 
	dbi_write_data16(0x18); 
	dbi_write_data16(0x0B); 
	dbi_write_data16(0x0E); 
	dbi_write_data16(0x09); 
	dbi_write_data16(0x47); 
	dbi_write_data16(0x94); 
	dbi_write_data16(0x35); 
	dbi_write_data16(0x0A); 
	dbi_write_data16(0x13); 
	dbi_write_data16(0x05); 
	dbi_write_data16(0x08); 
	dbi_write_data16(0x03); 
	dbi_write_data16(0x00); 
	dbi_write_cmd(0XE1); 
	dbi_write_data16(0x0F); 
	dbi_write_data16(0x3A); 
	dbi_write_data16(0x37); 
	dbi_write_data16(0x0B); 
	dbi_write_data16(0x0C); 
	dbi_write_data16(0x05); 
	dbi_write_data16(0x4A); 
	dbi_write_data16(0x24); 
	dbi_write_data16(0x39); 
	dbi_write_data16(0x07); 
	dbi_write_data16(0x10); 
	dbi_write_data16(0x04); 
	dbi_write_data16(0x27); 
	dbi_write_data16(0x25); 
	dbi_write_data16(0x00); 

	// 需要设置打开背光
	// HAL_TIM_PWM_Start(HTIM_BLK, CHANNEL_BLK);
    // __HAL_TIM_SetCompare(HTIM_BLK, CHANNEL_BLK, 1000);
	// HAL_GPIO_WritePin(screen_blk_GPIO_Port, screen_blk_Pin, GPIO_PIN_SET);
	
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