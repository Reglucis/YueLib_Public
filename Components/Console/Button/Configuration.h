/*****************************************************************************************************
 * @file		Configuration.h
 * @author		Reglucis
 * @version		V1.0
 * @date		2025-01-16
 * @brief		按键参数配置
 * @email		Reglucis@outlook.com	
 ****************************************************************************************************
 * @warning		This file must be saved as GB2312 format, otherwise, the Chinese characters will be 
 * 				garbled in the Keil Configuration Wizard.
 * 			
 * 		
 ***************************************************************************************************/
#ifndef __BUTTON_CONFIGURATION__
#define __BUTTON_CONFIGURATION__
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
// <h> 按键参数配置
	// <o> 消抖心跳次数
	#define DESHAKE_REPEAT_TIMES 5

	// <o> 长按激活时间
	// <i> 单位: ms
	#define LONG_PRESS_TIME 500

	// <o> 双击超时时间
	// <i> 单位: ms
	#define DOUBLE_CLICK_TIMEOUT 200
// </h>
//------------- <<< end of configuration section >>> -----------------------

#endif
