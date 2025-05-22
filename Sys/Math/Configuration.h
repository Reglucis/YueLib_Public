/*****************************************************************************************************
 * @file        Configuration.h
 * @author      RegLucis
 * @version     V2.0
 * @date        2023-12-20
 * @brief
 * @email		RegLucis@outlook.com
 ****************************************************************************************************
 * @warning		This file must be edited(saved) in GB-18030 encoding.
 * @details
 ***************************************************************************************************
 * @bug
 ***************************************************************************************************/
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
#ifndef __MATH_LIB__
#define __MATH_LIB__

// <q.0> CMSIS-DSP 
#define CMSIS_DSP_ENABLE 1

// <q.0> 基础数学运算库
#define MATH_BASICLIB_ENABLE 1

// <q.0> 基础数学运算库
#define MATH_VECTOR3D_ENABLE 1

// <q.0> 普通最小二乘库
#define MATH_ORDINARY_LEAST_SQUARES_ENABLE 1

// <q.0> 递归最小二乘库
#define MATH_RECURSIVE_LEAST_SQUARES_ENABLE 0

// <q.0> 导航算法库
#define MATH_NAVIGATION_ENABLE 1

// <e> 随机数生成库
// <i> 暂未支持
// TODO 随机数生成库未适配
#define MATH_RANDOMNUM_ENABLE 0
	// <q.0> 硬件随机数生成器使能
	#define MATH_RANDOMNUM_ENABLE 0
// </e>

// <q.0> 矩阵运算库
#define MATH_Matrix_ENABLE 0

//------------- <<< end of configuration section >>> -----------------------
#endif
