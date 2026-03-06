/*!	
*			\file aht20.h
*			\brief 温湿度传感器驱动头文件
*
*/

#ifndef _AHT20_H_
#define _AHT20_H_

#include "main.h"

#define AHT20_ADDRESS 0X38
#define AHT20_READ 		0X71
#define AHT20_WRITE 	0X70

#define AHT20_AC_CMD 	0XAC
#define AHT20_AC_DATA_1	0X33
#define AHT20_AC_DATA_2 0X00


typedef struct
{
	uint32_t temp;
	uint32_t humi;
  uint8_t data[8];
	float temp_data;
	float	humi_data;
}aht20_param;

extern aht20_param aht20_data;

void aht20_init(void);
uint8_t aht20_read_state(void);
void aht20_send_ac(void);
void aht20_read_data(aht20_param *handle);
void aht20_read_data_crc(aht20_param *handle);
void aht20_start_init(void);

#endif

