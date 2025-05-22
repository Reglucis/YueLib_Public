// #ifndef _A1_MOTOR_CONTROL_H_
// #define _A1_MOTOR_CONTROL_H_

// #include "stm32h743xx.h"

// #define pi 		3.1415926535f
// #define Reduction_ratio 9.1f

// /*参数范围限制说明

// 用户操作参数针对A1电机输出轴
// 电机实际发送命令参数针对A1电机转子，
// 电机转子和电机输出轴有个减速比-Reduction_ratio

// 针对电机输出轴：用户操作
// 	A1_MOTOR_send.T = 0.0f;			//单位：Nm, |T| < 128
//     A1_MOTOR_send.W = 0.0f;			//单位：rad/s, |W| < (256/Reduction_ratio)=28.13
//     A1_MOTOR_send.Pos = 0.0f;		//单位：rad, |Pos| < (823549/Reduction_ratio)=90499.89
//     A1_MOTOR_send.K_P = 0.0f;		// 0 < K_P < 16
//     A1_MOTOR_send.K_W = 0.0f;		// 0 < K_W < 32

// 针对电机转子：电机实际发送命令
// 	A1_Motor_Tx_Type.T = 0.0f;							//单位：Nm, |T| < 128
//     A1_Motor_Tx_Type.W = 0.0f * Reduction_ratio ;		//单位：rad/s, |W| < 256
//     A1_Motor_Tx_Type.Pos = 0.0f * Reduction_ratio;		//单位：rad, |Pos| < 823549
//     A1_Motor_Tx_Type.K_P = 0.0f;						// 0 < K_P < 16
//     A1_Motor_Tx_Type.K_W = 0.0f;						// 0 < K_W < 32

// */




// /**
//   * @brief  A1电机发送原始数据结构体
//   * @note 	
//   * @param  
//   * @retval None
//   */
// typedef struct { 
// 	uint8_t start_0;	//包头
// 	uint8_t start_1;	//包头
// 	uint8_t motor_ID;	//电机ID-0,1,2,3 \0xBB 表示向所有电机广播（此时无返回）
// 	uint8_t reserved_0;
// 	uint8_t mode;		//电机关节模式选择-电机控制模式，0:空闲, 5:开环缓慢转动, 10:闭环控制
// 	uint8_t ModifyBit;	//电机控制参数修改位
// 	uint8_t ReadBite;	//电机控制参数发送位
// 	uint8_t reserved_1;
// 	uint32_t Modify;	//电机参数修改的数据//COMData32
// 	int16_t T;			//(Nm) 期望关节的输出力矩（电机本身的力矩）x256, 7 + 8 描述//q15_t=int16_t
// 	int16_t W;			//(rad/s) 期望关节速度 （电机本身的速度） x128,       8 + 7描述	//q15_t
// 	int32_t Pos;		//(rad) 期望关节位置 x 16384/6.2832, 14位编码器（主控0点修正，电机关节还是以编码器0点为准）
// 	int16_t K_P;		// 关节刚度系数 x2048  4+11 描述//q15_t
// 	int16_t K_W;		// 关节速度系数 x1024  5+10 描述//q15_t
// 	uint8_t LowHzMotorCmdIndex;	// 电机低频率控制命令的索引, 0-7, 分别代表LowHzMotorCmd中的8个字节
// 	uint8_t LowHzMotorCmdByte;	// 电机低频率控制命令的字节
// 	uint32_t reserved_2;	// 通讯 保留字节  用于实现别的一些通讯内容//COMData32
// 	uint32_t CRCdata;//COMData32
// }A1_Motor_Tx_Type;

// /**
//   * @brief  A1电机接收原始数据结构体
//   * @note 	
//   * @param  
//   * @retval None
//   */
// typedef struct { 
// 	uint8_t start_0;	//COMHead
// 	uint8_t start_1;
// 	uint8_t motor_ID;
// 	uint8_t reserved_0;
// 	uint8_t mode;		// 当前关节模式
// 	uint8_t ReadBit;	// 电机控制参数修改     是否成功位
// 	int8_t Temp;		// 电机当前平均温度   
// 	uint8_t MError;		// 电机错误 标识	
// 	uint32_t Read;		// 读取的当前 电机 的控制数据 //COMDarta32
// 	int16_t T;			// 当前实际电机输出力矩       7 + 8 描述
// 	int16_t W;			// 当前实际电机速度（高速）   8 + 7 描述
// 	int32_t LW;			// 当前实际电机速度（低速）   //float
// 	int16_t W2;			// 当前实际关节速度（高速）   8 + 7 描述
// 	int32_t LW2;		// 当前实际关节速度（低速）   //float
// 	int16_t Acc;		// 电机转子加速度       15+0 描述  惯量较小
// 	int16_t OutAcc;		// 输出轴加速度         12+3 描述  惯量较大
// 	int32_t Pos;		// 当前电机位置（主控0点修正，电机关节还是以编码器0点为准）
// 	int32_t Pos2;		// 关节编码器位置(输出编码器)
// 	int16_t gyro[3];	// 电机驱动板6轴传感器数据
// 	int16_t acc[3];
// 	int16_t Fgyro[3];	// 力传感器的数据   
// 	int16_t Facc[3];
// 	int16_t Fmag[3];
// 	uint8_t Ftemp;
// 	int16_t Fprce16;
// 	int8_t Fprce8;
// 	uint8_t FError;
// 	int8_t reserved_1;	// 通讯 保留字节
// 	uint32_t CRCdata;	//COMData32
// }A1_Motor_Rx_Type;


