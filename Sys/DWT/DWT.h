#ifndef __DWT_DELAY__
#define __DWT_DELAY__

#include "stm32f4xx_hal.h"

typedef struct {
	uint32_t DWT_Count;
	uint32_t HAL_Time;
	// 秒表用临时变量
	uint32_t temp;
	uint32_t diff;
} DWT_Stopwatch_t;

void DWT_Init(void);
void DWT_Delayus(uint32_t us);
void DWT_Delayms(uint32_t ms);
void DWT_Delay(uint32_t s);
void DWT_Stopwatch_start(DWT_Stopwatch_t* stopwatch);
float DWT_Stopwatch_stop(DWT_Stopwatch_t* stopwatch);

/********************************************************************
 * @brief		DWT 秒表记圈
 * @param		stopwatch: [IN] 秒表结构体指针
 * @return		 (单位: (2^32 / SysClockFreq) S)
 * @attention	该函数只允许 DWT.CYCCNT 溢出一次
 ********************************************************************/
static inline uint32_t DWT_Stopwatch_split(DWT_Stopwatch_t* stopwatch)
{
	stopwatch->temp = DWT->CYCCNT;
	stopwatch->diff = stopwatch->temp - stopwatch->DWT_Count;
	stopwatch->DWT_Count = stopwatch->temp;
	return stopwatch->diff;
}

#endif
