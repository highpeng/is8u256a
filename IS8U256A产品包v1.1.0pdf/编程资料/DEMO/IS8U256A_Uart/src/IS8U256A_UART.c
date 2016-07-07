/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	XA1302_UART.c
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

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
#define UART_CLK			48000000

/*Private macro-----------------------------------------------------*/
/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:GCD
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
static unsigned long GCD(unsigned long X1 , unsigned long X2)
{
	unsigned long max=0x0;
	unsigned long min=0x0;
	unsigned long X,Y,R;

	max = (X1>X2)?X1:X2;
	min = (X1>X2)?X2:X1;
	X = max;
	Y = min;

	while(0x0!=Y)
	{
		R = X%Y;
		X = Y;
		Y = R;
	}

	return X;
}

/********************************************************************
 * Function Name	:UARTSetBaudRate
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
static void UARTSetBaudRate(unsigned long baudrate)
{
	unsigned long gcd;
	unsigned long baud_freq,baud_limit;

	gcd = GCD(UART_CLK,16*baudrate);
	baud_freq = (16*baudrate)/gcd;
	baud_limit = (UART_CLK/gcd)-baud_freq;

	BAUD_FREQ = (unsigned char)(baud_freq&0xFF);
	BAUD_FREQ = (unsigned char)((baud_freq>>8)&0xFF);
	BAUD_LIMIT = (unsigned char)(baud_limit&0xFF);
	BAUD_LIMIT = (unsigned char)((baud_limit>>8)&0xFF);
}

/********************************************************************
 * Function Name	:UARTInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void UARTInit(void)
{
	/*ʹ��PLL*/
	PLLCON |= 0x01;

	/*�ȴ�PLL�ȶ�*/
	while(0x0==(PLLCON&0x02));

	/*ʹ��GPIOģ��*/
	PCON1 |= 0x08;

	/*GP11/12����ΪUART����*/
	COMCON |= 0x40;

	/*ʹ��UARTģ��*/
	PCON2 |= 0x04;

	/*ѡ��UART�Ĵ�����*/
	COMSEL = 0x01;

	/*���ò����ʣ�115200*/
	UARTSetBaudRate(9600);

	/*���ý���ֹͣλ��1bit*/
	UARTPR &= 0x3F;

	/*���ý������ݿ�ȣ�8bit*/
	UARTPR &= 0xCF;

	/*���÷���ֹͣλ��1bit  */
	UARTPR &= 0xF3;

	/*���÷������ݿ�ȣ�8bit */
	UARTPR &= 0xFC;

	/*ʹ�ܽ���żУ��*/
	UARTCON |= 0x10;

	/*ʹ�ܷ���żУ��*/
	UARTCON |= 0x04;

	/*ʹ��UART�ж�ģʽ*/
	UARTCON |= 0x01;

	/*ʹ��UART�ж�*/
	IEH |= 0x20;

	/*ʹ�����ж�*/
	IEH |= 0x80;
}
/********************************************************************
 * Function Name	:UARTSendByte
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void UARTSendByte(unsigned char ch)
{
	/*�ȴ��ϴη��ͽ���*/
	while(0x01&UARTSR);

	/*д�뷢�ͼĴ������������η���*/
	TX_DATA = ch;

}

/********************************************************************
 * Function Name	:UARTHandler
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
//void UARTHandler(void) interrupt 13
//{
//	unsigned char regtmp;
//
//	/*�ر����ж�*/
//	IEH &= 0x7F;	
//
//	/*��������ж�*/
//	if(UARTSTATUS&0x02)
//	{
//		/*��������жϱ�־*/
//		UARTSTATUS &= 0xFD;
//
//		/*û�н��մ���*/
//		if(!(UARTSTATUS&0x38))
//		{
//			/****************************************
//			 * 
//			 * �����û����룬
//			 * �����ڴ˱�����յ����ݣ��жϽ����Ƿ���
//			 * �ɣ�����λ��ر�־���������������崦��
//			 *
//			*****************************************/
//		}
//		/*���ݽ��մ���*/
//		else
//		{
//			/******************
//			 * 
//			 * ���Ӵ��������
//			 *
//			*******************/
//		}
//	}
//
//	/*�������ж�*/
//	if(UARTSTATUS&0x04)
//	{
//		/*��������жϱ�־*/
//		UARTSTATUS &= 0xFB;
//
//		/************************************
//		 * 
//		 * �����û����룬
//		 * �����ڴ�ֻ�����־λ��������������
//		 *
//		*************************************/
//	}
//
//	/*�ָ����ж�*/
//	IEH |= 0x80;
//}

/************************end of file*********************************/
