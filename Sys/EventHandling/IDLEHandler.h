#ifndef __IDLEHANDLER_H__
#define __IDLEHANDLER_H__

#include "stm32f4xx_hal.h"

typedef enum {
	IDLE_HANDLER_CANCEL_LASTOPERATION = 0,
	IDLE_HANDLER_CANCEL_THISOPERATION = 1,
	IDLE_HANDLER_ADD_NEW			  = 2
} IDLEHandlerMode_e;

void IDLEHandler_AddToQueue(void* handler, void* param, uint32_t paramSize, uint32_t delay, IDLEHandlerMode_e repetitiveBehavior);
void IDLEHandler_Process(void);

#endif
