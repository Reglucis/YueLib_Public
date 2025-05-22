#ifndef __P_I_D__
#define __P_I_D__

#define COEFFICIENT_TYPE float // 定义算法所使用的数据类型

#include "stm32f4xx_hal.h"

typedef struct
{
	/* 控制系数 */
	COEFFICIENT_TYPE ff;
	COEFFICIENT_TYPE kp; // Proportional 比例系数
	COEFFICIENT_TYPE ki; // Integral 	 积分系数
	COEFFICIENT_TYPE kd; // Derivative 	 微分系数
	/* 限幅 */
	COEFFICIENT_TYPE maxIout;
	COEFFICIENT_TYPE maxOut;
	/* 死区 */
	COEFFICIENT_TYPE deadband;
} PID_t;

typedef struct
{
	float measureValue;
	float dt;
} PIDInput_t;

struct __SystemState;
typedef struct __SystemState SystemState_t;

struct __PIDController;
typedef struct __PIDController PIDController_t;

typedef PIDInput_t (*Plant_InputHandler)(void* device);
typedef void (*Plant_OutputHandler)(void* device, float output);

PIDController_t* PID_New(PID_t* pid, void* device, uint32_t ols_order, Plant_InputHandler inputHandler, Plant_OutputHandler outputHandler);
void* PID_GetDevice(PIDController_t* controller);
void PID_SetTargetValue(PIDController_t* controller, float tagetValue);
void PID_AbsoulteCalc(PIDController_t* controller);
void PID_IncrementalCalc(PIDController_t* controller);
void PID_DebugPrint(PIDController_t* controller);

#endif
