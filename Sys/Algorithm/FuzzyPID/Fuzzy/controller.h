#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "./Sys/DWT/DWT.h"
#include "./Sys/Math/MyMathLib.h"
#include "main.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include <math.h>

#ifndef abs
#define abs(x) ((x > 0) ? x : -x)
#endif

#ifndef user_malloc
#ifdef _CMSIS_OS_H
#define user_malloc pvPortMalloc
#else
#define user_malloc malloc
#endif
#endif

/******************************** FUZZY PID **********************************/
#define PB 3  //  正大(Positive Big)
#define PM 2  //  正中(Positive Medium)
#define PS 1  //  正小(Positive Small)
#define ZE 0  //  零  (Zero)
#define NS -1 //  负小(Negative Small)
#define NM -2 //  负中(Negative Medium)
#define NB -3 //  负大(Negative Big)

typedef struct {
	float KpFuzzy; //  模糊PID控制器的比例增益
	float KiFuzzy; //  模糊PID控制器的积分增益
	float KdFuzzy; //  模糊PID控制器的微分增益

	float (*FuzzyRuleKp)[7]; //  指向模糊规则矩阵的指针，用于计算Kp的模糊规则
	float (*FuzzyRuleKi)[7]; //  指向模糊规则矩阵的指针，用于计算Ki的模糊规则
	float (*FuzzyRuleKd)[7]; //  指向模糊规则矩阵的指针，用于计算Kd的模糊规则

	float KpRatio; //  Kp的比例系数
	float KiRatio; //  Ki的比例系数
	float KdRatio; //  Kd的比例系数

	float eStep;  //  e的步长，用于模糊推理
	float ecStep; //  ec的步长，用于模糊推理

	float e;	 //  当前误差
	float ec;	 //  当前误差变化率
	float eLast; //  上一次的误差

	DWT_Stopwatch_t DWT_CNT; //  DWT计数器，用于记录时间
	float dt;				 //  时间间隔
} FuzzyRule_t;

void Fuzzy_Rule_Init(FuzzyRule_t* fuzzyRule, float (*fuzzyRuleKp)[7], float (*fuzzyRuleKi)[7], float (*fuzzyRuleKd)[7], float kpRatio, float kiRatio, float kdRatio, float eStep, float ecStep);
void Fuzzy_Rule_Implementation(FuzzyRule_t* fuzzyRule, float measure, float ref);

/******************************* PID CONTROL *********************************/
typedef enum pid_Improvement_e {
	NONE = 0X00,						// 0000 0000
	Integral_Limit = 0x01,				// 0000 0001	//  积分限制，用于防止积分项过大导致的积分饱和现象
	Derivative_On_Measurement = 0x02,	// 0000 0010	//  微分项基于测量值，而不是误差值，可以减少噪声对微分项的影响
	Trapezoid_Intergral = 0x04,			// 0000 0100	//  梯形积分，用于提高积分项的精度和减少积分波动
	Proportional_On_Measurement = 0x08, // 0000 1000	//  比例项基于测量值，而不是误差值，可以减少噪声对比例项的影响
	OutputFilter = 0x10,				// 0001 0000	//  输出滤波，用于平滑控制器的输出，减少系统的振荡
	ChangingIntegrationRate = 0x20,		// 0010 0000	//  可变积分率，根据系统的状态动态调整积分项的权重
	DerivativeFilter = 0x40,			// 0100 0000	//  微分滤波，用于减少微分项对噪声的敏感度
	ErrorHandle = 0x80,					// 1000 0000	//  错误处理，用于处理系统中的异常情况，如电机堵转等
} PID_Improvement_e;

typedef enum errorType_e {
	PID_ERROR_NONE = 0x00U,
	Motor_Blocked = 0x01U
} ErrorType_e;

typedef struct {
	uint64_t ERRORCount;
	ErrorType_e ERRORType;
} PID_ErrorHandler_t;

typedef struct pid_t { //  定义一个结构体类型pid_t，用于存储PID控制器的相关参数和状态
	float Ref;		   //  参考值，即目标值
	float Kp;		   //  比例系数
	float Ki;		   //  积分系数
	float Kd;		   //  微分系数

	float Measure;		//  当前测量值
	float Last_Measure; //  上一次的测量值
	float Err;			//  当前误差，即Ref与Measure的差值
	float Last_Err;		//  上一次的误差
	float Last_ITerm;	//  上一次的积分项输出

	float Pout;	 //  比例项输出
	float Iout;	 //  积分项输出
	float Dout;	 //  微分项输出
	float ITerm; //  当前积分项中间值

	float Output;	   //  当前PID控制器输出
	float Last_Output; //  上一次的PID控制器输出
	float Last_Dout;   //  上一次的微分项输出

	float MaxOut;		 //  PID控制器输出的最大限制值
	float IntegralLimit; //  积分限制，用于限制积分项的最大值，防止积分饱和
	float DeadBand;		 //  死区，当误差在死区范围内时，控制器不进行调节
	float ControlPeriod; //  控制周期，即控制器每次调节的时间间隔
	float CoefA;		 // For Changing Integral
	float CoefB;		 // ITerm = Err*((A-abs(err)+B)/A)  when B<|err|<A+B
	float Output_LPF_RC; // RC = 1/omegac
	float Derivative_LPF_RC;

	uint16_t OLS_Order;
	OLS_t OLS;

	DWT_Stopwatch_t DWT_CNT;
	float dt;

	FuzzyRule_t* FuzzyRule;

	uint8_t Improve;

	PID_ErrorHandler_t ERRORHandler;

	void (*User_Func1_f)(struct pid_t* pid);
	void (*User_Func2_f)(struct pid_t* pid);
} PID_t;

