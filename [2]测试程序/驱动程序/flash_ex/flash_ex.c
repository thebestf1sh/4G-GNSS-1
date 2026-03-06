/*!
*			\file flash_ex.c
*			\brief flash_ex的驱动函数,W25Q64JVSSIQ
*/

#include "flash_ex.h"

#define FLASH_CS_LOW HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
#define FLASH_CS_HIGH HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);


/*!
*		\brief flash_ex init
*/	
void flash_ex_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOB_CLK_ENABLE();	
		
	/*Configure GPIO pins : PB15*/
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
	MX_SPI1_Init();
	
}

uint8_t SPI1_ReadWriteByte(uint8_t TxData)//发送一个字节，并从寄存器返回一个字节
{
	uint8_t Rxdata;
	HAL_SPI_TransmitReceive(&hspi1, &TxData, &Rxdata, 1, 1000);       
 	return Rxdata;          		    
}


//uint8_t SPI1_WriteByte(uint8_t *ptr,uint16_t size)//发送一个字节，并从寄存器返回一个字节
//{
//	uint8_t Rxdata;
//	HAL_SPI_Transmit(&hspi1, ptr, size, 1000);       
// 	return Rxdata;          		    
//}

//uint8_t SPI1_ReadByte(uint8_t *ptr,uint16_t size)//发送一个字节，并从寄存器返回一个字节
//{
//	uint8_t Rxdata;
//	HAL_SPI_Receive(&hspi1, ptr, size, 1000);       
// 	return Rxdata;          		    
//}

uint32_t flash_read_id(void)
{
    uint8_t id1, id2, id3;
    uint32_t uiID;
    
    FLASH_CS_LOW;
    
	 /* send read id command*/
		SPI1_ReadWriteByte(FLASH_JEDEC_ID);
		id1 = SPI1_ReadWriteByte(0xff);
    id2 = SPI1_ReadWriteByte(0xff);
    id3 = SPI1_ReadWriteByte(0xff);
    FLASH_CS_HIGH;
    
    uiID = (id1 << 16) | (id2 << 8) | id3;
    
    return uiID;
}


/*!
*      \brief    receive data 
*/
static uint8_t flash_read_byte(void)
{
    return SPI1_ReadWriteByte(0xA5);
}

/*!
*      \brief    transmit data 
*/
static void flash_write_byte(uint8_t data)
{
    SPI1_ReadWriteByte(data);
}


/*!
*      \brief    write enable  
*/
static void flash_write_enable(void)
{
		FLASH_CS_LOW;
		/*Send write enable command*/
    flash_write_byte(FLASH_WRITE_ENABLE);
    FLASH_CS_HIGH;
}

/*!
*      \brief    write disable  
*/
void flash_write_disable(void)
{
    FLASH_CS_LOW;
		/*Send write disable command*/
    flash_write_byte(FLASH_WRITE_DISABLE);
    FLASH_CS_HIGH;
}


/*!
*			\brief  wait write end
*/
static uint8_t flash_wait_write_end(void)
{
    uint8_t status = 0;
    uint32_t timeout = 0;
    
    FLASH_CS_LOW;
	 /*send read status register command*/
    flash_write_byte(0x05);
    do
    {
        status = flash_read_byte();
        timeout++;
        if(timeout > 0xffffffff)
            return 0;    
    }while(status & 0x01);
    FLASH_CS_HIGH;
    
    return 1;
}

/*!
*			\brief   write status reg
*			\input 	 command = FLASH_WRITE_STATUS_REGISTER_1(01)
*												 FLASH_WRITE_STATUS_REGISTER_2(31)
*												 FLASH_WRITE_STATUS_REGISTER_3(35)
*/
void flash_write_status_register(uint8_t command, uint8_t status)
{
    FLASH_CS_LOW;
    flash_write_byte(command&0xFF);
    flash_write_byte(status&0xFF);
    FLASH_CS_HIGH;
}



uint8_t flash_write_page(const uint8_t* pdata, uint32_t addr, uint16_t size)
{
    uint8_t ret = 0;
        
		/*enable write*/
    flash_write_enable();
    
    FLASH_CS_LOW;
    
		/*send write command */
    flash_write_byte(0x02);
		/*send address*/
	
	//	W25Q32_Write_Byte((addr & 0xFF000000) >> 24);
    flash_write_byte((addr & 0xFF0000) >> 16);
    flash_write_byte((addr & 0xFF00) >> 8);
    flash_write_byte(addr & 0xFF);
    
    while(size--)
    {
        flash_write_byte(*pdata);
        pdata++;
    }
    
    FLASH_CS_HIGH;    
    
    return ret;
}

