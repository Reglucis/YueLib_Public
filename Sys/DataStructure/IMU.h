/*****************************************************************************************************
 * @file		
 * @author		Reglucis
 * @version		V0.1
 * @date		
 * @brief		
 * @email		Reglucis@outlook.com	
 ****************************************************************************************************
 * @details 	
 * 				合同: 不关心惯性导航单元是什么，但是所有惯性导航单元必须实现下方数据结构(接口)
 * 		
 ***************************************************************************************************/
#include <stdint.h>

#ifndef __IMU_DATASTRUCTURE_H__
#define __IMU_DATASTRUCTURE_H__

// 陀螺仪认为是正态分布, 对其均值进行修正
// TODO: 陀螺仪椭圆校准
// 加速度计通过重力加速度进行校准

typedef struct {
	// 解算数据
	float accel[3];
	float gyro[3];
	float temperature;
	// 配置的量程(灵敏度/分辨率)
	float accelSensitivity;
	float gyroSensitivity;
	// 校准数据
	float tempWhenCali;
	float gyroOffset[3];	// 
	float accelScale;		// g 标定值
	float gravity;
	// 原始数据
	uint8_t rawData[20];
	// 更新标志
	uint32_t updateFlag;
} IMU_t;

/* 用于修正安装误差的参数 */
typedef struct {
	uint8_t flag;

	float scale[3];

	float Yaw;
	float Pitch;
	float Roll;
} IMU_Param_t;

#endif


