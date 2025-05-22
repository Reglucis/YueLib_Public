#ifndef __RMD_MOTOR_H__
#define __RMD_MOTOR_H__

#include "stm32f4xx_hal.h"



void MOTOR_ctrl(uint32_t ID, uint8_t CMD, int16_t current);

#endif
