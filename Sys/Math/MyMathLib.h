/*****************************************************************************************************
 * @file		MyMathLib.h
 * @author		Reglucis
 * @version		V0.1
 * @date		2025-01-18
 * @brief		数学库头文件
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @details
 *
 *
 ***************************************************************************************************/

#ifndef __MYMATHLIB_H__
#define __MYMATHLIB_H__
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "./Sys/Math/Configuration.h"

#if (CMSIS_DSP_ENABLE == 1)
#include "arm_math.h" // 基础运算库
#endif
#include <math.h>

#include "./Sys/Compiler/Compiler.h"
#include "./Sys/Math/Configuration.h"

#if (MATH_BASICLIB_ENABLE == 1)
#include "./Sys/Math/MathLib/Basic.h" // 基础运算库
#endif

#if(MATH_VECTOR3D_ENABLE == 1)
#include "./Sys/Math/MathLib/Vector3d.h"	// 三维矢量数学库
#endif

#if (MATH_ORDINARY_LEAST_SQUARES_ENABLE == 1)
#include "./Sys/Math/MathLib/OLS.h" // 普通最小二乘库	Ordinary Least Squares
#endif

#if (MATH_RECURSIVE_LEAST_SQUARES_ENABLE == 1)
#include "./Sys/Math/MathLib/RLS.h" // 递归最小二乘库	Recursive Least Squares
#endif

#if(MATH_NAVIGATION_ENABLE == 1)
#include "./Sys/Math/MathLib/Navigation.h"	// 导航数学库
#endif

#if (MATH_RANDOMNUM_ENABLE == 1)
#include "./Sys/Math/MathLib/RandomNum.h" // 随机数生成库
#endif

#if (MATH_Matrix_ENABLE == 1)
#include "./Sys/Math/MathLib/Matrix.h"
#endif

#endif
