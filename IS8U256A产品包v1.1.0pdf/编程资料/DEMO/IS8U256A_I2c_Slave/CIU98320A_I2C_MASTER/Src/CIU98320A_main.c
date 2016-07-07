/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_main.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.14
*����������
*			1��main����
*			2�����SPI��ʼ�����ã�
*�����б�
*			1��
*			2��
*			3��
*��ʷ��¼��
*	1�� ���ڣ�
*		�汾��
*		���ߣ�
*	�޸����ݣ�
*	2��.....
\***************************************************/
#include <string.h>
#include "CIU98320A.h"
#include "CIU98320A_typesmacro.h"
#include "CIU98320A_sysclk.h"
#include "CIU98320A_i2c_master.h"
#include "CIU98320A_gpio.h"

#define BUFF_LENGTH				64
#define PAGE_LENGTH				64
#define CONTROL_BYTE_WRITE		0xAA
#define CONTROL_BYTE_READ		0xAB

unsigned char TxBuff_For_Test[BUFF_LENGTH]={0x0};
unsigned char RxBuff_For_Test[BUFF_LENGTH]={0x0};

void SysClkConfiguration(void)
{
	SysClkInitType SysClkInitStruct;
	
	SysClkInitStruct.SysClkSrc = SYSCLKOSC32M;
	SysClkInitStruct.SysClkDiv = SYSCLKDIV1;
	SysClkInitStruct.APBClkDiv = APBCLKDIV1;
	
	SysClkInitStruct.PLLEnable = PLLENABLE;
	SysClkInitStruct.PLLValue = PLLVALUE4;
	
	SysClkInit((SysClkInitType *)&SysClkInitStruct);
}

int main(void)
{
	UINT8 bytelen=0x0,i=0x0;

	SysClkConfiguration();

	GpioInit();				 

	SetGpioXIn(GPIO22);

	I2CCtrlInit(0xff,0xff);	

	while(1)
	{
		/*���Ϳ����ֽ�*/
		I2CGenerateStart(CONTROL_BYTE_WRITE);

		memset(TxBuff_For_Test,0xAA,sizeof TxBuff_For_Test);

		i=0x0;
		bytelen = 64;
		/*д����*/
		while(bytelen)
		{
			I2CSendByte(TxBuff_For_Test[i]);

			i++;

			bytelen--;
		}

		/*Stop*/
		I2CGenerateStop();

		I2CGenerateStart(CONTROL_BYTE_READ);

		memset(RxBuff_For_Test,0x0,sizeof RxBuff_For_Test);
		i=0x0;
		bytelen = 63;
		while(bytelen)
		{
			RxBuff_For_Test[i] = I2CReceByteWithACK();

			i++;

			bytelen--;
		}

		RxBuff_For_Test[i] = I2CReceByteWithNAK();

		I2CGenerateStop();

		for(i=0;i<64;i++)
			if(0xBB!=RxBuff_For_Test[i])
				goto Error;
	}

Error:
	while(1);
}
