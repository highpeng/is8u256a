/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	IS8U256A_SPISlave.c
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

/*Includes----------------------------------------------------------*/
#include "..\inc\IS8U256X.h"
#include "..\inc\IS8U256A_GPIO.h"

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
	/***********************************************
	 *���ݾ�����������ؾ����ָʾ�ź�
	 * **********************************************/
#define	TRANSMIT_RDY_FLAG		GPIO_PIN_20
#define TransmitRdySet()		GPIOSet(TRANSMIT_RDY_FLAG)
#define TransmitRdyReset()		GPIOReset(TRANSMIT_RDY_FLAG)

/*Private macro-----------------------------------------------------*/
/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:SpiSlaveInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void SpiSlaveInit(void)
{
	/*ʹ��SPIģ��*/
	PCON1 |= 0x10;

	/*GP7/8/9/10����ΪSPI����*/
	COMCON |= 0x02;

	/*ѡ��SPI�Ĵ�����*/
	COMSEL = 0x0;

	/*SPIģʽ������ģʽ*/
	SPIMODE &= 0xFC; 

	SPIMODE &= 0xDF;

	/*SPIģʽ����ģʽ*/
	SPICFG &= 0xFE;

	/*�������ݿ��Ϊ��8bit*/
	SPICFG |= 0x70;

	/*��������˳��Ϊ��MSB*/
	SPICFG |= 0x08;

	/*ʹ�ܷ��ͽ��չ���*/
	SPICON |= 0xC0;

	/*ʹ��SPI������*/
	SPICON |= 0x01;
}

/********************************************************************
 * Function Name	:SpiTransmitData
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void SpiTransmitData(
			unsigned char xdata * ptxbuff,	\
			unsigned char xdata * prxbuff,	\
			unsigned char bytelen			\
			)
{
	unsigned char xdata regtmp;
	unsigned char xdata*ptxtmp=ptxbuff;
	unsigned char xdata*prxtmp=prxbuff;
	
	while(bytelen)
	{
		if((void *)0!=ptxbuff)
		{
			/*д�봫������*/
			SPIDATA = *(ptxtmp++);
		}
		else
		{
			SPIDATA = 0x0;
		}

		/*����RDY��־:����Ч*/
		TransmitRdySet();

		/*���RDY��־*/
		TransmitRdyReset();

		/*�ȴ��������*/
		while(0x0==(0x04&SPISTATUS));

		regtmp = SPIDATA;

		if((void *)0!=prxbuff)
		{
			/*���ش��ͽ��*/
			*(prxtmp++) = regtmp;
		}

		bytelen--;

	}

}

/***************************End of File*******************************/

