/*********************************************************************
* 		Copyright(C)2012���������Ű��Ƽ����޹�˾
* 			All Rights Reserved	 
*
* �ļ����ƣ�	IS8U256A_I2CSlave.c
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
#include "..\inc\IS8U256A_I2CSlave.h"

/*Private typedef---------------------------------------------------*/
/*Private define----------------------------------------------------*/
/*Private macro-----------------------------------------------------*/
/*I2C-SLAVE�豸�ĵ�ַ��0xAA*/
/*ע�⣺�õ�ַ���ݾ���Ӧ�ö���ͬ*/
#define I2C_SLAVE_ADDRESS		0xAA

/*Private variables-------------------------------------------------*/
/*Private function prototypes---------------------------------------*/
/*Private functions-------------------------------------------------*/

/********************************************************************
 * Function Name	:I2CSlaveInit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveInit(void)
{
	/*ʹ��I2Cģ��*/
	PCON2 |= 0x08; 

	/*ʹ��GPIOģ��*/
	PCON1 |= 0x08;

	/*GPIO13/14����ΪI2C�ӿ�*/
	COMCON |= 0x80;

	/*ѡ��I2C�ӿڼĴ�����*/
	COMSEL |= 0x03;

	/*����I2C-Slaveģʽ��ַ*/
	I2CADDR = I2C_SLAVE_ADDRESS&0xFE;
}

/********************************************************************
 * Function Name	:I2CSlavePrepareToTransmit
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
Direction_TypeDef I2CSlavePrepareToTransmit(void)
{
	while(1)
	{
		/*����׼�������ź�*/
		I2CSlaveRDYSet();

		/*���׼�������ź�*/
		I2CSlaveRDYClr();

		/*�ȴ�������I2C-Master�豸����Start/ReStart�ź�*/
		while(0x0==(0x20&I2CSTATUS));

		/*�ȴ������ֽڴ������*/
		while(0x0==(0x80&I2CSTATUS));

		/*�жϵ�ַ�Ƿ�ƥ��*/
		if(0x0==(0x40&I2CSTATUS))
			continue;

		/*�жϺ������ݵĴ��䷽��*/
		if(0x0==(0x04&I2CSTATUS))
			return SLAVE_INPUT;
		else
			return SLAVE_OUTPUT;
	}

}

/********************************************************************
 * Function Name	:I2CSlaveSendByte
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveSendByte(unsigned char ch)
{
	/*�ж�ACK�ź�*/
	if(0x0==(0x01&I2CSTATUS))
	{
		/*����������д��Ĵ���*/
		I2CTDR = ch;
	
		/*���ÿɴ������ݱ�־*/
		I2CCON &= 0xF7;

		/*���������ɱ�־*/
		I2CCON |= 0x01;

		/*����׼�������ź�*/
		I2CSlaveRDYSet();

		/*���׼�������ź�*/
		I2CSlaveRDYClr();

		/*�ȴ��������*/
		while(0x0==(0x80&I2CSTATUS));
	}
}

/********************************************************************
 * Function Name	:I2CSlaveReceByte
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
unsigned char I2CSlaveReceByte(void)
{
	/*���ÿɴ������ݱ�־*/
	I2CCON &= 0xF7;

	/*���������ɱ�־*/
	I2CCON |= 0x01;

	/*����׼�������ź�*/
	I2CSlaveRDYSet();

	/*���׼�������ź�*/
	I2CSlaveRDYClr();

	/*�ȴ��������*/
	while(0x0==(0x80&I2CSTATUS));
	
	/*��ȡ���������*/
	return I2CRDR;
}

/********************************************************************
 * Function Name	:I2CSlaveRDYSet
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveRDYSet(void)
{
	/*************************
	 *
	 *�����û��Լ��ı�־�������
	 *
	 * ***********************/
	GPIOSet(GPIO_PIN_20);
	
}

/********************************************************************
 * Function Name	:I2CSlaveRDYClr
 * Description		:
 * Argument		:
 * Return		:
*********************************************************************/
void I2CSlaveRDYClr(void)
{
	/*************************
	 *
	 *�����û��Լ��ı�־�������
	 *
	 * ***********************/
	GPIOReset(GPIO_PIN_20);

}
/************************end of file*********************************/
