/*!
*			\file gnss.c
*			\brief gnss的驱动函数
*/

#include "gnss.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"







///*!
//*		\brief gnss gpio init
//*/
//void parseGpsBuffer(void)
//{
//	uint8_t hour[256];
//	int x;
//	char time[256];
//	if(usart2_para.GPS_TX[8]=='V'||usart2_para.GPS_TX[18]=='V'||usart2_para.GPS_TX[0]!='$')
//	{
//		err=1;
// 
//	}
//	
//	else if((usart2_para.GPS_TX[0]=='$' && usart2_para.GPS_TX[3]=='R' && usart2_para.GPS_TX[5]=='C') && usart2_para.GPS_TX[18]=='A')
//	{
//		memcpy(buf,usart2_para.GPS_TX,6);//$GPRMC
//		memcpy(time,usart2_para.GPS_TX+7,10);//时间
//		memcpy(usart2_para.tx_latitude,usart2_para.GPS_TX+20,9);//纬度
//		memcpy(usart2_para.N_S,usart2_para.GPS_TX+30,1);//纬度方向
//		memcpy(usart2_para.tx_longitude,usart2_para.GPS_TX+32,10);//经度
//		memcpy(usart2_para.E_W,usart2_para.GPS_TX+43,1);//经度方向
//		memcpy(usart2_para.spd,usart2_para.GPS_TX+45,5);//速度
//		
//		int y=atoi(time);
//		x=(y/10000)+8;
//		if(x<24)
//		{
//		hour[0]=(char)(x/10)+0x30;
//		hour[1]=(char)(x%10)+0x30;
//		}
//		else if (x>=24)
//		{
//			hour[0]=((x-24)/10)+0x30;
//			hour[1]=((x-24)%10)+0x30;
//		}
//		sprintf(usart2_para.tx_time,"%c%c:%c%c:%c%c",hour[0],hour[1],time[2],time[3],time[4],time[5]);
//		sta=1;

//	}	

//}

//void sanddata()
//{
//	char wei[256];
//	char jin[256];
//	if(sta==1)
//	{
//		sta=0;
//		HAL_UART_Transmit(&huart1,(unsigned char *)usart2_para.tx_time,8, 10);
//		HAL_UART_Transmit(&huart1,"\r\n",2,10);
//		
//		sprintf(wei,"%s:%s\r\n",usart2_para.N_S,usart2_para.tx_latitude);
//		HAL_UART_Transmit(&huart1,(unsigned char *)wei, strlen(wei), 50);
//		
//		sprintf(jin,"%s:%s\r\n",usart2_para.E_W,usart2_para.tx_longitude);
//		HAL_UART_Transmit(&huart1,(unsigned char *)jin, strlen(jin), 50);

//		HAL_UART_Transmit(&huart1,usart2_para.spd,5, 10);
//		HAL_UART_Transmit(&huart1,"**************\r\n",16,10);
//		HAL_Delay(1000);
//		LCD_DisplayStringLine(Line1, (u8 *)usart2_para.tx_time);
//	}
//}

//void error()
//{
//	
//	char STR[256];
//	if(err==1)
//	{
//		LCD_Clear(Black);
//		err=0;
//		sprintf(STR,"GPS DATA is not usefull!\r\n");
//	  HAL_UART_Transmit(&huart1,(unsigned char *)STR, strlen(STR),50);
//		HAL_Delay(1000);
//		HAL_UART_Transmit(&huart1,usart2_para.GPS_TX, usart2_para.rx_length,50);
//		HAL_UART_Transmit(&huart1,"\r",1,10);
//	}

//}

