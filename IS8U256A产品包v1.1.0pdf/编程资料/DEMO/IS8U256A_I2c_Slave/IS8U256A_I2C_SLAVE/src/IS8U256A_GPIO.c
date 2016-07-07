/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	IS8U256A_GPIO.c
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
/*Private macro-----------------------------------------------------*/
/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:GPIOInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void GPIOInit(void)
{
	/*ʹ��GPIOģ��*/
	PCON1 |= 0x08;

	/*GPIO20--GPIO1ȫ��ѡ��GPIOͨ��*/
	COMCON = 0x0;

	/*����GPIO8--GPIO1Ϊ����ģʽ*/
	GPIOPR = 0xFF;

	/*����GPIO16--GPIO9Ϊ����ģʽ*/
	GPIOPR1 = 0xFF;

	/*����GPIO20--GPIO17Ϊ����ģʽ*/
	GPIOPR2 = 0xF5;
}

/*********************************************************************
 * Function Name	:GPIOSetInput
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOSetInput(unsigned long const gpx)
{
	unsigned long index=~gpx;

	/*����GPIO8--GPIO0�Ƿ�������Ϊ����ģʽ*/
	GPIOCTRL &= (unsigned char)((index>>0)&0xFF);

	/*����GPIO16--GPIO9�Ƿ�������Ϊ����ģʽ*/
	GPIOCTRL1 &= (unsigned char)((index>>8)&0xFF);

	/*����GPIO20--GPIO17�Ƿ�������Ϊ����ģʽ*/
	GPIOCTRL2 &= (unsigned char)((index>>16)&0xFF);
}

/*********************************************************************
 * Function Name	:GPIOSetOutput
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOSetOutput(unsigned long const gpx)
{
	unsigned long index=gpx;

	/*����GPIO8--GPIO0�Ƿ�������Ϊ����ģʽ*/
	GPIOCTRL |= (unsigned char)((index>>0)&0xFF);

	/*����GPIO16--GPIO9�Ƿ�������Ϊ����ģʽ*/
	GPIOCTRL1 |= (unsigned char)((index>>8)&0xFF);

	/*����GPIO20--GPIO17�Ƿ�������Ϊ����ģʽ*/
	GPIOCTRL2 |= (unsigned char)((index>>16)&0xFF);
}

/*********************************************************************
 * Function Name	:GPIOReset
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOReset(unsigned long const gpx)
{
	unsigned long index=~gpx;

	/*����GPIO8--GPIO0�Ƿ����踴λ�ܽ�*/
	GPIODATA &= (unsigned char)((index>>0)&0xFF);

	/*����GPIO16--GPIO9�Ƿ����踴λ�ܽ�*/
	GPIODATA1 &= (unsigned char)((index>>8)&0xFF);

	/*����GPIO20--GPIO17�Ƿ����踴λ�ܽ�*/
	GPIODATA2 &= (unsigned char)((index>>16)&0xFF);
}

/*********************************************************************
 * Function Name	:GPIOSet
 * Description		:
 * Argument		:
 * Return		:
**********************************************************************/
void GPIOSet(unsigned long const gpx)
{
	unsigned long index=gpx;

	/*����GPIO8--GPIO0�Ƿ�������λ�ܽ�*/
	GPIODATA |= (unsigned char)((index>>0)&0xFF);

	/*����GPIO16--GPIO9�Ƿ�������λ�ܽ�*/
	GPIODATA1 |= (unsigned char)((index>>8)&0xFF);

	/*����GPIO20--GPIO17�Ƿ�������λ�ܽ�*/
	GPIODATA2 |= (unsigned char)((index>>16)&0xFF);
}

/***************************End of File*******************************/
