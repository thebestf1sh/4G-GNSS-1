/*!	
*			\file lsm6ds3tr.h
*			\brief lsm6ds3tr驱动函数的头文件
*
*/

#ifndef _LSM6DS3TR_H_
#define _LSM6DS3TR_H_

#include "main.h"

#define LSM6DS3TR_ADDRESS                 0x6B
#define LSM6DS3TR_READ                    0xD5
#define LSM6DS3TR_WRITE                   0xD4

#define FUNC_CFG_ACCESS										0x01			//bit 7 : 0 正常模式	1扩展功能模式
#define SENSOR_SYNC_TIME_FRAME						0x04
#define	FIFO_WATERMARK_SET								0x06			//设置fifo的阈值，最小分辨率为两字节
#define	FIFO_CTRL2												0x07
/*			bit 7 ：在存入fifo数据时，设置是(1)否(0)将时间戳也写入fifo中
*				bit 6 ：fifo写入的模式选择 0：基于XL/Gyro 数据准备好的条件允许写入 1：步数计数器的每次检测都允许写入
*				bit 0..3 ：fifo阈值的高4四位，总共是12位的fifo阈值*/
#define	FIFO_DECIMATION_SET								0x08
/*			bit 3..5	陀螺仪的fifo的抽取因子设置
*				bit	0..2	加速度传感器的fifo的抽取因子设置						*/
#define	FIFO_CTRL4												0x09
#define	FIFO_CTRL5												0x0A			//设置fifo的输出数据速率，以及模式
#define	ORIENT_CFG_G											0x0B			//xyz轴加速度传感器的一些配置，默认值0x00就可以
#define INT1_CTRL													0x0D			//同下面INT2
#define INT2_CTRL													0x0E		
#define	CHIP_ID														0x0F			//芯片ID
#define	CTRL1_XL													0x10			//加速度传感器设置输出速率，不设置就无输出，fs选择加速度计，bw选择滤波器的带宽
#define	CTRL2_G														0x11			//陀螺仪的输出速率以及FS
#define	CTRL3_C														0x12
/*			bit 7 ：boot 0 正常模式 1reboot memory content
*				bit 6 ：bdu	block data updata		0 持续更新寄存器 1直到LSB与MSB都被读出之后再更新
*				bit 5 ：中断输出高电平还是低电平，0 高电平  1 低电平
*				bit 4 ：设置推挽输出(0)还是开漏输出(1)
*				bit 3 ：SPI工作模式选择e
*				bit 2 ：I2C与SPI访问寄存器时候递增（需要），默认为1（enable）
*				bit 1 ：数据大小端模式 ，0小端模式 1大端模式
*				bit 0 ：软复位，默认为0，置1时候复位，复位后置0				*/
#define	CTRL4_C														0x13
/*			bit 7 ：加速度传感器的带宽选择 0 由ODR确定 1 由0X10寄存器中的BW_XL[1:0] 
*				bit 6 ：陀螺仪睡眠模式使能			默认为0 不使能
*				bit 5 ：中断输出全由INT1或者INT1和INT2都有
*				bit 4 ：使能温度传感器为第四个存入fifo的值吗，默认为0，不使能
*				bit 3 ：数据准备输出遮掩，如果使能的话，会直到传感器滤波结束后才能被读到
*				bit 2 ：i2c是否使能，默认为0，切勿更改
*				bit 0 ：允许fifo阈值的设置，默认为0，不设限制 			*/
#define	CTRL5_C														0x14
/*			bit 5..7 ：输出寄存器舍入模式
*				bit 2..3 ：角速度传感器自检模式
*				bit 0..1 ：线性加速度传感器自检模式		*/
#define	CTRL6_C														0x15
/*			bit 7 ：陀螺仪的一个edge-sensitvi trigger 使能
*				bit 6 ：陀螺仪的一个level-sensitvi trigger 使能
*				bit 5 ：陀螺仪的一个level-sensitive	latched 使能
*				bit 4 ：加速度传感器高性能模式的使能与否											*/
#define	CTRL7_C														0x16
/*			bit 7 ：陀螺仪的高性能模式的是能与否
*				bit 6 ：陀螺仪的数字高通滤波器的使能与否
*				bit 3 ：陀螺仪的数字高通滤波器的复位
*				bit 2 ：源寄存器的舍入功能的使能
*				bit 4..5 ：陀螺仪的数字高通滤波器的截止频率*/
#define	CTRL8_XL														0x17
/*			bit 7 ：加速度传感器低通滤波器LPF2的选择
*				bit 5..6 ：加速度传感器的斜率滤波器和高通滤波器的配置和截止频率
*				bit 2 ：加速度斜率滤波器/高通滤波器选择
*				bit 0 ：对六轴功能低通滤波器的选择*/
#define	CTRL9_XL														0x18
/*			bit 5 ：加速度传感器输出的z轴使能
*				bit 4 ：加速度传感器输出的Y轴使能
*				bit 3 ：加速度传感器输出的x轴使能
*				bit 2 ：启用磁强计软铁校正算法(1)。 需求0x1a中的IRON_EN bit 置1
*/
#define	CTRL10_C														0x19						
/*			bit 5 ：惯性传感器输出的z轴使能
*				bit 4 ：惯性传感器输出的Y轴使能
*				bit 3 ：惯性传感器输出的x轴使能
*				bit 2 ：启用嵌入式功能（计步器，倾斜，显著运动等）以及加速度传感器的HP和LPF2滤波器
*				bit 1 ：复位步数的计数
*				bit 0 ：启用显著运动功能
*/
#define MASTER_CONFIG												0x1A	//主配置寄存器
#define WAKE_UP_SRC													0x1B	//唤醒中断资源寄存器
#define TAP_SRC															0x1C  //节拍资源寄存器
#define D6D_SRC															0x1D	//纵向，横向，正面和正面向下的源寄存器
#define STATUS_REG													0x1E 	//状态寄存器

#define OUT_TEMP_L													0x20	//温度传感器的值
#define OUT_TEMP_H													0x21

#define OUTX_L_G														0x22	//角速度传感器X轴的值
#define OUTX_H_G														0x23

#define OUTY_L_G														0x24	//角速度传感器Y轴的值
#define OUTY_H_G														0x25

#define OUTZ_L_G														0x26	//角速度传感器Z轴的值
#define OUTZ_H_G														0x27

#define OUTX_L_XL														0x28	//线性加速度传感器X轴的值
#define OUTX_H_XL														0x29
	
#define OUTY_L_XL														0x2a	//线性加速度传感器Y轴的值
#define OUTY_H_XL														0x2b

#define OUTZ_L_XL														0x2c	//线性加速度传感器Z轴的值
#define OUTZ_H_XL														0x2d



uint8_t LSM6DS3TR_read_data(uint8_t address);
void LSM6DS3TR_write_data(uint8_t address,uint8_t data);
void LSM6DS3TR_init(void);

#endif

