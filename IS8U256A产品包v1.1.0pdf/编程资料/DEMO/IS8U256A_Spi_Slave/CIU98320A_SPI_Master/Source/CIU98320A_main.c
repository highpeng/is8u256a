/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_main.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.03
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
#include "CIU98320A_SPI.h"
#include "CIU98320A_GPIO.h"
//#include "CIU98320A_25Q80.h"

#define DATA_LENGTH		16

unsigned char Buff1_For_Test[64]={0x0};
unsigned char Buff2_For_Test[64]={0x0};

void SysClkConfiguration(void)
{
	SysClkInitType SysClkInitStruct;
	
	SysClkInitStruct.SysClkSrc = SYSCLKOSC32M;
	SysClkInitStruct.SysClkDiv = SYSCLKDIV4;
	SysClkInitStruct.APBClkDiv = APBCLKDIV1;
	
	SysClkInitStruct.PLLEnable = PLLENABLE;
	SysClkInitStruct.PLLValue = PLLVALUE4;
	
	SysClkInit((SysClkInitType *)&SysClkInitStruct);
}

void SpiConfiguration(void)
{
	SPICtrlInitTypes SPICtrlStruct;

	SPICtrlStruct.spi_interface_mode = NORMAL_MODE;
	SPICtrlStruct.spi_data_format = SPI_DATA_MSB;
	SPICtrlStruct.spi_cpol = SPI_CPOL_LOW;

	SPICtrlStruct.spi_mode = SPI_MODE_MASTER;

	SPICtrlStruct.spi_data_len = SPI_DATA_1B;

	SPICtrlStruct.spi_mdiv_en =  SPI_MDIV_EN;
	SPICtrlStruct.spi_div = 0x00;

	SPICtrlStruct.spi_ovrf_int_en = SPI_OVRF_INT_DIS;
	SPICtrlStruct.spi_done_int_en = SPI_DONE_INT_DIS;

   	SPI0CtrlInit((SPICtrlInitTypes *)&SPICtrlStruct);

}

int main(void)
{
	unsigned char i;

	SysClkConfiguration();

	GpioInit();
	SetGpioXIn(GPIO22);

	SpiConfiguration();	

	memset(Buff1_For_Test,0xAA,sizeof Buff1_For_Test);	

	while(1)
	{
		/*Send Data*/
		SPI0On();
		SPI0TransmitData(&Buff1_For_Test[0],(void *)0,DATA_LENGTH);
		SPI0Off();
		
		/*Receive Data*/
		memset(Buff2_For_Test,0x0,sizeof Buff2_For_Test);
		SPI0On();
		SPI0TransmitData((void *)0,Buff2_For_Test,DATA_LENGTH);
		SPI0Off();

		for(i=0;i<DATA_LENGTH;i++)
			if(0x88!=Buff2_For_Test[i])
				goto Error;

	}

Error:
	while(1);

}