void PID_Init(PID_t* pid, float max_out, float intergral_limit, float deadband, float kp, float ki, float kd, float A, float B, float output_lpf_rc, float derivative_lpf_rc, uint16_t ols_order,
			  uint8_t improve);
float PID_Calculate(PID_t* pid, float measure, float ref);

/*************************** 前馈控制器 LINEAR DISTURBANCE OBSERVER *****************************/
typedef struct {
	float c[3];// G(s) = 1/(c2s^2 + c1s + c0)	//  c数组存储传递函数G(s)的系数，其中c[2]对应s^2的系数，c[1]对应s的系数，c[0]对应常数项的系数
	float Ref;					 //  Ref表示参考输入信号
	float Last_Ref;				 //  Last_Ref存储上一次的参考输入信号，用于计算参考输入的变化率
	float DeadBand;				 //  DeadBand表示死区带宽，用于忽略微小的参考输入变化
	DWT_Stopwatch_t DWT_CNT;	 //  DWT_CNT是一个计时器，用于记录时间间隔
	float dt;					 //  dt表示时间间隔，用于计算参考输入的变化率
	float LPF_RC;// RC = 1/omegac//  LPF_RC表示低通滤波器的时间常数RC，其中omegac是截止频率
	float Ref_dot;				 //  Ref_dot表示参考输入信号的一阶导数，即变化率
	float Ref_ddot;				 //  Ref_ddot表示参考输入信号的二阶导数，即加速度
	float Last_Ref_dot;			 //  Last_Ref_dot存储上一次的参考输入信号的一阶导数，用于计算二阶导数
	uint16_t Ref_dot_OLS_Order;	 //  Ref_dot_OLS_Order表示用于计算Ref_dot的最小二乘法（OLS）的阶数
	OLS_t Ref_dot_OLS;			 //  Ref_dot_OLS是一个结构体，用于存储最小二乘法计算Ref_dot的相关参数和结果
	uint16_t Ref_ddot_OLS_Order; //  Ref_ddot_OLS_Order表示用于计算Ref_ddot的最小二乘法（OLS）的阶数
	OLS_t Ref_ddot_OLS;			 //  Ref_ddot_OLS是一个结构体，用于存储最小二乘法计算Ref_ddot的相关参数和结果
	float Output;				 //  Output表示前馈控制器的输出信号
	float MaxOut;				 //  MaxOut表示前馈控制器输出的最大值，用于限制输出信号的幅值
} Feedforward_t;				 

void Feedforward_Init(Feedforward_t* ffc, float max_out, float* c, float lpf_rc, uint16_t ref_dot_ols_order, uint16_t ref_ddot_ols_order);
float Feedforward_Calculate(Feedforward_t* ffc, float ref);

/************************* 线性扰动观测器 LINEAR DISTURBANCE OBSERVER *************************/
typedef struct {
	float c[3]; // G(s) = 1/(c2s^2 + c1s + c0)
	float Measure;
	float Last_Measure;
	float u; // system input
	float DeadBand;
	DWT_Stopwatch_t DWT_CNT;
	float dt;
	float LPF_RC; // RC = 1/omegac
	float Measure_dot;
	float Measure_ddot;
	float Last_Measure_dot;
	uint16_t Measure_dot_OLS_Order;
	OLS_t Measure_dot_OLS;
	uint16_t Measure_ddot_OLS_Order;
	OLS_t Measure_ddot_OLS;
	float Disturbance;
	float Output;
	float Last_Disturbance;
	float Max_Disturbance;
} LDOB_t;

void LDOB_Init(LDOB_t* ldob, float max_d, float deadband, float* c, float lpf_rc, uint16_t measure_dot_ols_order, uint16_t measure_ddot_ols_order);
float LDOB_Calculate(LDOB_t* ldob, float measure, float u);

/*************************** 跟踪微分器 Tracking Differentiator ***************************/
typedef struct {
	float Input;
	float h0;
	float r;
	float x;
	float dx;
	float ddx;
	float last_dx;
	float last_ddx;
	DWT_Stopwatch_t DWT_CNT;
	float dt;
} TD_t;

void TD_Init(TD_t* td, float r, float h0);
float TD_Calculate(TD_t* td, float input);

#endif
