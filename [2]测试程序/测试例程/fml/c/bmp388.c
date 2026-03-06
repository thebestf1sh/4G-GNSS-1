/*!
*			\file bmp388.c
*			\brief bmp388的驱动函数
*/

#include "bmp388.h"

output_compensation bmp388_compensation;

/*!
*		\brief 读取单个寄存器里的数据
*/
uint8_t bmp388_read_data(uint8_t address)
{
	uint8_t state;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(address);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	state = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	return state;
}

/*!
*		\brief 向单个寄存器写入数据
*/
void bmp388_write_data(uint8_t address,uint8_t data)
{
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(address);
	I2CWaitAck();
	I2CSendByte(data);
	I2CWaitAck();
	I2CStop();
}

/*!
*		\brief 读取芯片 ID 默认值是0x50
*/
uint8_t bmp388_read_chip_id(void)
{
	return bmp388_read_data(BMP388_CHIP_ID);
}
	
/*!
*		\brief 取错误信息
*/
uint8_t bmp388_read_error(void)
{
	return bmp388_read_data(BMP388_ERR_REG);
}

/*!
*		\BRIEF 取命令解码器状态
*/
uint8_t bmp388_read_state(void)
{
	return bmp388_read_data(BMP388_STATE);
}

/*!
*		\brief 取压力数据
*/
uint32_t bmp388_read_press(void)
{
	uint8_t data[3];
	uint32_t pressure;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(BMP388_DATA_0);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	data[0] = I2CReceiveByte();
	I2CSendAck();
	data[1] = I2CReceiveByte();
	I2CSendAck();
	data[2] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	pressure = data[0]+data[1]*256+data[2]*65536;
	return pressure ;
}

/*!
*		\brief 取温度数据
*/
uint32_t bmp388_read_temper(void)
{
	uint8_t data[3];
	uint32_t temper;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(BMP388_DATA_3);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	data[0] = I2CReceiveByte();
	I2CSendAck();
	data[1] = I2CReceiveByte();
	I2CSendAck();
	data[2] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	temper = data[0]+data[1]*256+data[2]*65536;
	return temper ;
}
/*!
*		\brief 取时间数据
*/
uint32_t bmp388_read_time(void)
{
	uint8_t data[3];
	uint32_t time;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(BMP388_SENSOR_TIME_0);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	data[0] = I2CReceiveByte();
	I2CSendAck();
	data[1] = I2CReceiveByte();
	I2CSendAck();
	data[2] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	time |= data[0];
	time |= data[1]<<8;
	time |= data[2]<<16;
	return time ;
}


/*!
*		\brief get event
*/
uint8_t bmp388_get_event(void)
{
	return bmp388_read_data(BMP388_EVENT);
}

/*!
*		\brief 获取中断的类型
*/
uint8_t bmp388_get_int_state(void)
{
	return bmp388_read_data(BMP388_INT_STATE);
}

/*!
*		\brief 获取fifo中的数据的长度
*/
uint16_t bmp388_read_fifo_length(void)
{
	uint8_t data[2];
	uint16_t length;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(BMP388_FIFO_LENGTH_0);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	data[0] = I2CReceiveByte();
	I2CSendAck();
	data[1] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	length |= data[0];
	length |= data[1]<<8;
	return length ;
}

/*!
*		\brief 获取fifo中的数据
*/
uint8_t bmp388_get_fifo_data(void)
{
	return bmp388_read_data(BMP388_FIFO_DATA);
}

/*!
*		\brief 设置fifo的water mark
*/
void bmp388_write_wtm(uint16_t mark)
{
	bmp388_write_data(BMP388_FIFO_WTM_0,(mark&0xff));
	bmp388_write_data(BMP388_FIFO_WTM_1,(mark>>8&0x01));
}
/*!
*		\brief 获取设置的fifo watermark
*/
uint16_t bmp388_read_wtm(void)
{
	uint8_t data[2];
	uint16_t wtm;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(BMP388_FIFO_WTM_0);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	data[0] = I2CReceiveByte();
	I2CSendAck();
	data[1] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	wtm |= data[0];
	wtm |= data[1]<<8;
	return wtm ;	
}
/*! 
*		\brief 设置fifo contorl 1
*/
void bmp388_write_fifo_control_1(uint8_t data)
{
	bmp388_write_data(BMP388_FIFO_CONTROL_1,data);
}

