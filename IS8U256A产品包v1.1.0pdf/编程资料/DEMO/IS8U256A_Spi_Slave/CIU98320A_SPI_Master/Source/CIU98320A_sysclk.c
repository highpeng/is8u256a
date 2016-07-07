/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_sysclk.c
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
#include "CIU98320A_sysclk.h"

void SysClkInit(SysClkInitType *SysClkInit)
{
	UINT32 regtmp=0x0;
	regtmp = u32READ(SYS_CLK_CFG);
	regtmp &= 0xFFFF0F00;
	regtmp |= SysClkInit->SysClkSrc | SysClkInit->SysClkDiv | 
			  SysClkInit->APBClkDiv ;
	u32WRITE(SYS_CLK_CFG,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SYS_CLK_PLLEN);
	regtmp &= 0x00;
	regtmp |= SysClkInit->PLLEnable;

	if(regtmp&0x01)
	{
		regtmp |= SysClkInit->PLLValue;
	}
	else
	{
		regtmp |= 0x40;
	}

	u32WRITE(SYS_CLK_PLLEN,regtmp);
}
