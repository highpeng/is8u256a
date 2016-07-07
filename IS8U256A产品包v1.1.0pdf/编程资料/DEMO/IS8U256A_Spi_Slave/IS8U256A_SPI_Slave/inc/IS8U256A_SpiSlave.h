/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	IS8U256A_SpiSlave.h
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
#ifndef __IS8U256A_SPISLAVE_H__
#define __IS8U256A_SPISLAVE_H_

/*Includes----------------------------------------------------------*/
/*Exported typedef--------------------------------------------------*/
/*Exported define---------------------------------------------------*/
#ifndef SPISLAVE_EXTERN
#define SPISLAVE_EXTERN			extern
#endif

SPISLAVE_EXTERN void SpiSlaveInit(void);

SPISLAVE_EXTERN void SpiTransmitData(
					unsigned char xdata *ptxbuff,\
					unsigned char xdata *prxbuff,\
					unsigned char bytelen);

/*Exported macro----------------------------------------------------*/
/*Exported functions------------------------------------------------*/

#endif

/************************end of file*********************************/


