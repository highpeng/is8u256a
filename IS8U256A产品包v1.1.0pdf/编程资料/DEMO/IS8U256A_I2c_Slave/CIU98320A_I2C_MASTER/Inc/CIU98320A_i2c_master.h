/************************************************************/
/*				Copy Right (C) HED.Inc						*/
/*				All Right Reserved							*/
/*�ļ����ƣ�CIU98320a_i2c_master.h							*/
/*��    �ߣ�												*/
/*��ǰ�汾��V1.0.0											*/
/*��    �ڣ�2012-08-26										*/
/*����������	   											*/
/*�޸����ݣ���������										*/
/************************************************************/

#ifndef __CIU98320A_I2C_MASTER_H__
#define __CIU98320A_I2C_MASTER_H__

#ifndef __I2C_MASTER__
#define I2C_EXT extern
#else
#define I2C_EXT
#endif

I2C_EXT I2CCtrlInit(unsigned long scl_hcnt,unsigned long scl_lcnt);
I2C_EXT void I2CGenerateStart(unsigned char controlbyte);
I2C_EXT void I2CGenerateReStart(unsigned char controlbyte);
I2C_EXT void I2CGenerateStop(void);
I2C_EXT void I2CSendByte(unsigned char data);
I2C_EXT unsigned char I2CReceByteWithACK(void);
I2C_EXT unsigned char I2CReceByteWithNAK(void);
#endif
