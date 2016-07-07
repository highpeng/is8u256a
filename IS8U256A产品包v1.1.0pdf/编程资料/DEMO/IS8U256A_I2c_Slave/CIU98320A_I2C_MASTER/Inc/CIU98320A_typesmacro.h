/************************************************************/
/*				Copy Right (C) HED.Inc						*/
/*				All Right Reserved							*/
/*�ļ����ƣ�CIU96S320A_typesmacro.h							*/
/*��    �ߣ�												*/
/*��ǰ�汾��V1.0.0											*/
/*��    �ڣ�2012-08-26										*/
/*����������	   											*/
/*		  ���ļ����ڶ���CIU96S320AоƬ���õ������Ͷ���ͺ�  */
/*�޸����ݣ���������										*/
/************************************************************/
#ifndef __CIU98S320A_TYPEMARCO_H__
#define __CIU98S320A_TYPEMARCO_H__

#define u8READ(REG)				(*((unsigned char *)(REG)))
#define u8WRITE(REG,DATA)		((*((unsigned char *)(REG)))=DATA)
#define u16READ(REG)			(*((unsigned short *)(REG)))
#define u16WRITE(REG,DATA)		((*((unsigned short *)(REG)))=DATA)
#define u32READ(REG)			(*((unsigned long *)(REG)))
#define u32WRITE(REG,DATA)		((*((unsigned long *)(REG)))=DATA)

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef pUINT8
typedef unsigned char *pUINT8;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef pUINT16
typedef unsigned short *pUINT16;
#endif

#ifndef UINT32
typedef unsigned long UINT32;
#endif

#ifndef pUINT32
typedef unsigned long *pUINT32;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef pBYTE
typedef unsigned char *pBYTE;
#endif

#ifndef WORD
typedef unsigned long WORD;
#endif

#ifndef pWORD
typedef unsigned char *pWORD;
#endif

#ifndef SUCCESS
#define SUCCESS		0x00
#endif

#ifndef FAIL
#define FAIL		0x01
#endif

#ifndef TRUE
#define TRUE		0x00
#endif

#ifndef FALSE
#define FALSE		0x01
#endif

#endif
