/*!
*			\file rtc_pcf8563.c
*			\brief rtc_pcf8563的驱动函数
*/

#include "rtc_pcf8563.h"
#include "i2c.h"

rtc_pcf8563_param rtc_data;

/*!
*		\brief rtc init
*/
void rtc_pcf8563_init(void)
{
	I2CInit();
}
/*!
*		\brief 读取单个寄存器里的数据
*/
uint8_t rtc_pcf8563_read_data(uint8_t address)
{
	uint8_t state;
	I2CStart();
	I2CSendByte(PCF8563_WRITE);
	I2CWaitAck();
	I2CSendByte(address);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(PCF8563_READ);
	I2CWaitAck();
	state = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	return state;
}

/*!
*		\brief 向单个寄存器写入数据
*/
void rtc_pcf8563_write_data(uint8_t address,uint8_t data)
{
	I2CStart();
	I2CSendByte(PCF8563_WRITE);
	I2CWaitAck();
	I2CSendByte(address);
	I2CWaitAck();
	I2CSendByte(data);
	I2CWaitAck();
	I2CStop();
}


void rtc_pcf8563_read(rtc_pcf8563_param *handle)
{
	I2CStart();
	I2CSendByte(PCF8563_WRITE);
	I2CWaitAck();
	I2CSendByte(PCF8563_VL_SECONDS);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(PCF8563_READ);
	I2CWaitAck();

	handle->sec= I2CReceiveByte();
	I2CSendAck();
	handle->minute= I2CReceiveByte();
	I2CSendAck();
	handle->hour= I2CReceiveByte();
	I2CSendAck();
	handle->day= I2CReceiveByte();
	I2CSendAck();	
	handle->week= I2CReceiveByte();
	I2CSendAck();	
	handle->mouth= I2CReceiveByte();
	I2CSendAck();
	handle->year= I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();	
	handle->vl = handle->sec>>7;
	handle->sec = handle->sec & 0x7f;
	handle->minute = handle->minute & 0x7f;
	handle->hour = handle->hour & 0x3f;
	handle->day = handle->day & 0x3f;
	handle->week = handle->week & 0x07;
	handle->mouth = handle->mouth & 0x1f;
	handle->year = handle->year & 0xff;
}

void rtc_pcf8563_set(rtc_pcf8563_param *handle)
{
	rtc_pcf8563_write_data(PCF8563_YEARS,handle->year);
	rtc_pcf8563_write_data(PCF8563_CENTURY_MONTHS,handle->mouth);
	rtc_pcf8563_write_data(PCF8563_WEEKDAYS,handle->week);
	rtc_pcf8563_write_data(PCF8563_DAYS,handle->day);
	rtc_pcf8563_write_data(PCF8563_HOURS,handle->hour);
	rtc_pcf8563_write_data(PCF8563_MINUTES,handle->minute);
	rtc_pcf8563_write_data(PCF8563_VL_SECONDS,handle->sec);
}



