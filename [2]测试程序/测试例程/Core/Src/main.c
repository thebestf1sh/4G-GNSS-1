/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


uint8_t str[20] = {' ','4','T','-','4','G','T','E','S','T',' ',' ','V','E','R','1','.','0','2',' '};
uint8_t read[200];
char buff[200];
uint8_t state,ntp_state;

uint16_t adada[10]={0x1234,0x2345,0x3456,0x4567,0x5678,0x6789};
//gnss
uint8_t time[20]=" TIME = ";
uint8_t latitude[20]=" lati = ";
uint8_t N_S[20]=" ns   = ";
uint8_t longitude[20]=" long = ";
uint8_t E_W[20]=" ew   = ";
uint8_t spd[20]=" spd  = ";


extern bmp_param bmp_data;
extern uint8_t key_1_flag;
extern uint8_t key_2_flag;
extern uint8_t key_3_flag;
uint8_t bmp388_flag;
uint16_t data,i;
uint32_t data_32;
float fdata;




void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{	
  HAL_Init();

  SystemClock_Config();
	a7600c1_init();
	/*SPI接口的LCD屏的初始化*/
//page 1 
	spi_lcd_init();
	spi_lcd_clear(RED);
	spi_lcd_clear(WHITE);
	/*按键初始化*/
	key_init();

	
/*********************************************flash 测试************************************************************/	
	/*flash 初始化,擦除与写入*/	
	flash_ex_init();
//	flash_chip_erase();
	flash_write_page(str,0x000200,20);
	HAL_Delay(1000);
	flash_read_data(read,0x000200,20);
	printf(" FLASH TEST ");
	
	
	sprintf(buff," FLASH TEST ");
	spi_lcd_display_string_line(Line1, Black,White,(uint8_t *)buff);	
	spi_lcd_display_string_line(Line2, Black,White,(uint8_t *)read);	
/************************************************LED 测试***********************************************************/
	/*LED灯初始化*/
	led_init();
	set_led_state(LD1_PIN,LED_ON);
	set_led_state(LD2_PIN,LED_OFF);
	set_led_state(LD3_PIN,LED_OFF);
	set_led_state(LD4_PIN,LED_OFF);
	HAL_Delay(300);
	set_led_state(LD1_PIN,LED_OFF);
	set_led_state(LD2_PIN,LED_ON);
	HAL_Delay(300);
	set_led_state(LD2_PIN,LED_OFF);
	set_led_state(LD3_PIN,LED_ON);
	HAL_Delay(300);
	set_led_state(LD3_PIN,LED_OFF);
	set_led_state(LD4_PIN,LED_ON);
	HAL_Delay(300);
	set_led_state(LD1_PIN,LED_ON);
	set_led_state(LD4_PIN,LED_OFF);
	HAL_Delay(300);
	set_led_state(LD1_PIN,LED_OFF);
	set_led_state(LD2_PIN,LED_ON);
	HAL_Delay(300);
	set_led_state(LD2_PIN,LED_OFF);
	set_led_state(LD3_PIN,LED_ON);
	HAL_Delay(300);
	set_led_state(LD3_PIN,LED_OFF);
	set_led_state(LD4_PIN,LED_ON);
	HAL_Delay(300);
	set_led_state(LD1_PIN,LED_ON);
	set_led_state(LD2_PIN,LED_ON);
	set_led_state(LD3_PIN,LED_ON);
	set_led_state(LD4_PIN,LED_ON);	

/***********************************************传感器测试************************************************************/

	/*压力传感器初始化*/
	bmp388_init();
	/*温湿度传感器初始化*/
//	aht20_init();
	sprintf(buff," BMP388  TEST ");
	spi_lcd_display_string_line(Line4, Black,White,(uint8_t *)buff);			
	sprintf(buff," AHT20   TEST ");
	spi_lcd_display_string_line(Line7, Black,White,(uint8_t *)buff);		
	while(key_1_flag == 0)
	{
		HAL_Delay(500);
		bmp388_read_compensation_data(&bmp388_compensation);
		
		data_32 = bmp388_read_temper();
		fdata = compensate_temperature(data_32);
		sprintf(buff," TEMP is %2.2f" , fdata);
		spi_lcd_display_string_line(Line5, BLUE,White,(uint8_t *)buff);
		data_32 = bmp388_read_press();
		fdata = compensate_pressure(data_32);
		sprintf(buff," PRES is %6.2f" , fdata);
		spi_lcd_display_string_line(Line6, BLUE,White,(uint8_t *)buff);	

//		aht20_read_data(&aht20_data);	
		sprintf(buff," TEMP is %2.2f" , aht20_data.temp_data);
		spi_lcd_display_string_line(Line8, BLUE,White,(uint8_t *)buff);		
		sprintf(buff," HUMI is %2.2f" , aht20_data.humi_data);
		spi_lcd_display_string_line(Line9, BLUE,White,(uint8_t *)buff);		
	}	
//page 2
	spi_lcd_clear(WHITE);
	/*加速度传感器初始化*/
	LSM6DS3TR_init();
	/*光照强度传感器初始化*/
	bh1750_Init();
	while(key_2_flag == 0)
	{
		sprintf(buff," LSM6DS3TR TEST");
		spi_lcd_display_string_line(Line0, Black,White,(uint8_t *)buff);	
		str[0] = LSM6DS3TR_read_data(OUTX_L_G);
		str[1] = LSM6DS3TR_read_data(OUTX_H_G);
		data  = str[1]*256+str[0];		
		sprintf(buff," Angular X  %d",data);
		spi_lcd_display_string_line(Line1,MEGENTA,White, (uint8_t *)buff);
		str[2] = LSM6DS3TR_read_data(OUTY_L_G);
		str[3] = LSM6DS3TR_read_data(OUTY_H_G);
		data  = str[3]*256+str[2];		
		sprintf(buff," Angular Y  %d",data);
		spi_lcd_display_string_line(Line2, MEGENTA,White,(uint8_t *)buff);
		str[4] = LSM6DS3TR_read_data(OUTZ_L_G);
		str[5] = LSM6DS3TR_read_data(OUTZ_H_G);
		data  = str[5]*256+str[4];	
		sprintf(buff," Angular Z  %d",data);
		spi_lcd_display_string_line(Line3, MEGENTA,White,(uint8_t *)buff);

		str[6] = LSM6DS3TR_read_data(OUTX_L_XL);
		str[7] = LSM6DS3TR_read_data(OUTX_H_XL);
		data  = str[7]*256+ str[6];		
		sprintf(buff," Linear X   %d",data);
		spi_lcd_display_string_line(Line4, MEGENTA,White,(uint8_t *)buff);
		str[8] = LSM6DS3TR_read_data(OUTY_L_XL);
		str[9] = LSM6DS3TR_read_data(OUTY_H_XL);
		data  = str[9]*256+str[8];		
		sprintf(buff," Linear Y   %d",data);
		spi_lcd_display_string_line(Line5, MEGENTA,White,(uint8_t *)buff);
		str[10] = LSM6DS3TR_read_data(OUTZ_L_XL);
		str[11] = LSM6DS3TR_read_data(OUTZ_H_XL);	
		data  = str[11]*256+str[10];	
		sprintf(buff," Linear Z   %d",data);
		spi_lcd_display_string_line(Line6, MEGENTA,White,(uint8_t *)buff);

		str[12] = LSM6DS3TR_read_data(OUT_TEMP_H);
		str[13] = LSM6DS3TR_read_data(OUT_TEMP_L);
		data  = str[12]*256+str[13];
		fdata = data/256.0 + 25;
		sprintf(buff," TEMP   is  %2.2f",fdata);
		spi_lcd_display_string_line(Line7, MEGENTA,White,(uint8_t *)buff);	
		
		sprintf(buff," BH1750 TEST");
		spi_lcd_display_string_line(Line8, Black,White,(uint8_t *)buff);
		fdata = bh1750_Read_Measure();
		sprintf(buff," AL  %2.2f LX" , fdata);
		spi_lcd_display_string_line(Line9, RED,White,(uint8_t *)buff);			
		
	}
//page 3
	spi_lcd_clear(WHITE);
	/*4G模组串口初始化*/
	MX_USART3_UART_Init();
	sprintf(buff," 4G A7600C1 TEST");
	spi_lcd_display_string_line(Line0, Black,White,(uint8_t *)buff);
	
	printf("AT+CPIN?\r\n");
	HAL_Delay(200);
	if(usart3_para.rx_length != 0)
	{
		for(i=0;i<usart3_para.rx_length;i++)
		{
			read[i] = usart3_para.rx_buffer[i];
			if((read[i] == 0x0a)||(read[i] == 0x0d))
			{
				read[i] = 0;
			}
			if(read[i] == '+')
			{
				read[i] = ' ';
			}
		}	
		sprintf(buff," ENTER PIN  ");
		spi_lcd_display_string_line(Line1,BLACK,White,(uint8_t *)buff);
		spi_lcd_display_string_line(Line2,RED,White,read+11);		
		usart3_para.rx_length = 0;
	}
		
	while(key_3_flag == 0)
	{
		
		/*查询CSQ*/
		printf("AT+CSQ\r\n");
		HAL_Delay(10);
		if(usart3_para.rx_length != 0)
		{
			for(i=0;i<usart3_para.rx_length;i++)
			{
				read[i] = usart3_para.rx_buffer[i];
				if((read[i] == 0x0a)||(read[i] == 0x0d))
				{
					read[i] = 0;
				}
				if(read[i] == '+')
				{
					read[i] = ' ';
				}
			}	
			for(i=20;i<30;i++)
			{
				read[i] = ' ';
				
			}
			sprintf(buff," SIGNAL QUALITY ");
			spi_lcd_display_string_line(Line3,BLACK,White,(uint8_t *)buff);
			spi_lcd_display_string_line(Line4,RED,White,read+9);		
			usart3_para.rx_length = 0;
		}
		
		if(ntp_state == 0)
		{
			printf("AT+CNTP=\"ntp.tencent.com\"\r\n");
			HAL_Delay(50);
			printf("AT+CNTP\r\n");
			HAL_Delay(500);
			if(usart3_para.rx_length != 0)
			{
				for(i=0;i<usart3_para.rx_length;i++)
				{
					read[i] = usart3_para.rx_buffer[i];
					if((read[i] == 0x0a)||(read[i] == 0x0d))
					{
						read[i] = 0;
					}
					if(read[i] == '+')
					{
						read[i] = ' ';
					}
				}	
				usart3_para.rx_length = 0;
				if(read[9]=='0')
				{
					sprintf(buff," CONNECT NTP OK ");
					spi_lcd_display_string_line(Line5,BLACK,White,(uint8_t *)buff);
					spi_lcd_display_string_line(Line6,RED,White,read+2);	
					ntp_state = 1;
				}
				usart3_para.rx_length = 0;
			}			
		}
		
		printf("AT+CCLK?\r\n");
		HAL_Delay(20);
			if(usart3_para.rx_length != 0)
			{
				for(i=0;i<usart3_para.rx_length;i++)
				{
					read[i] = usart3_para.rx_buffer[i];
					if((read[i] == 0x0a)||(read[i] == 0x0d))
					{
						read[i] = '-';
					}
					if((read[i] == '+')||(read[i] == '\"'))
					{
						read[i] = ' ';
					}
				}
				read[36]=0;
				sprintf(buff," REAL-TIME ");
				spi_lcd_display_string_line(Line7,BLACK,White,(uint8_t *)buff);
				spi_lcd_display_string_line(Line8,RED,White,read+18);		
				usart3_para.rx_length = 0;
			}
	}
//page 4
	spi_lcd_clear(WHITE);
	
	/*调试串口初始化*/
//	MX_USART1_UART_Init();
  /*GNSS串口初始化*/
	MX_USART2_UART_Init();	
  /*RS485串口初始化*/
//	MX_UART4_UART_Init();
	/*RTC实时时钟初始化*/
	rtc_pcf8563_init();
	sprintf(buff," GNSS TEST ");
	spi_lcd_display_string_line(Line0,BLACK,White,(uint8_t *)buff);
	while(1)
	{
		if(usart2_para.rx_length != 0)
		{
			for(i=0;i<1024;i++)
			{
				if(usart2_para.rx_buffer[i]==0x0A ||usart2_para.rx_buffer[i] == 0x0d)
				{
					usart2_para.rx_buffer[i] = 0;
				}
			}
			for(i=0;i<1024;i++)
			{
				if((usart2_para.rx_buffer[i]=='$')&&(usart2_para.rx_buffer[i+1]=='G')&&(usart2_para.rx_buffer[i+2]=='P')&&(usart2_para.rx_buffer[i+3]=='G')&&(usart2_para.rx_buffer[i+4]=='S')&&(usart2_para.rx_buffer[i+5]=='V'))
				{
					spi_lcd_display_string_line(Line1, Black,White,usart2_para.rx_buffer+i);	
				}
				if((usart2_para.rx_buffer[i]=='$')&&(usart2_para.rx_buffer[i+1]=='B')&&(usart2_para.rx_buffer[i+2]=='D')&&(usart2_para.rx_buffer[i+3]=='G')&&(usart2_para.rx_buffer[i+4]=='S')&&(usart2_para.rx_buffer[i+5]=='V'))
				{
					spi_lcd_display_string_line(Line2, Black,White,usart2_para.rx_buffer+i);	
				}
				if((usart2_para.rx_buffer[i]=='$')&&(usart2_para.rx_buffer[i+1]=='G')&&(usart2_para.rx_buffer[i+2]=='N')&&(usart2_para.rx_buffer[i+3]=='R')&&(usart2_para.rx_buffer[i+4]=='M')&&(usart2_para.rx_buffer[i+5]=='C'))
				{
	
					memcpy(time+7,usart2_para.rx_buffer+i+7,10);//时间
					
					sprintf(buff," TIME = %d:%d:%d       ",(time[7]-0x30)*10+time[8]-0x30+8,(time[9]-0x30)*10+time[10]-0x30,(time[11]-0x30)*10+time[12]-0x30);
					spi_lcd_display_string_line(Line4,BLACK,White,(uint8_t *)buff);
					memcpy(latitude+8,usart2_para.rx_buffer+i+20,9);//纬度
					memcpy(N_S+8,usart2_para.rx_buffer+i+31,1);//纬度方向
					memcpy(longitude+8,usart2_para.rx_buffer+i+33,10);//经度
					memcpy(E_W+8,usart2_para.rx_buffer+i+45,1);//经度方向
					memcpy(spd+8,usart2_para.rx_buffer+i+47,4);//速度
					spi_lcd_display_string_line(Line5,Black,White,latitude);	
					spi_lcd_display_string_line(Line6,Black,White,N_S);	
					spi_lcd_display_string_line(Line7,Black,White,longitude);	
					spi_lcd_display_string_line(Line8,Black,White,E_W);	
					spi_lcd_display_string_line(Line9,Black,White,spd);		
				}
				
			}

			usart2_para.rx_length = 0;
		}	
	}


	

	

	/*4G模块初始化*/
	
	
/**************************************************设置RTC时钟*********************************************/	
//	rtc_data.year = 0x22;
//	rtc_data.mouth = 0x07;
//	rtc_data.week = 0x05;
//	rtc_data.day = 0x29;
//	rtc_data.hour = 0x15;
//	rtc_data.minute = 0x56;
//	rtc_data.sec = 0x00;
//	
//	rtc_pcf8563_set(&rtc_data);
/**********************************************************************************************************/	

	




	while (1)
	{
					
/****************************************4G 模块串口透传AT指令测试*****************************************/
//		if(usart1_para.rx_length!=0)
//		{
//			HAL_UART_Transmit(&huart3 ,usart1_para.rx_buffer,usart1_para.rx_length, 100);
//			usart1_para.rx_length = 0;
//		}

//		if(usart3_para.rx_length!=0)
//		{
//			HAL_UART_Transmit(&huart1 ,usart3_para.rx_buffer,usart3_para.rx_length, 100);
//			usart3_para.rx_length = 0;
//		}
/**********************************************************************************************************/
/**********************************************光照传感器测试**********************************************/		
//		fdata = bh1750_Read_Measure();
//		sprintf(buff,"   %2.2f" , fdata);
//		spi_lcd_display_string_line(Line1, Black,White,(uint8_t *)buff);		
/**********************************************************************************************************/		
/*********************************************flash 读写测试***********************************************/		
//		flash_read_data(read,0x000100,20);	
//		HAL_UART_Transmit(&huart1 ,read , 20, 100);
//		HAL_Delay(1000);
/**********************************************************************************************************/
/********************************************RTC实时时钟测试***********************************************/		
//		rtc_pcf8563_read(&rtc_data);
//		
//		str[0] = rtc_data.hour>>4;
//		str[1] = rtc_data.hour&0x0f;
//		str[2] = rtc_data.minute>>4;
//		str[3] = rtc_data.minute&0x0f;
//		str[4] = rtc_data.sec>>4;
//		str[5] = rtc_data.sec&0x0f;
//		sprintf(buff,"   %d%d:%d%d:%d%d" , str[0],str[1],str[2],str[3],str[4],str[5]);
//		spi_lcd_display_string_line(Line1, Black,White,(uint8_t *)buff);
//		str[6] = rtc_data.year>>4;
//		str[7] = rtc_data.year&0x0f;
//		str[8] = rtc_data.mouth>>4;
//		str[9] = rtc_data.mouth&0x0f;
//		str[10] = rtc_data.day>>4;
//		str[11] = rtc_data.day&0x0f;
//		str[12] = rtc_data.week;
//		sprintf(buff,"   %d%d/%d%d/%d%d  %d" , str[6],str[7],str[8],str[9],str[10],str[11],str[12]);
//		spi_lcd_display_string_line(Line2, Black,White,(uint8_t *)buff);
/**********************************************************************************************************/
		
/*******************************************AHT20 温湿度传感器读取测试*************************************/
//		aht20_read_data_crc(&aht20_data);	
//		printf("humi is %6.2f%%,temp us %6.2f \r\n",aht20_data.humi_data,aht20_data.temp_data);
//		HAL_Delay(500);
/**********************************************************************************************************/	
/*********************************************BMP388温度大气压读取测试*************************************/			
//		bmp388_read_compensation_data(&bmp388_compensation);
//		
//		data_32 = bmp388_read_temper();
//		fdata = compensate_temperature(data_32);
//		sprintf(buff,"tem_388 is %2.2f" , fdata);
//		spi_lcd_display_string_line(Line2, Black,White,(uint8_t *)buff);
//		data_32 = bmp388_read_press();
//		fdata = compensate_pressure(data_32);
//		sprintf(buff,"pre is %6.2f" , fdata);
//		spi_lcd_display_string_line(Line4, Black,White,(uint8_t *)buff);
//		
//		HAL_Delay(200);				
/**********************************************************************************************************/		
/*********************************************LSM 加速度传感器*********************************************/		
//		备注：我只是测试了焊接是否OK，能否读到数据。没有具体实现很具体的功能			
//		data  = str[1]<<8 | str[0];		
//		sprintf(buff,"gx is %d          ",data);
//		spi_lcd_display_string_line(Line1,Black,White, (uint8_t *)buff);
//		str[2] = LSM6DS3TR_read_data(OUTY_L_G);
//		str[3] = LSM6DS3TR_read_data(OUTY_H_G);
//		data  = str[3]<<8 | str[2];		
//		sprintf(buff,"gy is %d           ",data);
//		spi_lcd_display_string_line(Line2, Black,White,(uint8_t *)buff);
//		str[4] = LSM6DS3TR_read_data(OUTZ_L_G);
//		str[5] = LSM6DS3TR_read_data(OUTZ_H_G);
//		data  = str[5]<<8 | str[4];	
//		sprintf(buff,"gz is %d           ",data);
//		spi_lcd_display_string_line(Line3, Black,White,(uint8_t *)buff);

//		str[6] = LSM6DS3TR_read_data(OUTX_L_XL);
//		str[7] = LSM6DS3TR_read_data(OUTX_H_XL);
//		data  = str[7]<<8 | str[6];		
//		sprintf(buff,"ax is %d           ",data);
//		spi_lcd_display_string_line(Line5, Black,White,(uint8_t *)buff);
//		str[8] = LSM6DS3TR_read_data(OUTY_L_XL);
//		str[9] = LSM6DS3TR_read_data(OUTY_H_XL);
//		data  = str[9]<<8 | str[8];		
//		sprintf(buff,"ay is %d           ",data);
//		spi_lcd_display_string_line(Line6, Black,White,(uint8_t *)buff);
//		str[10] = LSM6DS3TR_read_data(OUTZ_L_XL);
//		str[11] = LSM6DS3TR_read_data(OUTZ_H_XL);	
//		data  = str[11]<<8 | str[10];	
//		sprintf(buff,"az is %d           ",data);
//		spi_lcd_display_string_line(Line7, Black,White,(uint8_t *)buff);

//		str[12] = LSM6DS3TR_read_data(OUT_TEMP_H);
//		str[13] = LSM6DS3TR_read_data(OUT_TEMP_L);
//		data  = str[12]<<8 | str[13];
//		fdata = data/256.0 + 25;
//		sprintf(buff,"tem1 is %2.2f",fdata);
//		spi_lcd_display_string_line(Line9, Black,White,(uint8_t *)buff);
/**********************************************************************************************************/				
/*********************************************SPI LCD测试**************************************************/		
//		spi_lcd_clear(WHITE);
//		HAL_Delay(1000);
//		spi_lcd_clear(RED);
//		HAL_Delay(1000);
//		spi_lcd_clear(GREEN);
//		HAL_Delay(1000);
//		spi_lcd_clear(BLACK);
//		HAL_Delay(1000);
//		spi_lcd_clear(GREY);
//		HAL_Delay(1000);
//		spi_lcd_clear(BLUE);
//		HAL_Delay(1000);
//		spi_lcd_clear(BLUE2);
//		HAL_Delay(1000);
//		spi_lcd_clear(MEGENTA);
//		HAL_Delay(1000);
//		spi_lcd_clear(CYAN);
//		HAL_Delay(1000);
//		spi_lcd_clear(YELLOW);
//		HAL_Delay(1000);		
/**********************************************************************************************************/			
/*********************************************串口回传测试*************************************************/	
//		if(usart1_para.rx_length!=0)
//		{
//			HAL_UART_Transmit(&huart1 ,usart1_para.rx_buffer,usart1_para.rx_length, 100);
//			usart1_para.rx_length = 0;
//		}

//		if(usart3_para.rx_length!=0)
//		{
//			HAL_UART_Transmit(&huart3 ,usart3_para.rx_buffer,usart3_para.rx_length, 100);
//			usart3_para.rx_length = 0;
//		}

//		if(usart2_para.rx_length!=0)
//		{
//			HAL_UART_Transmit(&huart2 ,usart2_para.rx_buffer,usart2_para.rx_length, 100);
//			usart2_para.rx_length = 0;
//		}

//		if(usart4_para.rx_length!=0)
//		{
//			HAL_UART_Transmit(&huart4 ,usart4_para.rx_buffer,usart4_para.rx_length, 100);
//			usart4_para.rx_length = 0;
//		}		
/**********************************************************************************************************/		

/********************************************按键外部中断测试**********************************************/
//		if(key_1_flag == 1)
//		{
//			set_led_state(LD1_PIN,LED_ON);
//			key_1_flag = 0;
//			HAL_Delay(50);
//		}
//		if(key_2_flag == 1)
//		{
//			set_led_state(LD1_PIN,LED_OFF);
//			key_2_flag = 0;
//			HAL_Delay(50);
//		}		
/**********************************************************************************************************/	

/*********************************************LED闪烁测试**************************************************/
//		set_led_state(LD1_PIN,LED_OFF);
//		set_led_state(LD2_PIN,LED_OFF);
//		set_led_state(LD3_PIN,LED_OFF);
//		set_led_state(LD4_PIN,LED_OFF);
//		HAL_Delay(100);
//		set_led_state(LD1_PIN,LED_ON);
//		set_led_state(LD2_PIN,LED_ON);
//		set_led_state(LD3_PIN,LED_ON);
//		set_led_state(LD4_PIN,LED_ON);			
//		HAL_Delay(100);
/**********************************************************************************************************/
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

int fputc(int ch,FILE *p)
{
	char c = ch;
	HAL_UART_Transmit(&huart3,(unsigned char *)&c, 1, 50);
	return ch;
}

/*!
*		\brief 中断回调函数
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case KEY_1:
			key_1_flag = 1;
			break;
		case KEY_2:
			key_2_flag = 1;
			break;
		case KEY_3:
			key_3_flag = 1;
			break;
		case BMP388_INT:
			bmp388_flag =1 ;
			break;
		
		default:
							break;
	}
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