// /**
//   * @brief  用户操作A1电机发送数据
//   * @note 	//Define the message to be send. 【定义发送数据】
//   * @param  
//   * @retval None
//   */
// typedef struct {
//     A1_Motor_Tx_Type  motor_send_data;  //电机控制数据结构体，详见
//     //The values of motor commands 【待发送的各项数据】
//     uint8_t id;              //Motor ID【电机ID】
//     uint8_t mode;            //The control mode, 0:free, 5:Open loop slow turning, 10:close loop control【电机控制模式，0:空闲, 5:开环缓慢转动, 10:闭环控制】
//     //The following parameters are just motor's parameters, do not concern the reducer. The real torque command to control board is:
//     //【以下参数均为电机本身参数，与减速器无关。实际传递给控制板的指令力矩为：】
//     //K_P*delta_Pos + K_W*delta_W + T
//     float T;                        //Desired output torque of motor【期望电机本身的输出力矩（Nm）】
//     float W;                        //Desired output speed of motor【期望电机本身的速度(rad/s)】
//     float Pos;                      //Desired shaft position of motor【期望电机本身的位置（rad）】
//     float K_P;                      //The position stiffness【电机本身的位置刚度系数】
//     float K_W;                      //The speed stiffness【电机本身的速度刚度系数】

// }A1_MOTOR_send;


// /**
//   * @brief  用户操作A1电机接收数据
//   * @note 	//Define the data structure of received message. 【定义接收数据结构】
//   * @param  
//   * @retval None
//   */
// typedef struct
// {
//     A1_Motor_Rx_Type motor_recv_data;     //The data received from motor. Details are shown in motor_msg.h【电机接收数据结构体，详见motor_msg.h】
//     uint8_t correct;                    //Whether the received data is correct(1:correct, 0:wrong)【接收数据是否完整（1完整，0不完整）】
//     //解读得出的电机数据
//     uint8_t id;         //Motor ID【电机ID】
//     uint8_t mode;             //The control mode, 0:free, 5:Open loop slow turning, 10:close loop control【电机控制模式，0:空闲, 5:开环缓慢转动, 10:闭环控制】
//     int16_t Temp;                       //Temperature【温度】
//     uint8_t MError;           //Error code【错误码】

//     float T;                        //The output torque of motor【当前实际电机输出力矩】
//     float W;                        //The motor shaft speed(without filter)【当前实际电机速度（无滤波器）】
//     float LW;                       //The motor shaft speed(with filter)【当前实际电机速度（有滤波器）】
//     int16_t Acc;                    //The acceleration of motor shaft【电机转子加速度】
    
// 	float Pos;                      //The motor shaft position(control board zero fixed)【当前电机位置（主控0点修正，电机关节还是以编码器0点为准）】
// 	float Pos_init;
// 	float Pos_now;
// 	float Pos_last;
// 	int16_t Pos_count;	
	
//     float gyro[3];                  //The data of 6 axis inertial sensor on the control board【电机驱动板6轴传感器数据】
//     float acc[3];

// }A1_MOTOR_recv;


// /**
//   * @brief  用户操作A1电机数据
//   * @note 	
//   * @param  
//   * @retval None
//   */
// typedef struct
// {
// 	A1_MOTOR_send tx;
// 	A1_MOTOR_recv rx;
    
// }A1_Motor_Type;

// /**
//   * @brief  结构体声明
//   * @note 	
//   * @param  
//   * @retval None
//   */
// extern A1_Motor_Type a1_dat_1;
// extern A1_Motor_Type a1_dat_2;


// /**
//   * @brief  A1电机所有数据Init
//   * @note 	
//   * @param  
//   * @retval None
//   */
// void USER_A1_ALL_Data_Init(void);

// /**
//   * @brief  A1电机发送数据函数
//   * @note 	
//   * @param  ID:电机ID
//   * @param  Mode:电机模式
//   * @param  T:
//   * @param  W:
//   * @param  P:
//   * @param  KP:
//   * @param  KW:
//   * @retval None
//   */
// void USER_A1_Data_Send(uint8_t ID,uint8_t Mode,float T,float W,float P,float KP,float KW);

// /**
//   * @brief  A1电机接收数据转换处理
//   * @note 	
//   * @param  buf:要写入的数组地址
//   * @param  a1_dat:数据结构体
//   * @retval None
//   */
// void USER_A1_RX_Data_update(uint8_t *buf, A1_Motor_Type *a1_dat);


// #endif

