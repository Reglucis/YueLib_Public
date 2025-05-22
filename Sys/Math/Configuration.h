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

// <q.0> ������ѧ�����
#define MATH_BASICLIB_ENABLE 1

// <q.0> ������ѧ�����
#define MATH_VECTOR3D_ENABLE 1

// <q.0> ��ͨ��С���˿�
#define MATH_ORDINARY_LEAST_SQUARES_ENABLE 1

// <q.0> �ݹ���С���˿�
#define MATH_RECURSIVE_LEAST_SQUARES_ENABLE 0

// <q.0> �����㷨��
#define MATH_NAVIGATION_ENABLE 1

// <e> ��������ɿ�
// <i> ��δ֧��
// TODO ��������ɿ�δ����
#define MATH_RANDOMNUM_ENABLE 0
	// <q.0> Ӳ�������������ʹ��
	#define MATH_RANDOMNUM_ENABLE 0
// </e>

// <q.0> ���������
#define MATH_Matrix_ENABLE 0

//------------- <<< end of configuration section >>> -----------------------
#endif
