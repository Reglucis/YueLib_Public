/*****************************************************************************************************
 * @file        MIPI-DBI.h
 * @author      RegLucis
 * @version     V0.1
 * @date        2023-08-09
 * @brief       MIPI-DBI
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @details
 * 		TypeA --> M68 | TypeB --> I80 | TypeC --> SPI
 * 
 * 		提供接口如下:
 * 			dbi_write_cmd			--->	写命令
 * 			dbi_write_data16		--->	写16位数据
 * 			dbi_write_data16To8		--->	以8位长度写16位数据
 * 			Write_data8Tocmd		--->	写8位数据至指定寄存器
 ***************************************************************************************************
 * @bug
 * 		1.TypeA总线未使用过，未编写
 * 		2.TypeC总线没有模块进行测试，只从旧库中Copy过来
 ***************************************************************************************************/
#include "./Sys/compiler/compiler.h"
#include "./User/Device/Screen/Configuration.h"

#ifndef __MIPI_DBI_H__
#define __MIPI_DBI_H__
#include <stdint.h>
//----------- M68 配置 -----------
#if(DBI_BUS_TYPE == 0)

#endif

//----------- I80 配置 -----------
#if (DBI_BUS_TYPE == 1)
/// @note
/// 	FSMC_NEx <----> CSX  (LCD_CS)
/// 	FSMC_Ax  <----> D/CX (LCD_RS)
/// 	FSMC_NWE <----> WRX  (LCD_RD)
/// 	FSMC_NOE <----> RDX  (LCD_WR)

typedef struct
{
    volatile uint16_t ADDR;
    volatile uint16_t DATA;
} LCD_TypeDef_t;

#define LCD_BASE					((0x60000000 + (0x04000000 * (__FSMC_NE__ - 1))) | ((2 << (__FSMC_A__ - 1)) - 1) * 2)
#define LCD                         ((LCD_TypeDef_t *)LCD_BASE)

static FORCE_INLINE void dbi_write_cmd(uint8_t command)
{
	LCD->ADDR = command;
}

static FORCE_INLINE void dbi_write_data16(uint16_t data)
{
	LCD->DATA = data;
}

static FORCE_INLINE void dbi_write_data16_by8(uint16_t data)
{
	LCD->DATA = ((data) >> 8);
	LCD->DATA = ((data) & 0xFF);
}

static FORCE_INLINE void dbi_write_cmd_data8(uint8_t command, uint8_t data)
{
	LCD->ADDR = command;
	LCD->DATA = data;
}

// static inline void dbi_write_cmd_data16(uint8_t command, uint16_t data)
// {
// 	LCD->ADDR = command;
// 	LCD->DATA = ((data) >> 8);
// 	LCD->DATA = ((data) & 0xFF);
// }
#endif

//----------- SPI 配置 -----------
#if (DBI_BUS_TYPE == 2)
#define DMA_ENABLE 1	//DMA启用控制

#define SPI_Instance		 				hspi2
#define Transmit(_pData_, _size_) 			HAL_SPI_Transmit(&SPI_Instance, _pData_, _size_, 0xFFFFFFFFU)
#define Delay(_time_) 		 				HAL_Delay(_time_)

#define ST7789V_CS(x)		 x == 0 ? HAL_GPIO_WritePin(DBI_CS_GPIO_Port,  DBI_CS_Pin,  GPIO_PIN_RESET)\
									: HAL_GPIO_WritePin(DBI_CS_GPIO_Port,  DBI_CS_Pin,  GPIO_PIN_SET)
#define ST7789V_DC(x)		 x == 0 ? HAL_GPIO_WritePin(DBI_DC_GPIO_Port,  DBI_DC_Pin,  GPIO_PIN_RESET)\
									: HAL_GPIO_WritePin(DBI_DC_GPIO_Port,  DBI_DC_Pin,  GPIO_PIN_SET)
#define ST7789V_RST(x)		 x == 0 ? HAL_GPIO_WritePin(DBI_RST_GPIO_Port, DBI_RST_Pin, GPIO_PIN_RESET)\
									: HAL_GPIO_WritePin(DBI_RST_GPIO_Port, DBI_RST_Pin, GPIO_PIN_SET)
#define ST7789V_BLK(x)		 x == 0 ? HAL_GPIO_WritePin(DBI_BLK_GPIO_Port, DBI_BLK_Pin, GPIO_PIN_RESET)\
									: HAL_GPIO_WritePin(DBI_BLK_GPIO_Port, DBI_BLK_Pin, GPIO_PIN_SET)

#endif

///////////////////////////////////////////// DCS 命令 /////////////////////////////////////////////

#define Sleep(_x_)	 				if(_x_) dbi_write_cmd(0x10); else dbi_write_cmd(0x11)
#define Reverse_color(_x_)			if(_x_) dbi_write_cmd(0x21); else dbi_write_cmd(0x20)
#define Display(_x_)	 	 		if(_x_) dbi_write_cmd(0x29); else dbi_write_cmd(0x28)
#define Enter_PartialMode()	 		dbi_write_cmd(0x12)
#define Enter_NormalMode()			dbi_write_cmd(0x13)


/////////////////////////////////////////////  E N D  //////////////////////////////////////////////

#endif

