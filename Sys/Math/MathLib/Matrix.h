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
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "./Sys/Math/MyMathLib.h"

typedef float MatrixType;
typedef struct {
	uint32_t rowNum;	// 行数	约定：row -> 第几行，column -> 第几列
	uint32_t columnNum; // 列数 约定：rowNum -> 共几行，columnNum -> 共几列
	MatrixType data[];
} Matrix_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ////    配  置  区    //// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ////  非  配  置  区  //// ⬇ ⬇ ⬇ ⬇ ⬇ ⬇ ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------ 变量类型 ------------------------------------------------------------*/
#define SAFE_CHECK 1
/*------------------------------------------------------------ 函数声明 ------------------------------------------------------------*/
int32_t Matrix_GetAliveNum();
Matrix_t* Matrix_New(uint32_t rowNum, uint32_t columnNum);
Matrix_t* Matrix_NewEye(uint32_t dimension);
Matrix_t* Matrix_Copy(Matrix_t* pMatrix);
void Matrix_Delete(Matrix_t* pMatrix);
void inline Matrix_SetValue(Matrix_t* pMatrix, MatrixType* pValue);
void inline Matrix_Clear(Matrix_t* pMatrix);
void inline Matrix_SetOnes(Matrix_t* pMatrix, MatrixType value);
void Matrix_printf(Matrix_t* pMatrix);

void Matrix_Add(Matrix_t* summand1, Matrix_t* summand2, Matrix_t* sum);
void Matrix_Product(Matrix_t* leftpMatrix, Matrix_t* rightpMatrix, Matrix_t* product);
void Matrix_ScalarMul(MatrixType scalar, Matrix_t* matrix, Matrix_t* res);


#endif
