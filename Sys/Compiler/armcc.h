/*****************************************************************************************************
 * @file        armcc.h
 * @author      Reglucis
 * @version     V0.1
 * @date        2023/12/16
 * @brief       ARMCC 编译属性映射
 * @email		Reglucis@outlook.com
 ****************************************************************************************************
 * @details 	
 * 			
 * 		
 ***************************************************************************************************/
#ifdef __ARMCC_VERSION

#ifndef __ARMCC_COMPILER_MACRO_H__
#define __ARMCC_COMPILER_MACRO_H__


#define FORCE_INLINE		__attribute__((always_inline))
#define PACKING				__attribute__((packed))
#define IN_CCM				__attribute__((section (".CCM_RAM")))
#define __IN_CCM			__attribute__((section (".CCM_RAM")))




#define __COMCOMPILER_RECOGNIZED__

#endif
#endif
