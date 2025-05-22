/*****************************************************************************************************
 * @file        gcc.h
 * @author      Reglucis
 * @version     V0.1
 * @date        2023/12/16
 * @brief       GCC 编译属性映射
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @details
 *
 *
 ***************************************************************************************************/
#ifndef __ARMCC_VERSION
#ifdef __GNUC__

#ifndef __GCC_COMPILER_MACRO_H__
#define __GCC_COMPILER_MACRO_H__

#define FORCE_INLINE __attribute__((always_inline)) inline
#define PACKING
#define IN_CCM
#define __IN_CCM

#define __COMCOMPILER_RECOGNIZED__

#endif
#endif
#endif