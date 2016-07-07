/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_24lc128.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.14
*����������
*			���I2C���豸24LC128оƬ�ĸ��ֲ���
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
#include "CIU98320A.h"
#include "CIU98320A_typesmacro.h"
#include "CIU98320A_i2c_master.h"

/***************************************************\
*�������ƣ�ByteWrite
*�������ܣ�24LC128���дһ�ֽ�
*���������
*			1��UINT16 address�����ݵ�Ŀ�ĵ�ַ
*			2��UINT8 data����д���һ�ֽ�����
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void ByteWrite(UINT16 address,UINT8 data)
{
	UINT8 addr_h;
	UINT8 addr_l;
	addr_h = (address>>8)&0xFF;
	addr_l = address&0xFF;

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);

	I2CTransmitData(0x31,data);
	I2CGenerateStop();

	I2CBusStatCheck();
}

/***************************************************\
*�������ƣ�RandomRead
*�������ܣ�24LC128��ɶ�һ�ֽ�
*���������
*			1��UINT16 address������ȡ���ݵĵ�ַ
*�����������
*�� �� ֵ����ȡ���
*����˵����
\***************************************************/
UINT8 RandomRead(UINT16 address)
{
	UINT8 addr_h;
	UINT8 addr_l;
	UINT8 datatmp;

	addr_h = (address>>8)&0xFF;
	addr_l = address&0xFF;

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);

	I2CTransmitData(0x25,0xA1);

	datatmp = I2CReceiveData(0x21);
	I2CGenerateStop();

	return datatmp;
}

/***************************************************\
*�������ƣ�PageWrite
*�������ܣ�24LC128���д64�ֽ�
*���������
*			1��UINT16 address����д�����ݵ�Ŀ�ĵ�ַ
*			2��UINT8 *pData����д�����ݵ�Դ��ַ
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void PageWrite(UINT16 address,UINT8 *pData)
{
	UINT8 addr_l=0x0;
	UINT8 addr_h=0x0;
	UINT8 i=0x0;
	
	addr_l = (UINT8)(address&&0xFF);
	addr_h = (UINT8)((address>>8)&&0xFF);

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);
	
	for(i=0;i<64;i++)
	{
		I2CTransmitData(0x31,*(pData+i));
	}

	I2CGenerateStop();

	I2CBusStatCheck();
}

/***************************************************\
*�������ƣ�SequentialRead
*�������ܣ�24LC128���д������ȡbytelen�ֽ�
*���������
*			1��UINT16 address������ȡ���ݵ�Դ��ַ
*			2��UINT8 *pData������ȡ���ݵ�Ŀ�ĵ�ַ
*			3��UINT8 bytelen������ȡ���ݵĳ���
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void SequentialRead(UINT8 *pData,UINT16 address,UINT8 bytelen)
{
	UINT8 addr_l=0x0;
	UINT8 addr_h=0x0;
	UINT8 datatmp=0x0;
	UINT8 i=0x0;
	
	addr_l = (UINT8)(address&&0xFF);
	addr_h = (UINT8)((address>>8)&&0xFF);

	I2CTransmitData(0x30,0xA0);

	I2CTransmitData(0x31,addr_h);

	I2CTransmitData(0x31,addr_l);

	I2CTransmitData(0x25,0xA1);

	for(i=0;i<bytelen;i++)
	{
		datatmp = I2CReceiveData(0x21);
		*(pData+i) = datatmp;
		datatmp = 0x0;
	}

	I2CGenerateStop();

	I2CBusStatCheck();
}
