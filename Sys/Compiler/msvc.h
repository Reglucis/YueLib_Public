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
#ifdef _MSC_VER

#ifndef __MSVC_COMPILER_MACRO_H__
#define __MSVC_COMPILER_MACRO_H__

#define Debug_printf printf

#define FORCE_INLINE inline
#define PACKING
#define IN_CCM
#define __IN_CCM

#define __COMCOMPILER_RECOGNIZED__

#endif
#endif