/*****************************************************************************************************
 * @file        BspUART.h
 * @author      RegLucis
 * @version     V2.1
 * @date        2023-11-17
 * @brief       串口高级通信功能实现
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @details
 * 定义 NODEBUG 以禁用调试输出
 *
 * Time Line:
 * V2.1	更新宏函数, 增加宏函数绘图功能; 增加调试输出控制
 *
 *  ***************************************************************************************************
 * @bug
 *
 ***************************************************************************************************/

#ifndef __BSPUART_H__
#define __BSPUART_H__

#include "stm32f4xx_hal.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ////    配  置  区    //// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_UART_ID		  1		  // 调试信息输出串口
#define POOL_SIZE			  3 * 512 // 输出池默认大小(单位: byte)
#define ENABLE_DMA_THERSHOLED 0x08	  // 定义启用 DMA 发送信息的阈值
#define ENABLE_UART7_UART8	  0		  // UART7&8 使能控制, 默认不使用
#define IDLE_RXBUFFER_SIZE	  50	  // 定义空闲接收缓冲区长度

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ////  非  配  置  区  //// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------- 宏 命 令 区 -----------------------------------------------------------*/
#define __check_printf_format__(a, b) __attribute__((format(printf, a, b)))

/*------------------------------------------------------------定义数据类型------------------------------------------------------------*/
typedef struct {
	uint32_t Length;  // 字符串长度
	uint8_t Buffer[]; // 缓冲区
} UartMessage_t;

typedef void (*UART_TxAction)();
typedef void (*UART_RxAction)(UartMessage_t* message);

/*------------------------------------------------------------ 函数声明 ------------------------------------------------------------*/

int32_t UART_InitTrans(UART_HandleTypeDef* huart);
void UART_Transmit(UART_HandleTypeDef* huart, uint8_t* data, uint32_t length);
int32_t __printf_UART(const char* pStr, ...);
void HalloWorld();

int32_t SubscribeEvent_UartTransmit(UART_HandleTypeDef* huart, UART_TxAction EventHandler);
int32_t SubscribeEvent_UartReceive(UART_HandleTypeDef* huart, uint32_t length, UART_RxAction EventHandler);

void Anotc_SendEulerOrientation(int16_t roll, int16_t pitch, int16_t yaw);
void Anotc_SendQuatOrientation(int16_t q0, int16_t q1, int16_t q2, int16_t q3);
#ifndef NODEBUG

int32_t __printf_UART(const char* pStr, ...) __check_printf_format__(1, 2);

/********************************************************************
 * @brief		在指定绘图窗绘制曲线
 * @param		title:	绘图窗
 * @param		fmt:	数据格式
 * @param		args:	变参
 * @example		Plot(plotter, "%d, %d, %.2f", data1, data2, data3);
 ********************************************************************/
#define Plot(title, fmt, ...) __printf_UART("{" #title "}" fmt "\r\n", ##__VA_ARGS__)
// #define Plot(title, fmt, ...) 	__printf_UART("<%d>{"#title"}"fmt"\r\n", HAL_GetTick(), ##__VA_ARGS__)
/********************************************************************
 * @brief		调试信息输出, 使用方法等价于printf
 ********************************************************************/
#define Debug_printf(fmt, ...)	 __printf_UART(fmt, ##__VA_ARGS__)
#define Debug_Transmit(ptr, len) __Transmit_UART(ptr, len)

/********************************************************************
 * @brief		调试断言
 ********************************************************************/
#define Debug_Assert(condition)                                                   \
	while (condition) {                                                           \
		Debug_printf("Assertion holds at %d of file '%s'\n", __LINE__, __FILE__); \
		\                                                                         \
	}
#else

static inline int no_printf(const char* fmt, ...) __check_printf_format__(1, 2);
static inline int no_printf(const char* fmt, ...)
{
	return 0;
}
#define Plot(title, fmt, ...)	no_printf("<%d>{" #title "}" fmt "\n", HAL_GetTick(), ##__VA_ARGS__)
#define Debug_printf(fmt, ...)	no_printf(fmt, ##__VA_ARGS__)
#define Debug_Assert(condition) NULL

#endif

#endif
