/***************************************************\
*			Copy Right(C)HED.Inc
*			 All Right Reserved
*
*�ļ����ƣ�CIU98320A_spi.c
*��    �ߣ����ܷ�
*��    ����V1.0.0
*��    �ڣ�2012.09.03
*�������������CIU98320A����SPIͨ�ŵĵײ�����
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
#define SPI_GLOBAL

#include "CIU98320A.h"
#include "CIU98320A_typesmacro.h"
#include "CIU98320A_spi.h"
#include "CIU98320A_GPIO.h"

#define SPI_INTERFACE_MODE_MASK			((UINT32)0x8F)
#define SPI_DATA_FORMAT_MASK			((UINT32)0xF7)
#define SPI_CPOL_MASK					((UINT32)0xFB)
#define SPI_CHAP_MASK					((UINT32)0xFD)
#define SPI_MODE_MASK					((UINT32)0xFE)

#define SPI_DATALEN_MASK				((UINT32)0x00)

#define SPI_MDIV_EN_MASK				((UINT32)0x0FF)
#define SPI_DIV_MASK					((UINT32)0x0100)

#define SPI_IE_MASK						((UINT32)0x0C)

#define SPI_SLAVE_FLAG					((UINT32)0x01<<21)

/***************************************************\
*�������ƣ�SPI0CtrlInit
*�������ܣ����SPI0�ĳ�ʼ������
*���������spi_ctrl_struct
*�����������
*�� �� ֵ����
*����˵����
\***************************************************/
void SPI0CtrlInit(SPICtrlInitTypes *spi_ctrl_struct)
{
	UINT32 regtmp=0x0;

	/*Enable GPIO module*/
	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<19);
	u32WRITE(SYS_CLK_EN,regtmp);
	regtmp = 0x0;

	/*GPIO7-->SPI0_SS Enable*/
	regtmp = u32READ(GPIO_DIR);
	regtmp |= ((UINT32)0x40);
	u32WRITE(GPIO_DIR,regtmp);
	regtmp = 0x0;
	
	/*Enable SPI0 module*/
	regtmp = u32READ(SYS_CLK_EN);
	regtmp |= (1<<18);
	u32WRITE(SYS_CLK_EN,regtmp);
	regtmp = 0x0;

//	u32WRITE(SYS_CLK_CFG,0x00);
	
//	u32WRITE(SYS_CLK_PLLEN,0x41);
	
	/*COMCON --> Bit9:4*/
	regtmp = u32READ(SYS_COMCON);
	regtmp |= 0x03F0;
	u32WRITE(SYS_COMCON,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SPI0_CTRL);
	regtmp &= SPI_INTERFACE_MODE_MASK;
	regtmp |= spi_ctrl_struct->spi_interface_mode;
	u32WRITE(SPI0_CTRL,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SPI0_CTRL);
	regtmp &= SPI_DATA_FORMAT_MASK;
	regtmp |= spi_ctrl_struct->spi_data_format;
	u32WRITE(SPI0_CTRL,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SPI0_CTRL);
	regtmp &= SPI_CPOL_MASK;
	regtmp |= spi_ctrl_struct->spi_cpol;
	u32WRITE(SPI0_CTRL,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SPI0_CTRL);
	regtmp &= SPI_CHAP_MASK;
	regtmp |= spi_ctrl_struct->spi_chap;
	u32WRITE(SPI0_CTRL,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SPI0_CTRL);
	regtmp &= SPI_MODE_MASK;
	regtmp |= spi_ctrl_struct->spi_mode;
	u32WRITE(SPI0_CTRL,regtmp);
	regtmp = 0x0;

   	regtmp = u32READ(SPI0_DATALEN);
   	regtmp &= SPI_DATALEN_MASK;
   	regtmp |=  spi_ctrl_struct->spi_data_len;
	u32WRITE(SPI0_DATALEN,regtmp);
	regtmp = 0x0;

	regtmp = u32READ(SPI0_DIV);
   	regtmp &= SPI_MDIV_EN_MASK;
   	regtmp |=  spi_ctrl_struct->spi_mdiv_en;
	u32WRITE(SPI0_DIV,regtmp);
	regtmp = 0x0;

   	if(SPI_MDIV_EN==(spi_ctrl_struct->spi_mdiv_en))
	{
		regtmp = u32READ(SPI0_DIV);
   		regtmp &= SPI_DIV_MASK;
   		regtmp |=  spi_ctrl_struct->spi_div;
		u32WRITE(SPI0_DIV,regtmp);
		regtmp = 0x0;
	}

	if(SPI_MODE_MASTER==(spi_ctrl_struct->spi_mode))
	{
		regtmp = u32READ(SPI0_IE);
   		regtmp &= SPI_IE_MASK;
   		regtmp |=  spi_ctrl_struct->spi_done_int_en;
		u32WRITE(SPI0_IE,regtmp);
		regtmp = 0x0;
	}
	
	if(SPI_MODE_SLAVE==(spi_ctrl_struct->spi_mode))
	{
		regtmp = u32READ(SPI0_IE);
   		regtmp &= SPI_IE_MASK;
   		regtmp |=  spi_ctrl_struct->spi_ovrf_int_en;
		u32WRITE(SPI0_IE,regtmp);
		regtmp = 0x0;
	}

	/*SPI_SS=1*/
	regtmp = u32READ(GPIO_DATA);
	regtmp |= 0x40;
	u32WRITE(GPIO_DATA,regtmp);
	regtmp = 0x0;
}

/***************************************************\
*�������ƣ�SPI0TransmitData();
*�������ܣ�SPI0���ݴ��䣬�������պͷ���
*�����������
*�����������
*�� �� ֵ��SPI0DATA�е�����
\***************************************************/
void SPI0TransmitData(
						unsigned char *const ptxbuff,\
						unsigned char *const prxbuff,\
						unsigned int bytelen)
{
	UINT32 regtmp;
	unsigned char *ptmp1=ptxbuff,*ptmp2=prxbuff;

	while(bytelen)
	{
		u32WRITE(SPI0_DATALEN,0x0);
		
		if((void *)0!=ptxbuff)
		{
			u32WRITE(SPI0_DATA,*ptmp1++);
		}
		else
		{
			u32WRITE(SPI0_DATA,0x0);
		}

		/********��ѯ���豸׼��������־**********/
		while(0x0==((u32READ(GPIO_DATA))&SPI_SLAVE_FLAG));

		u32WRITE(SPI0_STR,0x01);

		regtmp = 0x00;
		do
		{
			regtmp = u32READ(SPI0_STAT);
			regtmp &= 0x01;
		}while(regtmp!=0x01);
	
		u32WRITE(SPI0_STAT,0x00);
	
		regtmp = u32READ(SPI0_DATA);

		if((void *)0!=prxbuff)
			*ptmp2++ = (unsigned char)regtmp;

		bytelen--;

		while(0x0!=((u32READ(GPIO_DATA))&SPI_SLAVE_FLAG));
	}
}

void SPI0On(void)
{
	UINT32 regtmp=0x0;
	
	regtmp = u32READ(GPIO_DATA);
	regtmp &= ~0x40;
	u32WRITE(GPIO_DATA,regtmp);
}

void SPI0Off(void)
{
	UINT32 regtmp=0x0;
	
	regtmp = u32READ(GPIO_DATA);
	regtmp |= 0x40;
	u32WRITE(GPIO_DATA,regtmp);
}
