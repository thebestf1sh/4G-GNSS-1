/*!	
*			\file flash_ex.h
*			\brief flash_ex驱动函数的头文件
*
*/

#ifndef _FLASH_EX_H_
#define _FLASH_EX_H_

#include "main.h"
#define FLASH_WRITE_ENABLE 									0x06
#define FLASH_WRITE_DISABLE 								0x04

#define FLASH_READ_STATUS_REGISTER_1				0x05   	//s7-s0
#define FLASH_WRITE_STATUS_REGISTER_1				0x01

#define FLASH_READ_STATUS_REGISTER_2				0x35		//s15-s8
#define FLASH_WRITE_STATUS_REGISTER_2				0x31

#define FLASH_READ_STATUS_REGISTER_3				0x15		//s23-s16
#define FLASH_WRITE_STATUS_REGISTER_3				0x11

#define FLASH_SECTOR_ERASE_4								0x20
#define FLASH_BLOCK_ERASE_32								0x52
#define FLASH_BLOCK_ERASE_64								0xd8
#define FLASH_CHIP_ERASE_1									0xC7
#define FLASH_CHIP_ERASE_2									0x60

#define FLASH_ERASE_PROGRAM_SUSPEND					0x75
#define FLASH_ERASE_PROGRAM_RESUME					0x7A

#define FLASH_POWER_DOWN										0xB9
#define FLASH_POWER_ON_OR_ID								0xab

#define FLASH_MANUFACTURER_ID								0x90
#define FLASH_JEDEC_ID											0x9f

#define FLASH_ENABLE_RESET									0x66
#define FLASH_RESET_DEVICE									0x99

#define FLASH_READ_UNIQUE_ID								0x4b

#define FLASH_PAGE_PROGRAM									0x02
#define FLASH_READ_DATA											0x03		
#define FLASH_FAST_READ_DATA								0x0B


void flash_ex_init(void);
uint8_t flash_write_page(const uint8_t* pdata, uint32_t addr, uint16_t size);
uint32_t flash_read_id(void);
uint8_t flash_sectir_erase(uint32_t sector_addr);
uint8_t flash_chip_erase(void);
void flash_read_data(uint8_t* pdata, uint32_t address, uint16_t size);


#endif