/*!
*		\brief 获取fifo contorl 1
*/
uint8_t bmp388_read_fifo_control_1(void)
{
	return bmp388_read_data(BMP388_FIFO_CONTROL_1);
}

/*! 
*		\brief 设置fifo contorl 2
*/
void bmp388_write_fifo_control_2(uint8_t data)
{
	bmp388_write_data(BMP388_FIFO_CONTROL_2,data);
}

/*!
*		\brief 获取fifo contorl 2
*/
uint8_t bmp388_read_fifo_control_2(void)
{
	return bmp388_read_data(BMP388_FIFO_CONTROL_2);
}

/*! 
*		\brief 设置int control
*/
void bmp388_write_int_control(uint8_t data)
{
	bmp388_write_data(BMP388_INT_CONTROL,data);
}

/*!
*		\brief 获取int control
*/
uint8_t bmp388_read_int_control(void)
{
	return bmp388_read_data(BMP388_INT_CONTROL);
}

/*! 
*		\brief 设置if config
*/
void bmp388_write_if_control(uint8_t data)
{
	bmp388_write_data(BMP388_IF_CONFIG,data);
}

/*!
*		\brief 获取if config
*/
uint8_t bmp388_read_if_control(void)
{
	return bmp388_read_data(BMP388_IF_CONFIG);
}

/*! 
*		\brief 设置power control
*/
void bmp388_write_power_control(uint8_t data)
{
	bmp388_write_data(BMP388_POWER_CONTROL,data);
}

/*!
*		\brief 获取power control
*/
uint8_t bmp388_read_power_control(void)
{
	return bmp388_read_data(BMP388_POWER_CONTROL);
}

/*! 
*		\brief 设置osr
*/
void bmp388_write_osr(uint8_t data)
{
	bmp388_write_data(BMP388_OSR,data);
}

/*!
*		\brief 获取osr
*/
uint8_t bmp388_read_osr(void)
{
	return bmp388_read_data(BMP388_OSR);
}

/*! 
*		\brief 设置odr
*/
void bmp388_write_odr(uint8_t data)
{
	bmp388_write_data(BMP388_ODR,data);
}

/*!
*		\brief 获取odr
*/
uint8_t bmp388_read_odr(void)
{
	return bmp388_read_data(BMP388_ODR);
}

/*! 
*		\brief 设置iir滤波器系数
*/
void bmp388_write_config(uint8_t data)
{
	bmp388_write_data(BMP388_CONFIG,data);
}

/*!
*		\brief 获取iir滤波器系数
*/
uint8_t bmp388_read_config(void)
{
	return bmp388_read_data(BMP388_CONFIG);
}

/*! 
*		\brief 设置iir滤波器系数
*/
void bmp388_write_cmd(uint8_t data)
{
	bmp388_write_data(BMP388_CMD,data);
}

/*!
*		\brief 获取补偿参数
*/
void bmp388_read_compensation_data(output_compensation *handle)
{
	uint8_t data[21];
	uint8_t i;
	I2CStart();
	I2CSendByte(BMP388_WRITE);
	I2CWaitAck();
	I2CSendByte(BMP388_COMPENSATION_1);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(BMP388_READ);
	I2CWaitAck();
	for(i=0;i<20;i++)
	{
		data[i] = I2CReceiveByte();
		I2CSendAck();
	}
	data[20] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
	
	handle->t1 |= data[0];
	handle->t1 |= data[1]<<8;
	handle->ft1 = (float)(handle->t1 * 256.0);
	
	handle->t2 |= data[2];
	handle->t2 |= data[3]<<8;	
	handle->ft2 = (float)(handle->t2 / 1073741824.0);
	
	handle->t3 =  data[4];
	handle->ft3 = (float)(handle->t3/ 281474976710656.0);
	
	handle->p1 |= data[5];
	handle->p1 |= data[6]<<8;
	handle->fp1 = (float)((handle->p1 - 16384)/1048576.0);
	
	handle->p2 |= data[7];
	handle->p2 |= data[8]<<8;		
	handle->fp2 = (float)((handle->p2 - 16384)/536870912.0);
	
	handle->p3 =  data[9];
	handle->fp3 = (float)(handle->p3 / 4294967296.0);

	handle->p4 =  data[10];	
	handle->fp4 = (float)(handle->p4 / 137438953472.0);
	
	handle->p5 |= data[11];
	handle->p5 |= data[12]<<8;
	handle->fp5 = (float)(handle->p5 * 8.0);
	
	handle->p6 |= data[13];
	handle->p6 |= data[14]<<8;		
	handle->fp6 = (float)(handle->p6 / 64.0);
	
	handle->p7 =  data[15];
	handle->fp7 = (float)(handle->p7 / 256.0);
	
	handle->p8 =  data[16];		
	handle->fp8 = (float)(handle->p8 / 32768.0);
	
	handle->p9 |= data[17];
	handle->p9 |= data[18]<<8;		
	handle->fp9 = (float)(handle->p9 / 281474976710656.0);
	
	handle->p10 =  data[19];
	handle->fp10 = (float)(handle->p10/ 281474976710656.0);
	
	handle->p11 =  data[20];		
	handle->fp11 = (float)(handle->p11 / 36893488147419103232.0);
}

