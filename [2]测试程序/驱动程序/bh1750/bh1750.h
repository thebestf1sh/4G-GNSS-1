/*!
*			\file bh1750.h
*			\brief bh1750光照传感器驱动头文件
*/

#ifndef __BH1750_H
#define __BH1750_H

#include "main.h"

//BH1750的地址 硬件配置I2C地址引脚 ADDR 接地
#define BH1750_WRITE							0x46			
#define BH1750_READ								0X47

//BH1750指令码
#define BH1750_POWER_OFF					0x00			
#define BH1750_POWER_ON						0x01
#define BH1750_RESET							0x07	
#define	BH1750_CONTINUE_H_MODE		0x10		//以1lx分辨率开始测量，测量时间通常为120ms
#define BH1750_CONTINUE_H_MODE2		0x11		//以0.5lx分辨率开始测量，测量时间通常为120ms
#define BH1750_CONTINUE_L_MODE		0x13		//以4lx分辨率开始测量，测量时间通常为16ms
#define BH1750_ONE_TIME_H_MODE		0x20		//以1lx分辨率开始测量，测量时间通常为120ms,完成后掉电
#define BH1750_ONE_TIME_H_MODE2		0x21		//以0.5lx分辨率开始测量，测量时间通常为120ms,完成后掉电
#define OBH1750_NE_TIME_L_MODE		0x23		//以4lx分辨率开始测量，测量时间通常为120ms,完成后掉电


uint8_t bh1750_Byte_Write(uint8_t data);
void bh1750_Power_ON(void);
void bh1750_config_mode(void);
float bh1750_Read_Measure(void);



void bh1750_Init(void);




#endif
