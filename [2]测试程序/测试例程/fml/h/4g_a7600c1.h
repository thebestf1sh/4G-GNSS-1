/*!	
*			\file 4g_a7600c1.h
*			\brief 4g模块驱动函数的头文件
*
*/

#ifndef _4G_A7600C1_H_
#define _4G_A7600C1_H_

#include "main.h"
typedef struct
{
	uint8_t a7600c1_rx[256];
	uint8_t length ;
}a7600c1_rx_data;

typedef struct
{	/*BCD码*/
	uint16_t year;
	uint16_t mouth;
	uint16_t day;
	uint16_t hour;
	uint16_t minute;
	uint16_t sec;
	uint16_t time_zone;
}real_time_data;




typedef struct
{
	/*V.25TER 参数    NULL */
	
	/*status_control 参数*/
	uint8_t functionality_level;
	real_time_data	real_time;
	
	
	uint8_t cgreg;
	uint8_t cereg;
	uint8_t cgatt;
	
	uint8_t ping_baidu_result;
	
	uint8_t iccid[20];
	
	uint8_t rssl;
	uint8_t ber;
	
	
}a7600c1_para;


extern a7600c1_para a7600c1_data;
extern a7600c1_rx_data a7600c1_rxdata;
uint8_t ascii_to_hex(uint8_t ascii);

/*status_control*/
void a7600c1_init(void);
	
uint8_t a7600c1_set_phone_functionality(a7600c1_para *handle,uint8_t level);
uint8_t a7600c1_get_phone_functionality(a7600c1_para *handle);
uint8_t a7600c1_inquire_csq(a7600c1_para *handle);
uint8_t a7600c1_set_csq_auto_report(a7600c1_para *handle,uint8_t set,uint8_t mode);
uint8_t a7600c1_setrssi_delta_change_threshold(a7600c1_para *handle,uint8_t threshold);
uint8_t a7600c1_power_down_the_module(a7600c1_para *handle);
uint8_t a7600c1_reset_the_module(a7600c1_para *handle);
uint8_t a7600c1_set_real_time_module(a7600c1_para *handle);
uint8_t a7600c1_read_real_time_module(a7600c1_para *handle);
uint8_t a7600c1_change_module_equiment_error_report_format(a7600c1_para *handle,uint8_t error_level);

#endif

