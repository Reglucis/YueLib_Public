/*****************************************************************************************************
 * @file        compiler.h
 * @author      Reglucis
 * @version     V0.1
 * @date        2023/12/16
 * @brief       编译器属性映射
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @details 	
 * 			
 * 		
 ***************************************************************************************************/
#ifndef __COMCOMPILER_H__
#define __COMCOMPILER_H__

// 引用全部编译器映射
#include "armcc.h"
#include "gcc.h"
#include "msvc.h"

#define RedLED_Pin GPIO_PIN_5
#define RedLED_GPIO_Port GPIOE
#define GreenLED_Pin GPIO_PIN_6
#define GreenLED_GPIO_Port GPIOE
#define GreenLED_ON()		HAL_GPIO_WritePin(GreenLED_GPIO_Port, GreenLED_Pin, GPIO_PIN_RESET)
#define RedLED_ON()			HAL_GPIO_WritePin(RedLED_GPIO_Port, RedLED_Pin, GPIO_PIN_RESET)
#define GreenLED_OFF()		HAL_GPIO_WritePin(GreenLED_GPIO_Port, GreenLED_Pin, GPIO_PIN_SET)
#define RedLED_OFF()		HAL_GPIO_WritePin(RedLED_GPIO_Port, RedLED_Pin, GPIO_PIN_SET)

// 没有编译器被识别, 防止 vscode 报错
#ifndef __COMCOMPILER_RECOGNIZED__				
#error "No Compiler Recognized"

#define FORCE_INLINE
#define PACKING	
#define IN_CCM		
#define __IN_CCM	




#endif
#endif












