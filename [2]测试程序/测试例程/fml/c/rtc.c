/*!
*			\file rtc.c
*			\brief rtc的驱动函数
*/

#include "rtc.h"

#define RTC_CLK_H 	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13, GPIO_PIN_SET);	
#define RTC_CLK_L		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13, GPIO_PIN_RESET);

#define RTC_RST_H		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14, GPIO_PIN_SET);
#define RTC_RST_L		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14, GPIO_PIN_RESET);

#define RTC_DATA_H	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12, GPIO_PIN_SET);
#define RTC_DATA_L	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12, GPIO_PIN_RESET);

/*!
*		\brief rtc init
*/
void rtc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOB_CLK_ENABLE();	
	
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

}

void rtc_data_out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOB_CLK_ENABLE();	
	
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void rtc_data_in(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOB_CLK_ENABLE();	
	
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}



void DS1302_WriteByte(uint8_t data)
{
	uint8_t i=0;
	
	rtc_data_out();//DS1302_DAT_setOUT()
	for(i=0;i<8;i++)
	{
		
		if(data&0x01)
		{
			RTC_DATA_H;//数据线放上数据，先发低位
		}
		else
		{
			RTC_DATA_L;
		}
		RTC_CLK_L;//时钟线拉低
		HAL_Delay(1);		
		RTC_CLK_H;//时钟上升沿写入数据
		HAL_Delay(1);
		
		data>>=1;
	}
	RTC_DATA_L;
}

uint8_t DS1302_ReadByte(void)
{
	uint8_t bit=0;
	uint8_t input_value=0;
	uint8_t i=0;	
	rtc_data_in();//DS1302_DAT_setIN();//配置IO为输入
	HAL_Delay(1);
        
	for(i=0;i<8;i++)
	{
		RTC_CLK_H;
		HAL_Delay(1);
		RTC_CLK_L;
		HAL_Delay(1);//时钟线拉低，时钟下降沿读数据。读之前为DS1302_WriteByte，最后为DS1302_CLK_H
		bit=(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12));
		input_value |= (bit << i);			
	}
        rtc_data_out();//配置IO为输出,恢复正常状态
        HAL_Delay(1);
	return input_value;
}		


void DS1302_WriteSingleReg(uint8_t reg,uint8_t data)
{
	RTC_RST_L;//禁止数据传输 ！！！这条很重要
	RTC_CLK_L;//确保写数据前SCLK为低电平
	HAL_Delay(1);
	
	RTC_RST_H;	//RET=1;//启动DS1302总线
	HAL_Delay(1);
	
	DS1302_WriteByte(reg);
	DS1302_WriteByte(data);
	
	RTC_RST_L;// CE=0;
	RTC_CLK_L;//CLK=0;
	
}
uint8_t DS1302_ReadSingleReg(uint8_t reg)
{
	uint8_t data=0;
	RTC_RST_L;//禁止数据传输 ！！！这条很重要
	RTC_CLK_L;//确保写数据前SCLK为低电平
	HAL_Delay(1);
	RTC_RST_H;//RET=1;//启动DS1302总线,当CE被从0置为1时，时钟线必须为逻辑0。
	HAL_Delay(1);
	
	DS1302_WriteByte(reg);
	data=DS1302_ReadByte();
        
	RTC_RST_L;
	HAL_Delay(1);
	RTC_CLK_L;

	return data; // BCD码
}

/*BCD码输入*/
void DS1302_set_time(uint8_t year,uint8_t week,uint8_t mouth,uint8_t day,uint8_t hour,uint8_t min,uint8_t sec)
{
	DS1302_WriteSingleReg(0x80,sec);
	DS1302_WriteSingleReg(0x82,min);
	DS1302_WriteSingleReg(0x84,hour);
	DS1302_WriteSingleReg(0x86,day);
	DS1302_WriteSingleReg(0x88,mouth);
	DS1302_WriteSingleReg(0x8a,week);
	DS1302_WriteSingleReg(0x8c,year);
}

void DS1302_get_time(uint8_t *year,uint8_t *week,uint8_t *mouth,uint8_t *day,uint8_t *hour,uint8_t *min,uint8_t *sec)
{
		*sec = DS1302_ReadSingleReg(0x81);
		*min = DS1302_ReadSingleReg(0x83);
		*hour = DS1302_ReadSingleReg(0x85);
		*day = DS1302_ReadSingleReg(0x87);
		*mouth = DS1302_ReadSingleReg(0x89);
		*week = DS1302_ReadSingleReg(0x8b);
		*year = DS1302_ReadSingleReg(0x8d);
	
	
}







