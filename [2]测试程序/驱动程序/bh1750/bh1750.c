/*!
*				\file  bh1750.c
*				\brief bh1750环境光传感器驱动程序 
*/

#include "bh1750.h"

uint8_t resolution;
uint8_t bh1750_Byte_Write(uint8_t data)
{
	I2CStart();
	I2CSendByte(BH1750_WRITE);
	I2CWaitAck();
	I2CSendByte(data);
	I2CWaitAck();
	I2CStop();
	
	return 0;
}

//BH1750读取测量数据
//返回值 成功：返回光照强度 	失败：返回0
float bh1750_Read_Measure(void)
{
	uint16_t state;
	float light;
	I2CStart();
	I2CSendByte(BH1750_READ);
	I2CWaitAck();
	state = I2CReceiveByte();
	I2CSendAck();
	state = (state<<8) +I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	light = state/1.2;
	return light;
}


//BH1750s上电
void bh1750_Power_ON(void)
{
	bh1750_Byte_Write(BH1750_POWER_ON);
}

//BH1750s断电
void bh1750_Power_OFF(void)
{
	bh1750_Byte_Write(BH1750_POWER_OFF);
}

//BH1750复位	仅在上电时有效
void bh1750_RESET(void)
{
	bh1750_Byte_Write(BH1750_RESET);
}
/*配置采集模式为1lx/bit，连续采样*/
void bh1750_config_mode(void)
{
	bh1750_Byte_Write(BH1750_CONTINUE_H_MODE); 
}
//BH1750初始化
void bh1750_Init(void)
{
	I2CInit();
	bh1750_Power_ON();
	HAL_Delay(5);
	bh1750_config_mode();
}

