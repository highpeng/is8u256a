/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_gpio.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.14
*����������
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

/***************************************************\
*�������ƣ�GpioInit
*�������ܣ����GPIO��ʼ��
*�����������
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void GpioInit(void)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<19);
	u32WRITE(SYS_CLK_EN,regtmp);
}

/***************************************************\
*�������ƣ�SetGpioXOut
*�������ܣ�������Ӧ��GPIO����Ϊ���
*���������UINT32 GPIOX
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void SetGpioXOut(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DIR);
	regtmp |= GPIOX;
	u32WRITE(GPIO_DIR,regtmp);

}

/***************************************************\
*�������ƣ�SetGpioXIn
*�������ܣ�������Ӧ��GPIO����Ϊ����
*���������UINT32 GPIOX
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void SetGpioXIn(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DIR);
	regtmp &= ~GPIOX;
	u32WRITE(GPIO_DIR,regtmp);
}

/***************************************************\
*�������ƣ�SetGpioXHigh
*�������ܣ�������Ӧ��GPIO����Ϊ�ߵ�ƽ
*���������UINT32 GPIOX
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void SetGpioXHigh(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DATA);
	regtmp |= GPIOX;
	u32WRITE(GPIO_DATA,regtmp);
}

/***************************************************\
*�������ƣ�SetGpioXLow
*�������ܣ�������Ӧ��GPIO����Ϊ�͵�ƽ
*���������UINT32 GPIOX
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void SetGpioXLow(UINT32 GPIOX)
{
	UINT32 regtmp=0x0;

	regtmp = u32READ(GPIO_DATA);
	regtmp &= ~GPIOX;
	u32WRITE(GPIO_DATA,regtmp);
}
