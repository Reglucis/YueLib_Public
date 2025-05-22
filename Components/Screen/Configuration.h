/*****************************************************************************************************
 * @file        Screen.h
 * @author      RegLucis
 * @version     V2.0
 * @date        2023-12-20
 * @brief       
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @warning		This file must be edited(saved) in GB-18030 encoding.
 * @details 	
 ***************************************************************************************************
 * @bug 		
 ***************************************************************************************************/
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
#ifndef __Screen__
#define __Screen__
// <h> 面板参数
	// <h> 面板分辨率
		// <o> 横向像素数量
		#define Screen_W   320
		// <o> 纵向像素数量
		#define Screen_H   480
	// </h>

	// <o> 刷新率
	// <i> 单位: Hz
	// <i> 该项目前无任何作用 
	#define Screen_Rate 60
// </h>

// <h> 显示方向
	// <o > 屏幕方向	
	// 		<0=> 竖屏模式
	// 		<1=> 竖屏模式(180°)
	// 		<2=> 横屏模式
	//		<3=> 横屏模式(180°)
	#define SCREEN_ROTATION 0
	// <q> 水平镜像
	#define HORIZONTAL_MIRRORING 	1
	// <q> 垂直镜像
	#define VERTICAL_MIRRORING 		0
	// <q> 行列交换
	#define ROW_COLUMN_EXCHANGE 	0
// </h>

// <h> 屏幕驱动方式
	// <e> DBI
	#define DBI_BUS 1
		// <o DBI_BUS_TYPE> DBI 总线协议
		// 		<0=> TypeA(M68)
		// 		<1=> TypeB(I80)
		// 		<2=> TypeC(SPI)
		// <i> 选择 DBI 驱动方式的总线传输协议
		#define DBI_BUS_TYPE 1
		
		// <h> TypeA Configuration
			// <n> 目前未接触过 M68 总线驱动的屏幕, 故暂未编写
		// </h>

		// <h> TypeB Configuration
			// <o> FSMC 片选 <1-4>
			#define __FSMC_NE__               	1 
			// <o> FSMC 命令/数据映射地址 <16-23>
			#define __FSMC_A__                	19
		// </h>

		// <h> TypeC Configuration
			// <n> 偷懒, 没对 SPI 总线进行适配
		// </h>

		// <o DBI_BUS_TYPE> DBI 总线协议
		// 		<0=> ST7789
		// 		<1=> ILI9341
		// 		<2=> ILI9486
		// <i> 选择 DBI 驱动方式的总线传输协议
		#define SCREEN_DRIVER 2 
	// </e>
	
	// <e> DPI
		#define DPI_BUS 0
	// </e>

	// <e> DSI
		#define DSI_BUS 0  
	// </e>
// </h>

//------------- <<< end of configuration section >>> -----------------------

// 物理分辨率映射为逻辑分辨率
#if	  ( SCREEN_ROTATION == 0 ||  SCREEN_ROTATION == 1 )
	#define	LOGIC_W	Screen_W
	#define LOGIC_H	Screen_H
#elif ( SCREEN_ROTATION == 2 ||  SCREEN_ROTATION == 3 )
	#define	LOGIC_W	Screen_H
	#define LOGIC_H	Screen_W
#else
	#error "SCREEN_ROTATION must be 0,1,2,3"
#endif


// 选择包括的头文件
#if	  (DBI_BUS)
#include "./User/Device/Screen/AbstractionLayer/MIPI/MIPI-DBI.h"
#elif (DPI_BUS)
#include "./Device/Screen/AbstractionLayer/MIPI/MIPI-DPI.h"
#elif (DSI_BUS)
#include "./Device/Screen/AbstractionLayer/MIPI/MIPI-DSI.h"
#else
#error "You must be selected only one from {DBI_BUS, DPI_BUS and DSI_BUS}!"
#endif

// 选择使用的控制器
#if   (SCREEN_DRIVER  == 0)
#include "./Device/Screen/AbstractionLayer/Chip/ST7789.h"
#elif (SCREEN_DRIVER  == 1)
#include "./Device/Screen/AbstractionLayer/Chip/ILI9341.h"
#elif (SCREEN_DRIVER  == 2)
#include "./User/Device/Screen/AbstractionLayer/Chip/ILI9486.h"
#else
#error "Unsupported screen driver"
#endif

#endif
