/*****************************************************************************************************
 * @file
 * @author		Reglucis
 * @version		V0.1
 * @date
 * @brief
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @details
 *
 *
 ***************************************************************************************************/

#ifndef __BMI088DRIVER_H__
#define __BMI088DRIVER_H__

#include <stdint.h>

#include "main.h"

#include "./Components/BMI088/Core/BMI088_RegList.h"
#include "./Sys/DataStructure/IMU.h" // 需要符合标准

#define BMI088_SPI hspi1

/*------------------------------------------------------------ 变量类型 ------------------------------------------------------------*/

typedef enum {
	BMI088_NO_ERROR						= 0x00,
	BMI088_ACC_PWR_CTRL_ERROR			= 0x01,
	BMI088_ACC_PWR_CONF_ERROR			= 0x02,
	BMI088_ACC_CONF_ERROR				= 0x03,
	BMI088_ACC_SELF_TEST_ERROR			= 0x04,
	BMI088_ACC_RANGE_ERROR				= 0x05,
	BMI088_INT1_IO_CTRL_ERROR			= 0x06,
	BMI088_INT_MAP_DATA_ERROR			= 0x07,
	BMI088_GYRO_RANGE_ERROR				= 0x08,
	BMI088_GYRO_BANDWIDTH_ERROR			= 0x09,
	BMI088_GYRO_LPM1_ERROR				= 0x0A,
	BMI088_GYRO_CTRL_ERROR				= 0x0B,
	BMI088_GYRO_INT3_INT4_IO_CONF_ERROR = 0x0C,
	BMI088_GYRO_INT3_INT4_IO_MAP_ERROR	= 0x0D,

	BMI088_SELF_TEST_ACCEL_ERROR = 0x80,
	BMI088_SELF_TEST_GYRO_ERROR	 = 0x40,
	BMI088_NO_SENSOR			 = 0xFF,
} BMI088_ERROR_CODE;

typedef struct {
	uint8_t reg;   // 寄存器地址
	uint8_t value; // 寄存器值
	uint8_t error; // 错误代码
} bmi088_InitUnit_t;

/*------------------------------------------------------------ 函数声明 ------------------------------------------------------------*/

IMU_t* BMI088_New(const bmi088_InitUnit_t* accelConfigTable, uint32_t accelTableSize, const bmi088_InitUnit_t* gyroConfigTable, uint32_t gyroTableSize, double phi);
void BMI088_AsynRead(IMU_t* bmi088);
void BMI088_SyncRead(IMU_t* bmi088);

#endif
