/*****************************************************************************************************
 * @file        Screen.h
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
#ifndef __Screen__
#define __Screen__
// <h> ������
	// <h> ���ֱ���
		// <o> ������������
		#define Screen_W   320
		// <o> ������������
		#define Screen_H   480
	// </h>

	// <o> ˢ����
	// <i> ��λ: Hz
	// <i> ����Ŀǰ���κ����� 
	#define Screen_Rate 60
// </h>

// <h> ��ʾ����
	// <o > ��Ļ����	
	// 		<0=> ����ģʽ
	// 		<1=> ����ģʽ(180��)
	// 		<2=> ����ģʽ
	//		<3=> ����ģʽ(180��)
	#define SCREEN_ROTATION 0
	// <q> ˮƽ����
	#define HORIZONTAL_MIRRORING 	1
	// <q> ��ֱ����
	#define VERTICAL_MIRRORING 		0
	// <q> ���н���
	#define ROW_COLUMN_EXCHANGE 	0
// </h>

// <h> ��Ļ������ʽ
	// <e> DBI
	#define DBI_BUS 1
		// <o DBI_BUS_TYPE> DBI ����Э��
		// 		<0=> TypeA(M68)
		// 		<1=> TypeB(I80)
		// 		<2=> TypeC(SPI)
		// <i> ѡ�� DBI ������ʽ�����ߴ���Э��
		#define DBI_BUS_TYPE 1
		
		// <h> TypeA Configuration
			// <n> Ŀǰδ�Ӵ��� M68 ������������Ļ, ����δ��д
		// </h>

		// <h> TypeB Configuration
			// <o> FSMC Ƭѡ <1-4>
			#define __FSMC_NE__               	1 
			// <o> FSMC ����/����ӳ���ַ <16-23>
			#define __FSMC_A__                	19
		// </h>

		// <h> TypeC Configuration
			// <n> ͵��, û�� SPI ���߽�������
		// </h>

		// <o DBI_BUS_TYPE> DBI ����Э��
		// 		<0=> ST7789
		// 		<1=> ILI9341
		// 		<2=> ILI9486
		// <i> ѡ�� DBI ������ʽ�����ߴ���Э��
		#define SCREEN_DRIVER 2 
	// </e>
	
	// <e> DPI
		#define DPI_BUS 0
	// </e>

	// <e> DSI
		#define DSI_BUS 0  
	// </e>
// </h>

//------------- <<< end of configuration section >>> -----------------------

// ����ֱ���ӳ��Ϊ�߼��ֱ���
#if	  ( SCREEN_ROTATION == 0 ||  SCREEN_ROTATION == 1 )
	#define	LOGIC_W	Screen_W
	#define LOGIC_H	Screen_H
#elif ( SCREEN_ROTATION == 2 ||  SCREEN_ROTATION == 3 )
	#define	LOGIC_W	Screen_H
	#define LOGIC_H	Screen_W
#else
	#error "SCREEN_ROTATION must be 0,1,2,3"
#endif


// ѡ�������ͷ�ļ�
#if	  (DBI_BUS)
#include "./User/Device/Screen/AbstractionLayer/MIPI/MIPI-DBI.h"
#elif (DPI_BUS)
#include "./Device/Screen/AbstractionLayer/MIPI/MIPI-DPI.h"
#elif (DSI_BUS)
#include "./Device/Screen/AbstractionLayer/MIPI/MIPI-DSI.h"
#else
#error "You must be selected only one from {DBI_BUS, DPI_BUS and DSI_BUS}!"
#endif

// ѡ��ʹ�õĿ�����
#if   (SCREEN_DRIVER  == 0)
#include "./Device/Screen/AbstractionLayer/Chip/ST7789.h"
#elif (SCREEN_DRIVER  == 1)
#include "./Device/Screen/AbstractionLayer/Chip/ILI9341.h"
#elif (SCREEN_DRIVER  == 2)
#include "./User/Device/Screen/AbstractionLayer/Chip/ILI9486.h"
#else
#error "Unsupported screen driver"
#endif

#endif
