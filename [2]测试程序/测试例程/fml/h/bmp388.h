/*!	
*			\file bmp388.h
*			\brief bmp388驱动函数的头文件
*
*/

#ifndef _BMP388_H_
#define _BMP388_H_

#include "main.h"

#define BMP388_ADDRESS 				0X76
#define BMP388_READ  					0XED
#define BMP388_WRITE					0XEC



/*中断引脚*/
#define BMP388_INT	GPIO_PIN_4
/*工作模式*/
#define BMP388_SLEEP_MODE 		0X00			//不进行测量
#define BMP388_FORCED_MODE		0X01			//测量一次之后就进入睡眠模式
#define BMP388_NORMAL_MODE		0X03			//正常的周期性测量
/*memory map*/
#define BMP388_CHIP_ID				0X00			//默认值0x50

#define BMP388_ERR_REG				0X02			
/*			bit 0 : fatal error 致命错误
*				bit 1 :	command execution error 命令执行错误，读后就清除
*				bit 2 :	sensor configuration error detected 检测传感器配置错误，读后就清除
*/
#define BMP388_STATE					0X03
/*			bit 4 ：CMD decoder statue 命令解码器的状态，0 命令正在进行 1 准备好接收下一条指令了
*				bit 5 ：data ready for pressure 压力数据准备好了，读取后复位
*				bit 6 ：data ready for temperature 温度数据准备好了，读取后复位
*/
#define BMP388_DATA_0					0X04			//press_7_0	        压力数据		
#define BMP388_DATA_1					0X05			//press_15_8				
#define BMP388_DATA_2					0X06			//press_23_16
#define BMP388_DATA_3					0X07			//temper_7_0				温度数据
#define BMP388_DATA_4					0X08			//temper_15_8
#define BMP388_DATA_5					0X09			//temper_23_16
#define BMP388_SENSOR_TIME_0	0X0C			//sensor_time_7_0		传感器时间（数据生成的时间？
#define BMP388_SENSOR_TIME_1	0X0D			//sensor_time_15_8
#define BMP388_SENSOR_TIME_2	0X0E			//sensor_time_23_16
#define BMP388_EVENT					0X10			//bit 0 : 在上电或者软复位后会置1 ，读后清除
#define BMP388_INT_STATE			0X11
/*			bit 0	：FIFO Watermark interrupt 
*				bit 1 ：FIFO full interrupt
*				bit 3 ：data ready interrupt
*/
#define BMP388_FIFO_LENGTH_0	0X12			//fifo_length_7_0
#define BMP388_FIFO_LENGTH_1	0X13			//fifo_length_15_8
#define BMP388_FIFO_DATA			0X14			//fifo read data
#define BMP388_FIFO_WTM_0			0X15			//fifo_wtm_7_0
#define BMP388_FIFO_WTM_1			0X16			//fifo_wtm_8
#define BMP388_FIFO_CONTROL_1	0X17
/*			bit 0 : fifo mode 使能或者禁用fifo 0 disable 1 enable
*				bit 1 ：fifo stop on full	使能或者禁用当fifo满了之后停止写入 0 diasble 1 enable
*				bit 2 ：fifo time en 在上一个数据帧后发送时间帧 0 disable 1 enable
*				bit 3 ：fifo press en 将压力数据存入fifo中 0 disable 1 enable
*				bit 4 ：fifo temper en 将温度数据存入fifo中 0 disable 1 enable
*/
#define BMP388_FIFO_CONTROL_2	0X18
/*			bit 2..0 ：fifo subsampling fifo采样次数，次数为2^（bit 2..0）
*				bit 4..3 ：data select 选择数据来源，0 未经过滤波的原始数据 1 滤波后的数据 2/3 保留，同0
*/
#define BMP388_INT_CONTROL		0X19
/*			bit 0 ：int od 配置int引脚的输出模式 0 推挽输出	1 开漏输出
*				bit 1 ：int level 配置int引脚的 0 active_low 1 active_high
*				bit 2 ：int latch int引脚和int状态寄存器的锁存 0 disable 1 enable 
*				bit 3 ：fwtm en 使能或者禁用 fifo watermark 中断 0 disable 1 enable
*				bit 4 ：ffull en 使能或者禁用 fifo full 中断 0 disable 1 enable
*				bit 6 ：drdy en 使能或者禁用 data ready 中断 0 disable 1 enable
*/
#define BMP388_IF_CONFIG			0X1A
/*			bit 0 ：spi interface mode 配置 spi的模式  0 spi4 1 spi3 
*				bit 1 ：i2c wdt en 启用由NVM支持的i2c看门狗定时器 0	disable 1 enable 
*				bit 2 ：i2c wdt sel 选择看门狗超时时间 0 1.25ms 1 40ms
*/
#define BMP388_POWER_CONTROL	0X1B
/*			bit 0 ：press en 使能或者禁用压力传感器 0 diable 1 enable
*				bit 1 ：temper en 使能或者禁用温度传感器 0 disable 1 enable 
*				bit 5..4 ：mode  设置工作模式 00 slee  11 normal  01/10 forced mode
*/
#define BMP388_OSR						0X1C
/*			osr ：over sampling register 过采样配置寄存器
*				bit 2..0 ：osr_p 压力的过采样配置寄存器 采样率为 2^(bit 2..0)
*				bit 5..3 ：osr_p 温度的过采样配置寄存器 采样率为 2^(bit 5..3)
*/
#define BMP388_ODR						0X1D
/*			odr ：out data register 输出数据寄存器
*				bit 4..0 ：取值范围是0-17 其他超出值默认为17 2^(bit 4..0)   输出频率
*									0 = 200 hz  5ms   1 = 100 hz  10ms  2 = 50hz 20ms  依次类推
*/
#define BMP388_CONFIG					0X1F
/*			bit 3..1 ：配置iir滤波器系数   
*									系数 = 2^(bit 3..1) - 1 
*/
#define BMP388_CMD						0X7E
#define BMP388_CMD_NOP				0X00
#define BMP388_CMD_EXTMODE		0X34
#define BMP388_CMD_FLUSH_FIFO	0X50
#define BMP388_CMD_SR					0XB6
/*			发送控制命令
*				0x00 nop  保留
*				0x34 extmode en middle 
*				0x50 fifo flush 在不更改fifo config的情况下冲刷fifo中的所有数据
*				0xb6 softreset 软复位，所有的配置都将被回复为默认值
*/
#define BMP388_COMPENSATION_1	0X31
typedef struct
{
	uint16_t 	t1;
	uint16_t 	t2;
	int8_t 		t3;
	
	float 	t_lin;
	
	int16_t 	p1;
	int16_t 	p2;
	int8_t 		p3;
	int8_t 		p4;
	uint16_t 	p5;
  uint16_t 	p6;
	int8_t 		p7;
	int8_t 		p8;	
	int16_t 	p9;
	int8_t 		p10;
	int8_t 		p11;	
	
	float ft1;
	float ft2;
	float ft3;
	
	float fp1;
	float fp2;
	float fp3;
	float fp4;
	float fp5;
	float fp6;
	float fp7;
	float fp8;
	float fp9;
	float fp10;
	float fp11;
}output_compensation;

