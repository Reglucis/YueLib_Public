/*****************************************************************************************************
 * @file		button.h
 * @author		Reglucis
 * @version		V0.2
 * @date		2025/1/16
 * @brief		按键驱动层支持
 * @email		Reglucis@outlook.com	
 ****************************************************************************************************
 * @detail
 * 			
 * 		
 ***************************************************************************************************/

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdint.h>
#include "stm32f4xx_hal.h"

#include "./Components/Console/Button/ButtonMiddleware.h"
/*------------------------------------------------------------ 变量类型 ------------------------------------------------------------*/
typedef struct __AbstractButton__ AbstractButton_t;
typedef void (*BTN_Action)(AbstractButton_t* object);

typedef struct {
	BTN_Action KeyDown_EventHandler;
	BTN_Action KeyUp_EventHandler;
	BTN_Action KeyClick_EventHandler;
	BTN_Action KeyDClick_EventHandler;
	BTN_Action KeyHold_EventHandler;
} BTN_EventHandler_t;
/*------------------------------------------------------------ 函数声明 ------------------------------------------------------------*/
void BTN_Init(void* object, BTN_EventHandler_t* event_handler);
void BTN_Task(void);

#endif
