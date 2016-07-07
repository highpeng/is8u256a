/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	IS8U256A_I2CSlave.h
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
#ifndef __IS8U256A_I2CSLAVE_H__
#define __IS8U256A_I2CSLAVE_H__

/*Includes----------------------------------------------------------*/
/*Exported typedef--------------------------------------------------*/
typedef enum{SLAVE_INPUT=0,SLAVE_OUTPUT = !SLAVE_INPUT}Direction_TypeDef;
/*Exported define---------------------------------------------------*/
#ifndef I2CSLAVE_EXTERN
#define I2CSLAVE_EXTERN			extern
#endif

I2CSLAVE_EXTERN void I2CSlaveInit(void);
I2CSLAVE_EXTERN void I2CSlaveSendByte(unsigned char ch);
I2CSLAVE_EXTERN unsigned char I2CSlaveReceByte();
I2CSLAVE_EXTERN unsigned char I2CSlavePrepareToTransmit(void);
I2CSLAVE_EXTERN void I2CSlaveRDYSet(void);
I2CSLAVE_EXTERN void I2CSlaveRDYClr(void);

/*Exported macro----------------------------------------------------*/
/*Exported functions------------------------------------------------*/

#endif

/************************end of file*********************************/


