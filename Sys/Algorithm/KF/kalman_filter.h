#ifndef __KALMAN_FILTER_H__
#define __KALMAN_FILTER_H__


#include "stm32f407xx.h"
#include "./Sys/Math/MyMathLib.h"

#define matrix arm_matrix_instance_f32
#define MATRIX_DATA_SIZE sizeof(float)
#define Matrix_Init		 arm_mat_init_f32
#define Matrix_Add		 arm_mat_add_f32
#define Matrix_Subtract	 arm_mat_sub_f32
#define Matrix_Multiply	 arm_mat_mult_f32
#define Matrix_Transpose arm_mat_trans_f32
#define Matrix_Inverse	 arm_mat_inverse_f32

typedef struct kf_t {
	float* FilteredValue;
	float* MeasuredVector;
	float* ControlVector;

	uint8_t xhatSize;
	uint8_t uSize;
	uint8_t zSize;

	uint8_t UseAutoAdjustment;
	uint8_t MeasurementValidNum;

	uint8_t* MeasurementMap;	  // 量测与状态的关系 how measurement relates to the state
	float* MeasurementDegree;	  // 测量值对应H矩阵元素值 elements of each measurement in H
	float* MatR_DiagonalElements; // 量测方差 variance for each measurement
	float* StateMinVariance;	  // 最小方差 避免方差过度收敛 suppress filter excessive convergence
	uint8_t* temp;

	// 配合用户定义函数使用,作为标志位用于判断是否要跳过标准KF中五个环节中的任意一个
	uint8_t SkipEq1, SkipEq2, SkipEq3, SkipEq4, SkipEq5;

	// definiion of struct mat: rows & cols & pointer to vars
	matrix xhat;	  // x(k|k)
	matrix xhatminus; // x(k|k-1)
	matrix u;		  // control vector u
	matrix z;		  // measurement vector z
	matrix P;		  // covariance matrix P(k|k)
	matrix Pminus;	  // covariance matrix P(k|k-1)
	matrix F, FT;	  // state transition matrix F FT
	matrix B;		  // control matrix B
	matrix H, HT;	  // measurement matrix H
	matrix Q;		  // process noise covariance matrix Q
	matrix R;		  // measurement noise covariance matrix R
	matrix K;		  // kalman gain  K
	matrix S, temp_matrix, temp_matrix1, temp_vector, temp_vector1;

	int8_t MatStatus;

	// 用户定义函数,可以替换或扩展基准KF的功能
	void (*User_Func0_f)(struct kf_t* kf, void* userData);
	void (*User_Func1_f)(struct kf_t* kf, void* userData);
	void (*User_Func2_f)(struct kf_t* kf, void* userData);
	void (*User_Func3_f)(struct kf_t* kf, void* userData);
	void (*User_Func4_f)(struct kf_t* kf, void* userData);
	void (*User_Func5_f)(struct kf_t* kf, void* userData);
	void (*User_Func6_f)(struct kf_t* kf, void* userData);
} KalmanFilter_t;

KalmanFilter_t* KalmanFilter_New(uint8_t xhatSize, uint8_t uSize, uint8_t zSize);
// void Kalman_Filter_Measure(KalmanFilter_t* kf);
// void Kalman_Filter_xhatMinusUpdate(KalmanFilter_t* kf);
// void Kalman_Filter_PminusUpdate(KalmanFilter_t* kf);
// void Kalman_Filter_SetK(KalmanFilter_t* kf);
// void Kalman_Filter_xhatUpdate(KalmanFilter_t* kf);
// void Kalman_Filter_P_Update(KalmanFilter_t* kf);
float* KalmanFilter_Update(KalmanFilter_t* kf, void* userData);

#endif