extern output_compensation bmp388_compensation;


uint8_t bmp388_init(void);

uint8_t bmp388_read_data(uint8_t address);
void bmp388_write_data(uint8_t address,uint8_t data);

uint8_t bmp388_read_chip_id(void);

uint8_t bmp388_read_error(void);

uint8_t bmp388_read_state(void);

uint32_t bmp388_read_press(void);

uint32_t bmp388_read_temper(void);

uint32_t bmp388_read_time(void);

uint8_t bmp388_get_event(void);

uint8_t bmp388_get_int_state(void);

uint16_t bmp388_read_fifo_length(void);
uint8_t bmp388_get_fifo_data(void);

void bmp388_write_wtm(uint16_t mark);
uint16_t bmp388_read_wtm(void);

void bmp388_write_fifo_control_1(uint8_t data);
uint8_t bmp388_read_fifo_control_1(void);

void bmp388_write_fifo_control_2(uint8_t data);
uint8_t bmp388_read_fifo_control_2(void);

void bmp388_write_int_control(uint8_t data);
uint8_t bmp388_read_int_control(void);

void bmp388_write_if_control(uint8_t data);
uint8_t bmp388_read_if_control(void);

void bmp388_write_power_control(uint8_t data);
uint8_t bmp388_read_power_control(void);

void bmp388_write_osr(uint8_t data);
uint8_t bmp388_read_osr(void);

void bmp388_write_odr(uint8_t data);
uint8_t bmp388_read_odr(void);

void bmp388_write_config(uint8_t data);
uint8_t bmp388_read_config(void);

void bmp388_write_cmd(uint8_t data);

void bmp388_read_compensation_data(output_compensation *handle);
	
float compensate_temperature(uint32_t tem);
float compensate_pressure(uint32_t pressure);
#endif