/*!
*		\brief 修正温度
*/
float compensate_temperature(uint32_t tem)
{
    float partial_data1;
    float partial_data2;

		partial_data1 = (float)(tem-bmp388_compensation.ft1);
		partial_data2 = (float)(partial_data1*bmp388_compensation.ft2);
	
		bmp388_compensation.t_lin = partial_data2+(partial_data1*partial_data1)*bmp388_compensation.ft3;
	
		return bmp388_compensation.t_lin;
}

float  compensate_pressure(uint32_t pressure)
{
  float comp_pressure;
	float partial_data1;
	float partial_data2;
	float partial_data3;
	float partial_data4;
	float partial_out1;
	float partial_out2;

	partial_data1 = bmp388_compensation.fp6*bmp388_compensation.t_lin;
	partial_data2 = bmp388_compensation.fp7*(bmp388_compensation.t_lin*bmp388_compensation.t_lin);
	partial_data3 = bmp388_compensation.fp8*(bmp388_compensation.t_lin*bmp388_compensation.t_lin*bmp388_compensation.t_lin);
	partial_out1 = bmp388_compensation.fp5+partial_data1+partial_data2+partial_data3;

	partial_data1 = bmp388_compensation.fp2*bmp388_compensation.t_lin;
	partial_data2 = bmp388_compensation.fp3*(bmp388_compensation.t_lin*bmp388_compensation.t_lin);
	partial_data3 = bmp388_compensation.fp4*(bmp388_compensation.t_lin*bmp388_compensation.t_lin*bmp388_compensation.t_lin);
	partial_out2 = (float)pressure*(bmp388_compensation.fp1+partial_data1+partial_data2+partial_data3);
	
	partial_data1 = (float)pressure*(float)pressure;
	partial_data2 = bmp388_compensation.fp9+bmp388_compensation.fp10*bmp388_compensation.t_lin;
	partial_data3 = partial_data2*partial_data1;
	partial_data4 = partial_data3+((float)pressure*(float)pressure*(float)pressure)*bmp388_compensation.fp11;
	comp_pressure = partial_out1+partial_out2+partial_data4;
  return comp_pressure;
}
/*!
*		\brief bmp388 gpio init
*/
uint8_t bmp388_init(void)
{
	uint8_t data;
	I2CInit();
	
	if(bmp388_read_chip_id()!=0x50)
	{
		/*I2C通讯失败*/
		return 1;
	}
	/*软复位*/
	bmp388_write_cmd(BMP388_CMD_SR);
	/*等待复位完成*/
	while(bmp388_get_event() == 1);
	/*禁用fifo*/
	bmp388_write_fifo_control_1(0x00);
	/*配置中断*/
	data = 0x42;
	bmp388_write_int_control(data);
	/*配置spi与看门狗*/
	data = 0x00;
	bmp388_write_if_control(data);
	/*配置工作模式*/
	data = 0x33;
	bmp388_write_power_control(data);
	/*配置分辨率*/
	data = 0x13;
	bmp388_write_osr(data);
	/*配置iir filter*/
	data = 0x02;
	bmp388_write_config(data);
	/*配置输出频率*/
	data = 0x04;
	bmp388_write_odr(data);
	/*获取输出补偿参数*/
	bmp388_read_compensation_data(&bmp388_compensation);
	return 0;
}


