/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_i2c_master.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.14
*����������
*			CIU98320A��ģʽ�µ�I2Cͨ��
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
#include "ciu98320a.h"
#include "ciu98320a_typesmacro.h"
#include "ciu98320a_gpio.h"

#define I2C_SLAVE_FLAG					((UINT32)0x01<<21)

void I2CCtrlInit(unsigned long scl_hcnt,unsigned long scl_lcnt)
{
	UINT32 regtmp=0x0;

	// Enable GPIO-module
	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<19);
	u32WRITE(SYS_CLK_EN,regtmp);
	regtmp = 0x0;

	// Enable I2C-module
	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<23);
	u32WRITE(SYS_CLK_EN,regtmp);
	regtmp = 0x0;

	// GP15��16 --- I2C
	regtmp = u32READ(SYS_COMCON);
	regtmp |= (1<<3);
	u32WRITE(SYS_COMCON,regtmp);
	regtmp = 0x0;

//	u32WRITE(I2C_SCL_HCNT,scl_hcnt);
//	u32WRITE(I2C_SCL_LCNT,scl_lcnt);
	
//	u32WRITE(SYS_CLK_CFG,0x30);

//	u32WRITE(SYS_CLK_PLLEN,0x41);

}

/***************************************************\
*�������ƣ�I2CGenerateStart
*�������ܣ�I2C����start�źţ�ռ������
*�����������
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void I2CGenerateStart(unsigned char controlbyte)
{
	unsigned long regtmp=0x0;

	/*�ȴ����߿���*/
	while((((unsigned long)0x20)&(u32READ(I2C_STAT))));

	/*���Ϳ����ֽ�*/
	u32WRITE(I2C_TX_DATA,(unsigned long)controlbyte);

	/*���ú������ݴ��䷽��*/
	regtmp = u32READ(I2C_CTRL);
	regtmp &= 0xFFFFFFEF;
	if(0x0==(0x01&controlbyte))
		regtmp |= (unsigned long)0x10;

	/*����Start�ź�*/
	regtmp |= (unsigned long)0x20;

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*�ȴ����δ������*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

}

/***************************************************\
*�������ƣ�I2CGenerateReStart
*�������ܣ�I2C����ReStart�źţ�ռ������
*�����������
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void I2CGenerateReStart(unsigned char controlbyte)
{
	UINT32 regtmp=0x0;

	/*д������ֽ�*/
	u32WRITE(I2C_TX_DATA,(unsigned long)controlbyte);

	/*���ú����ֽڷ���*/
	regtmp = u32READ(I2C_CTRL);
	regtmp &= 0xFFFFFFEF;
	if(0x0==(0x01&controlbyte))
		regtmp |= (unsigned long)0x10;

	/*����ReStart�ź�*/
	regtmp |= (unsigned long)0x04;

	/*�������δ���*/
	regtmp |= (unsigned long)0x01;

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*�ȴ����δ������*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*���ReStart����λ*/
	regtmp = u32READ(I2C_CTRL);
	regtmp &= 0xFFFFFFFB;
	u32WRITE(I2C_CTRL,regtmp);

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
}

/***************************************************\
*�������ƣ�I2CGenerateStop
*�������ܣ�I2C����Stop�źţ��ͷ�����
*�����������
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void I2CGenerateStop(void)
{
	unsigned long regtmp;

	regtmp = u32READ(I2C_CTRL);

	/*����Stop�ź�*/
	regtmp &= 0xFFFFFFDF;

	/*��������λ*/
	regtmp |= (unsigned long)0x01;

	u32WRITE(I2C_CTRL,regtmp);

}

/***************************************************\
*�������ƣ�I2CTransmitData
*�������ܣ���������
*���������
*		   1��UINT8 ctrl,I2C�����ֽ�
*		   2��UINT8 data,����������
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void I2CSendByte(unsigned char data)
{
	unsigned long regtmp;

	u32WRITE(I2C_TX_DATA,data);

	/*��������*/
	regtmp = u32READ(I2C_CTRL);
	regtmp |= (unsigned long)0x01;

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*�ȴ����δ������*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
}

/***************************************************\
*�������ƣ�I2CReceiveData
*�������ܣ���������
*���������
*		   1��UINT8 ctrl,I2C�����ֽ�
*�����������
*�� �� ֵ��UINT8 datatmp,���յ�����
*����˵����
\***************************************************/
UINT8 I2CReceByteWithACK(void)
{
	unsigned long regtmp;

	regtmp = u32READ(I2C_CTRL);

	/*����Master-Receiveģʽ�£�����ACK*/
	regtmp &= 0xFFFFFFF7;

	/*�������δ���*/
	regtmp |= (unsigned long)0x01;

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*�ȴ����δ������*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
	
	regtmp = u32READ(I2C_RX_DATA);

	return (unsigned char)regtmp;
}

UINT8 I2CReceByteWithNAK(void)
{
	unsigned long regtmp;

	regtmp = u32READ(I2C_CTRL);

	/*����Master-Receiveģʽ�£�����ACK*/
	regtmp |= (unsigned long)0x08;

	/*�������δ���*/
	regtmp |= (unsigned long)0x01;

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(0x0==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));

	u32WRITE(I2C_CTRL,regtmp);

	/*�ȴ����δ������*/
	while(0x0==(((unsigned long)0x80)&(u32READ(I2C_STAT))));

	/*�ȴ�I2C_SLAVE�豸׼������*/
	while(I2C_SLAVE_FLAG==((u32READ(GPIO_DATA))&I2C_SLAVE_FLAG));
	
	regtmp = u32READ(I2C_RX_DATA);

	return (unsigned char)regtmp;
}
