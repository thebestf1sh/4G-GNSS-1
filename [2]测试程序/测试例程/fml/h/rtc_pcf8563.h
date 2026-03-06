/*!	
*			\file rtc_pcf8563.h
*			\brief rtc_pcf8563驱动函数的头文件
*
*/

#ifndef _RTC_PCF8563_H_
#define _RTC_PCF8563_H_

#include "main.h"
/*器件I2C地址*/
#define PCF8563_WRITE	0XA2
#define PCF8563_READ	0XA3
/*********************************控制寄存器****************************************/
#define PCF8563_CONTROL_1 			0X00
/*		
			bit 7 ：TEST1 切换测试模式  0：正常模式，要求正常操作模式下必须置0  1：EXT_CLK测试模式
			bit 5 ：STOP	切换RTC运行与否	0：正常运行  1：好像会关闭时钟资源
			bit 3 ：TESTC 设置上电后是否会复位 0：不会复位，要求正常操作模式下必须置0		1：上电后会自动复位
*/
#define PCF8563_CONTROL_2				0X01
/*
			bit 4 ：TI_TP 似乎是控制中断使能与否 0：使能中断 	1：禁用中断，长期处于高电平
			bit 3 ：AF		报警标志相关，也分为读写两类 0：如果是读，那么报警标志不活跃，如果是写，则清除报警标志	1：如果是读，那么报警装置活跃，如果是写，报警标志也不改变
			bit 2 ：TF		同bit3的AF  只不过是time flag
			bit 1 ：AIE		alarm中断使能  0：禁用 1：使能
			bit 0 ：TIE		time中断使能	 0：禁用 1：使能
*/
/********************************日期和数据寄存器***********************************/
#define PCF8563_VL_SECONDS			0X02
/*
			bit 7 ：VL		应该是判断数据是否已经稳定 0：表示数据可靠 1：表示数据暂未OK
			bit	6..4 ：BCD码 秒的十位 0..5
			bit 3..0 ：BCD吗 秒的个位 0..9
*/
#define PCF8563_MINUTES 				0X03
/*
			bit	6..4 ：BCD码 分的十位 0..5
			bit 3..0 ：BCD吗 分的个位 0..9
*/
#define PCF8563_HOURS						0X04
/*
			bit 5..4 ：BCD码 时的十位 0..2
			nit 3..0 ：BCD吗 时的个位 0..9
*/
#define PCF8563_DAYS						0X05
/*
			bit 5..4 ：BCD码 日期的十位 0..3
			bit 3..0 ：BCD吗 日期的个位 0..9
*/
#define PCF8563_WEEKDAYS				0X06
/*
			bit 2..0 ：BCD吗 时的个位 0..6  从周日开始
*/
#define PCF8563_CENTURY_MONTHS 	0X07
/*
			bit 7 ：表示世纪 0 应该用不到......
			bit 4 ：BCD码 0..1
			bit 3..0 ：BCD码 0..9
*/
#define PCF8563_YEARS 					0X08
/*
			bit 7..4 ：BCD码 年的十位 0..9
			bit 3..0 ：BCD吗 年的个位 0..9
*/
/*********************ALARM REGISTERS 闹铃相关寄存器**********************************/
#define PCF8563_MINUTE_ALARM		0X09
/*
			bit 7 ：AE_M分钟闹铃使能与否 0 ：使能 1：禁用
			bit 6..4 ：闹铃分钟的十位
			bit 3..0 ：闹铃分钟的个位
*/
#define PCF8563_HOUR_ALARM			0X0A
/*
			bit 7 ：AE_H时钟闹铃使能与否 0 ：使能 1：禁用
			bit 6..4 ：闹铃时钟的十位
			bit 3..0 ：闹铃时钟的个位
*/
#define PCF8563_DAY_ALARM				0X0B
/*
			bit 7 ：AE_D日期闹铃使能与否 0 ：使能 1：禁用
			bit 5..4 ：闹铃日期的十位
			bit 3..0 ：闹铃日期的个位
*/
#define PCF8563_WEEKDAY_ALARM		0X0C
/*
			bit 7 ：AE_D周闹铃使能与否 0 ：使能 1：禁用
			bit 2..0 ：闹铃周
*/
/*************************CLKOUT寄存器控制和CLOCK输出************************************/
#define PCF8563_CLKOUT_CONTROL 	0X0D
/*
			bit 7 ：FE	控制CLKOUT的输出与否  0：输出被抑制，呈现为高组态  1：输出使能（默认值
			bit 1..0 ：输出的频率 
			data      freq
			00				32.768KHZ
			01				1024HZ
			10				32HZ
			11				1HZ
*/
/***************************TIME 功能****************************************************/
#define PCF8563_TIMER_CONTROL		0X0E
/*
			bit 7 ：TE	定时器使能与否 	0 ：禁用定时器（默认）  1：使能定时器
			bit 1..0 ：定时器时钟源频率选择
			data  		freq
			00				4096KHZ
			01				64HZ
			10				1HZ
			11				1/60HZ
*/
#define PCF8563_TIME						0X0F	
/*
			定时器计数值  0-255与上面的频率配合实现一定功能
*/

typedef struct
{
	uint8_t year;
	uint8_t mouth;
	uint8_t week;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t sec;
	uint8_t vl;	
}rtc_pcf8563_param;
extern rtc_pcf8563_param rtc_data;
void rtc_pcf8563_init(void);
void rtc_pcf8563_set(rtc_pcf8563_param *handle);
void rtc_pcf8563_read(rtc_pcf8563_param *handle);


#endif

