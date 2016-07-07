/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	EEPROM_24LC128.h
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

/* Define to prevent recursive inclusion ---------------------------*/
#ifndef __EEPROM_24LC128_H__
#define __EEPROM_24LC128_H__

/*Includes----------------------------------------------------------*/
/*Exported typedef--------------------------------------------------*/
/*Exported define---------------------------------------------------*/
#ifndef EEPROM_EXTERN
#define EEPROM_EXTERN			extern
#endif

/*Exported macro----------------------------------------------------*/
/*Exported functions------------------------------------------------*/
EEPROM_EXTERN unsigned char EEPROM_ByteRead(unsigned int address);
EEPROM_EXTERN void EEPROM_ByteWrite(
										unsigned int address,\
										unsigned char ch);
EEPROM_EXTERN void EEPROM_PageWrite(
										unsigned int address,\
										unsigned char *const pbuff);

EEPROM_EXTERN void EEPROM_DataRead(
										unsigned int address,			  \
										unsigned char *const pRxBuff,\
										unsigned int bytelen);

#endif

/************************end of file*********************************/

