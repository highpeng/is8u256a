/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	XA1302_GPIO.h
* ��    �ߣ�	���ܷ�
* ��    ����	V1.0.0
* ��	�ڣ�	2013-11
* ����������	
* �����б�	
*
* ��ʷ��¼��
* 1.  ���ڣ�	
*	  �汾��
*	  ���ߣ�
* �޸����ݣ�
*
*********************************************************************/

/* Define to prevent recursive inclusion ----------------------------*/
#ifndef __IS8U256A_GPIO_H__
#define __IS8U256A_GPIO_H__

/*Includes----------------------------------------------------------*/
/*Exported typedef---------------------------------------------------*/
/*Exported define----------------------------------------------------*/
#define GPIO_PIN_1			0x00000001
#define GPIO_PIN_2			0x00000002
#define GPIO_PIN_3			0x00000004
#define GPIO_PIN_4			0x00000008
#define GPIO_PIN_5			0x00000010
#define GPIO_PIN_6			0x00000020
#define GPIO_PIN_7			0x00000040
#define GPIO_PIN_8			0x00000080
#define GPIO_PIN_9			0x00000100
#define GPIO_PIN_10			0x00000200
#define GPIO_PIN_11			0x00000400
#define GPIO_PIN_12			0x00000800
#define GPIO_PIN_13			0x00001000
#define GPIO_PIN_14			0x00002000
#define GPIO_PIN_15			0x00004000
#define GPIO_PIN_16			0x00008000
#define GPIO_PIN_17			0x00010000
#define GPIO_PIN_18			0x00020000
#define GPIO_PIN_19			0x00040000
#define GPIO_PIN_20			0x00080000

#ifndef GPIO_EXTERN
#define GPIO_EXTERN			extern
#endif

/*Exported macro-----------------------------------------------------*/
/*Exported functions-------------------------------------------------*/
GPIO_EXTERN	void GPIOInit(void);
GPIO_EXTERN	void GPIOSetInput(unsigned long gpx);
GPIO_EXTERN	void GPIOSetOutput(unsigned long gpx);
GPIO_EXTERN	void GPIOSet(unsigned long gpx);
GPIO_EXTERN	void GPIOReset(unsigned long gpx);

#endif

/***************************End of File*******************************/
