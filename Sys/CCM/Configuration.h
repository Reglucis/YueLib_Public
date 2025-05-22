
#ifndef __Core_Coupled_Memory_CONFIGURATION__
#define __Core_Coupled_Memory_CONFIGURATION__

#define CCM_ADDR 	0x10000000		// CCM_RAM_ADDR = 0x1000 0000 ~ 0x1000 FFFF
#define CCM_SIZE 	0x00010000		// CCM_RAM_SIZE = 0x0001 0000 (64KB)

#define CCM_HEAP_SIZE 0x0000D000	// 建议为 4 的倍数

#endif
