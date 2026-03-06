/*!
*			\file lsm6ds3tr.c
*			\brief lsm6ds3tr的驱动函数
*/

#include "lsm6ds3tr.h"

/*!
*		\brief 读取单个寄存器里的数据
*/
uint8_t LSM6DS3TR_read_data(uint8_t address)
{
	uint8_t state;
	I2CStart();
	I2CSendByte(LSM6DS3TR_WRITE);
	I2CWaitAck();
	I2CSendByte(address);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(LSM6DS3TR_READ);
	I2CWaitAck();
	state = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	return state;
}

/*!
*		\brief 向单个寄存器写入数据
*/
void LSM6DS3TR_write_data(uint8_t address,uint8_t data)
{
	I2CStart();
	I2CSendByte(LSM6DS3TR_WRITE);
	I2CWaitAck();
	I2CSendByte(address);
	I2CWaitAck();
	I2CSendByte(data);
	I2CWaitAck();
	I2CStop();
}

/*!
*		\brief key gpio init
*/	
void LSM6DS3TR_init(void)
{
	I2CInit();
	LSM6DS3TR_write_data(CTRL1_XL,0X60);
	LSM6DS3TR_write_data(CTRL2_G,0X60);	
}