uint8_t flash_write_sector(const uint8_t* pdata, uint32_t addr, uint16_t size)
{
    uint8_t ret = 0;
    uint16_t page_offset = 0;
    uint16_t page_remain = 0;
		
		/*calculates offset*/
    page_offset = addr%256;
		/*calculates remain*/
    page_remain = 256 - page_offset;
    
    if(size <= page_remain){
        page_remain = size;
    }
    
    while(1)
    {
        ret = flash_write_page(pdata, addr, page_remain);
        if(page_remain != size){
            addr += page_remain;
            pdata += page_remain;
            size -= page_remain;
            if(size > 256){
                page_remain = 256;
            }
            else{
                page_remain = size;
            }
        }else{
            break;
        }
    }
    return ret;
}


uint8_t flash_sectir_erase(uint32_t sector_addr)
{
    uint8_t ret = 0;
        
		/*enable write*/
    flash_write_enable();
    
    ret = flash_wait_write_end();
    if(ret == 0)
        return ret;
    
    FLASH_CS_LOW;
    /*send read command */
    flash_write_byte(FLASH_SECTOR_ERASE_4);
		/*send address */
    flash_write_byte((sector_addr & 0xFF0000) >> 16);
    flash_write_byte((sector_addr & 0xFF00) >> 8);
    flash_write_byte(sector_addr & 0xFF);
    
    FLASH_CS_HIGH;
    /*waiting for write finish */
    ret = flash_wait_write_end();
    
    return ret;
}

uint8_t flash_chip_erase(void)
{
    uint8_t ret = 0;
    
    /* enable write */
    flash_write_enable();

		FLASH_CS_LOW;
    /* send erase command */
    flash_write_byte(FLASH_CHIP_ERASE_1);

    FLASH_CS_HIGH;    
    
    /* waiting for erase finish  */
    ret = flash_wait_write_end();
    
    return ret;
}

void flash_read_data(uint8_t* pdata, uint32_t address, uint16_t size)
{
    uint32_t i;
    
    FLASH_CS_LOW;
    
    /* send read command */
    flash_write_byte(FLASH_READ_DATA);
    /* send 32 bit address */
    flash_write_byte(address >> 16);
    flash_write_byte(address >> 8);
    flash_write_byte(address);
    /* receive data */
    for(i = 0; i < size; i++)
    {
        pdata[i] = flash_read_byte();
    }

    FLASH_CS_HIGH;
}

#ifdef SECTOR_WRITE
uint8_t W25Q32_Write_Data(const uint8_t* pdata, uint32_t address, uint16_t size)
{
    uint8_t ret = 0;    
    uint32_t sector_pos = 0;
    uint16_t sector_offset = 0;            
    uint16_t sector_remain = 0;
    uint32_t i;
    
		/*sector address*/
    sector_pos = address/4096;
		/*calculates sector offset address*/
    sector_offset = address%4096;
	  /*calculates remain*/ 
    sector_remain = 4096 - sector_offset;
    
    if(size <= sector_remain){
        sector_remain = size;
    }
    while(1)
    {
        /* read sector data */
        W25Q32_Read_Data(W25Q32_buffer, sector_pos*4096, 4096);
        for(i = 0; i < sector_remain; i++){
            if(W25Q32_buffer[sector_offset + i] != 0xFF)
                break;
        }
        if(i < sector_remain){
            /* erash sector  */
            W25Q32_Sector_Erase(sector_pos*4096);
            for(i = 0; i < sector_remain; i++){
                W25Q32_buffer[sector_offset + i] = pdata[i];
            }
            ret = W25Q32_Write_Sector(W25Q32_buffer, sector_pos*4096, 4096);
        }else{
            ret = W25Q32_Write_Sector(pdata, address, sector_remain);
        }
        
        if(size == sector_remain){
            break;
        }else{
            sector_pos++;
            sector_offset = 0;
            
            pdata += sector_remain;
            address += sector_remain;
            size -= sector_remain;
            if(size > 4096){
                sector_remain = 4096;
            }else{
                sector_remain = size;
            }
        }
    }
    
    return ret;
}
#endif








