/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_25Q80.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.03
*�������������W25Q80�Ĳ���д����ID��
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
#include "CIU98320A_spi.h"
#include "CIU98320A.h"

unsigned char Buff1_For_Test[8]={0x0};
unsigned char Buff2_For_Test[8]={0x0};

//UINT32 BusyCheck(void)
//{
//	unsigned short id=0x0;
//
//	Buff1_For_Test[0] = 0x05;
//
//	SPI0On();
//    SPI0TransmitData(Buff1_For_Test,Buff2_For_Test,3);
//	SPI0Off();
//
//	return id;
//}

/***************************************************\
*�������ƣ�SpiFlashReadID
*�������ܣ�Normal-mode��W25Q80��ID
*�����������
*�� �� ֵ��ID�ţ�0x13EF
*����˵����
\***************************************************/
UINT32 SpiFlashReadID(void)
{
	unsigned short id=0x0;

	Buff1_For_Test[0] = 0x90;

	SPI0On();
    SPI0TransmitData(Buff1_For_Test,Buff2_For_Test,6);
	SPI0Off();

	id = (Buff2_For_Test[4]<<8) | Buff2_For_Test[5];

	return id;
}


