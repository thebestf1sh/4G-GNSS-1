/*!
*			\file led.c
*			\brief led的驱动函数
*/

#include "aht20.h"
aht20_param aht20_data;
void aht20_init(void)
{
	I2CInit();
	
	if((aht20_read_state()&0x18)!=0x18)
	{
		aht20_start_init(); 
		HAL_Delay(10);
	}
}
	
uint8_t aht20_read_state(void)
{
	uint8_t state;
	I2CStart();
	I2CSendByte(AHT20_READ);
	I2CWaitAck();
	state = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	return state;
}

void aht20_send_ac(void)
{
	I2CStart();
	I2CSendByte(AHT20_WRITE);
	I2CWaitAck();
	I2CSendByte(AHT20_AC_CMD);
	I2CWaitAck();
	I2CSendByte(AHT20_AC_DATA_1);
	I2CWaitAck();
	I2CSendByte(AHT20_AC_DATA_2);
	I2CWaitAck();
	I2CStop();
}
	

//CRC校验类型：CRC8/MAXIM
//多项式：X8+X5+X4+1
//Poly：0011 0001  0x31
//高位放到后面就变成 1000 1100 0x8c
//C现实代码：
uint8_t Calc_CRC8(uint8_t *message,uint8_t Num)
{
        uint8_t i;
        uint8_t byte;
        uint8_t crc=0xFF;
  for(byte=0; byte<Num; byte++)
  {
    crc^=(message[byte]);
    for(i=8;i>0;--i)
    {
      if(crc&0x80) crc=(crc<<1)^0x31;
      else crc=(crc<<1);
    }
  }
        return crc;
}

void aht20_para_init(aht20_param *handle)
{
	uint8_t i;
	handle->humi = 0;
	handle->temp = 0;
	handle->humi_data = 0;
	handle->temp_data = 0;
	for(i=0;i<8;i++)
	{
		handle->data[i] = 0;
	}
}

void aht20_read_data(aht20_param *handle)
{
	aht20_para_init(handle);
	aht20_send_ac();
	HAL_Delay(80);
	
	while(((aht20_read_state()&0x80)==0x80))//直到状态bit[7]为0，表示为空闲状态，若为1，表示忙状态
	{
		HAL_Delay(10);
	}
	
	I2CStart();
	I2CSendByte(AHT20_READ);
	I2CWaitAck();
	handle->data[0] = I2CReceiveByte();
	I2CSendAck();
	handle->data[1] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[2] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[3] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[4] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[5] = I2CReceiveByte();
	I2CSendNotAck();	
	I2CStop();
	
	handle->humi |= handle->data[1]<<16;
	handle->humi |= handle->data[2]<<8;
	handle->humi |= handle->data[3];
	handle->humi = handle->humi>>4;
	handle->humi_data = (handle->humi*100.0)/1048575.0;
	
	handle->temp |= handle->data[3]<<16;
	handle->temp |= handle->data[4]<<8;
	handle->temp |= handle->data[5];
	handle->temp = handle->temp&0xfffff;
	handle->temp_data = (handle->temp*200.0)/1048575.0-50.0;
	
}

void aht20_read_data_crc(aht20_param *handle)
{
	aht20_para_init(handle);
	aht20_send_ac();
	HAL_Delay(80);
	
	while(((aht20_read_state()&0x80)==0x80))//直到状态bit[7]为0，表示为空闲状态，若为1，表示忙状态
	{
		HAL_Delay(10);
	}
	
	I2CStart();
	I2CSendByte(AHT20_READ);
	I2CWaitAck();
	handle->data[0] = I2CReceiveByte();
	I2CSendAck();
	handle->data[1] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[2] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[3] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[4] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[5] = I2CReceiveByte();
	I2CSendAck();	
	handle->data[6] = I2CReceiveByte();
	I2CSendNotAck();	
	I2CStop();	
	if(Calc_CRC8(handle->data,6)==handle->data[6])	
	{
		handle->humi |= handle->data[1]<<16;
		handle->humi |= handle->data[2]<<8;
		handle->humi |= handle->data[3];
		handle->humi = handle->humi>>4;
		handle->humi_data = (handle->humi*100.0)/1048575.0;
		
		handle->temp |= handle->data[3]<<16;
		handle->temp |= handle->data[4]<<8;
		handle->temp |= handle->data[5];
		handle->temp = handle->temp&0xfffff;
		handle->temp_data = (handle->temp*200.0)/1048575.0-50.0;
	}
	
}

void ath20_reset_reg(uint8_t addr)
{
	uint8_t data[4];
	I2CStart();
	I2CSendByte(AHT20_WRITE);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	I2CSendByte(0x00);
	I2CWaitAck();
	I2CSendByte(0x00);
	I2CWaitAck();
	I2CStop();

	HAL_Delay(5);//延时5ms左右
	I2CStart();
	I2CSendByte(AHT20_READ);//
	I2CWaitAck();
	data[0] = I2CReceiveByte();
	I2CSendAck();
	data[1] = I2CReceiveByte();
	I2CSendAck();
	data[2] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
  HAL_Delay(10);//延时10ms左右
	I2CStart();
	I2CSendByte(AHT20_WRITE);///
	I2CWaitAck();
	I2CSendByte(0xB0|addr);////寄存器命令
	I2CWaitAck();
	I2CSendByte(data[1]);
	I2CWaitAck();
	I2CSendByte(data[2]);
	I2CWaitAck();
	I2CStop();
	data[1] = 0x00;
	data[2] = 0x00;
	
}


void aht20_start_init(void)
{
	ath20_reset_reg(0x1b);
	ath20_reset_reg(0x1c);
	ath20_reset_reg(0x1e);
}









