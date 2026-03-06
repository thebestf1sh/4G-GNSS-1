/*!
*			\file 4g_a7600c1.c
*			\brief 4g模块的驱动函数
*/

#include "4g_a7600c1.h"
//#define V_25TER
#define STATUS_CONTROL
#define NETWORK
#define PACKET_DOMAIN
#define SIM_CARD
#define CALL_CONTROL
#define PHONE_BOOK
#define SMS
#define SERIAL_INTERFACE
#define HARDWARE
#define FILE_SYSTEM
#define FILE_TRANSMISSION
#define INTERNER_SERVICE
#define MQTT

a7600c1_para a7600c1_data;
a7600c1_rx_data a7600c1_rxdata;
/*!
*		\brief a7600c1
*/
void a7600c1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
		
	/*Configure GPIO pins : PC6 PC7 */
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);
	/*Configure GPIO pin : PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
/*!	
*		\brief a7600c1发送at命令
*/
void a7600c1_send_at_cmd(uint8_t *pdata,uint16_t length)
{
	HAL_UART_Transmit(&huart3 ,pdata,length, 100);
}

/*!
*		\brief a7600c1等待接收at命令的返回
*		\input time 等待时间，等待之后还没收到就不收了
*		\output state 0 没接收到
*									1 接收成功
*/
uint8_t a7600c1_wait_at_reply(uint8_t time )
{
	uint8_t state;
	/*wait for rcv*/
	while(time--)
	{
		HAL_Delay(1);
		if(usart3_para.rx_length==0)
		{
			state = 0;
		}
		else{
			state = 1;
			memcpy(a7600c1_rxdata.a7600c1_rx,usart3_para.rx_buffer,usart3_para.rx_length);
			a7600c1_rxdata.length = usart3_para.rx_length;
			usart3_para.rx_length = 0;
			break;
		}		
	}
	
	return state;
}


uint8_t ascii_to_hex(uint8_t ascii)
{
	uint8_t hex;
	hex = ascii - 0x30;
	if(hex>0x09)
	{
		return 10;
	}
	return hex;
	
	
}

/****************************AT		COMMAND		V.25TER**************************************/
/*先写格式，需要的话再填写相应的判断*/
#ifdef V_25TER

/*!
*			\brief ATD Mobile originated call to dial anumbe  拨打电话
*			
*/
uint8_t a7600c1_call_dial_number(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief ATA Call answer  接听电话
*			
*/
uint8_t a7600c1_call_answer(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief ATH Disconnect existing call  挂断电话
*			
*/
uint8_t a7600c1_disconnect_exiting_call(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief ATS0 Automatic answer incoming calL  设置自动应答
*			
*/
uint8_t a7600c1_auto_answer_call(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief +++ Switch from data mode to command mode 从数据模式切换到命令模式
*			
*/
uint8_t a7600c1_switch_from_data_mode_to_cmd_mode(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief ATO Switch from command mode to data mode 从命令模式切换到数据模式
*			
*/
uint8_t a7600c1_switch_from_cmd_mode_to_data_mode(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief ATI Display product identification information 显示产品标志信息
*			
*/
uint8_t a7600c1_display_product_identification_info(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief ATE Enable command echo 使能命令回传
*			
*/
uint8_t a7600c1_enable_command_echo(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief AT&V Display current configuration 显示当前配置信息
*			
*/
uint8_t a7600c1_display_current_configuration(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief ATV Set result code format mode	设置结果代码格式模式
*			
*/
uint8_t a7600c1_set_result_code_format_mode(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief AT&F Set all current parameters to manufacturer defaults 将所有参数恢复出厂设置
*			
*/
uint8_t a7600c1_set_all_parameter_to_manufacturer_defaults(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief ATQ Set Result Code Presentation Mode 设置结果代码显示模式
*			
*/
uint8_t a7600c1_set_result_code_pressentation_mode(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief ATX Set CONNECT Result Code Format 设置连接结果代码格式
*			
*/
uint8_t a7600c1_set_connect_result_code_format(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief AT&W Save the user setting to ME 存储用户设置到移动设备中
*			
*/
uint8_t a7600c1_save_user_setting_to_ME(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief ATZ Restore the user setting from ME 从移动设备中还原用户设置
*			
*/
uint8_t a7600c1_restore_user_setting_from_ME(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief AT+CGMI Request manufacturer identification	请求制造商消息
*			
*/
uint8_t a7600c1_request_manufacturer_identification(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief AT+CGMR Request revision identification	请求固件版本信息
*			
*/
uint8_t a7600c1_request_revision_identification(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief AT+CGSN Request product serial number identification	请求产品序列号信息
*			
*/
uint8_t a7600c1_request_product_serial_number_identification(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief AT+CSCS Select TE character set 选择终端设备的字符库
*			
*/
uint8_t a7600c1_select_TE_character_set(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief AT+GCAP Request overall capabilities 请求报告附加功能表
*			
*/
uint8_t a7600c1_request_overall_capabilities(a7600c1_para *handle)
{
	
	return 0;
}

#endif



/****************************AT		STATUS		CONTROL**************************************/
#ifdef STATUS_CONTROL
/*!
*			\brief AT+CFUN Set phone functionality 设置电话的工作模式
*			\input level
*						 0：最小工作模式
*						 1：全功能模式，在线模式
*						 4：禁用手机收发射频电路
*						 5：工厂测试模式（在a7600产品下，与1的模式一样
*						 6：RESET
*						 7：掉线模式
*						 a7600c1_get_phone_functionality 查询工作模式
*/
uint8_t a7600c1_set_phone_functionality(a7600c1_para *handle,uint8_t level)
{
	uint8_t state;
	uint8_t cmd[11] = "AT+CFUN=1\r\n";
	cmd[8] = level+0x30;
	a7600c1_send_at_cmd(cmd,11);
	state = a7600c1_wait_at_reply(20);
	return state;
}
uint8_t a7600c1_get_phone_functionality(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[11] = "AT+CFUN?\r\n";
	a7600c1_send_at_cmd(cmd,10);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				handle->functionality_level = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-5]);
				state = 1;
			}
		}
	}
	return state;
}
/*!
*			\brief AT+CSQ Query signal quality	确认信号质量
*			\param rssl: 信号强度指示 1-31  99代表没检测到
*						 ber:	误码率	0 小于万分之一  1 小于千分一大于万分之一
*/
uint8_t a7600c1_inquire_csq(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[8] = "AT+CSQ\r\n";
	
	a7600c1_send_at_cmd(cmd,8);
	state = a7600c1_wait_at_reply(20);
	/*如果获取到csq消息*/
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				if((a7600c1_rxdata.a7600c1_rx[i-8]>0x30)&&(a7600c1_rxdata.a7600c1_rx[i-8]<=0x39))
				{
					handle->rssl = 10*ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-8])+ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-7]);
					handle->ber = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-5]);
					state = 1;
				}
				else
				{
					handle->rssl = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-7]);
					handle->ber = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-5]);
					state = 1;					
				}
			}
		}
	}
	return state;
}

/*!
*			\brief AT+AUTOCSQ Set CSQ report 设置是否自动报告csq信息，以及上报消息的方式
*						 AT+AUTOCSQ? 查询是否自动报告
*						 AT+AUTOCSQ=auto,mode     set  ：0  disable 
*																						 1	enable
*																			mode ：0	五秒报告一次
*																						 1	在rssi与ber改变之后才报告一次
*/
uint8_t a7600c1_set_csq_auto_report(a7600c1_para *handle,uint8_t set,uint8_t mode)
{
	uint8_t state;
	uint8_t cmd[16] = "AT+AUTOCSQ=0,0\r\n";
	cmd[11] = set+0x30;
	cmd[13] = mode+0x30;
	a7600c1_send_at_cmd(cmd,16);
	state = a7600c1_wait_at_reply(20);
	return state;
}
/*!
*			\brief AT+CSQDELTA Set RSSI delta change threshold	设置rssi变化的阈值，用于上个命令判断是否报告？	
*/
uint8_t a7600c1_setrssi_delta_change_threshold(a7600c1_para *handle,uint8_t threshold)
{
	uint8_t state;
	uint8_t cmd[15] = "AT+CSQDELTA=0\r\n";
	cmd[12] = threshold+0x30;	
	a7600c1_send_at_cmd(cmd,15);
	state = a7600c1_wait_at_reply(20);
	return state;
}

/*!
*			\brief AT+CPOF Power down the module 关机
*			
*/
uint8_t a7600c1_power_down_the_module(a7600c1_para *handle)
{
	uint8_t state;
	uint8_t cmd[11] = "AT+CPOF\r\n";
	a7600c1_send_at_cmd(cmd,9);
	state = a7600c1_wait_at_reply(20);
	return state;

}

/*!
*			\brief AT+CRESET Reset the module	重启	
*			
*/
uint8_t a7600c1_reset_the_module(a7600c1_para *handle)
{
	uint8_t state;
	uint8_t cmd[11] = "AT+CRESET\r\n";
	a7600c1_send_at_cmd(cmd,11);
	state = a7600c1_wait_at_reply(20);
	return state;
}

/*!
*			\brief AT+CACM Accumulated call meter 重置sim文件中的部分关于累计呼叫表的内容
*			
*/
uint8_t a7600c1_reset_accumulated_call_meter(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief AT+CAMM Accumulated call meter maximum	累计呼叫表满了的话，会发出通知
*			
*/
uint8_t a7600c1_report_accumulated_call_meter_maximum(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief AT+CPUC Price per unit and currency table 设置资费价格，货币等信息
*			
*/
uint8_t a7600c1_set_price_per_unit_and_currency_table(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief AT+CCLK Real time clock management 实时时钟管理
*			
*/
uint8_t a7600c1_set_real_time_module(a7600c1_para *handle)
{
	uint8_t state;
	uint8_t cmd[32] = "AT+CCLK=\"14/01/01,02:14:36+08\"\r\n";
	/*年*/
	cmd[9] = (handle->real_time.year>>8)+'0';
	cmd[10] = (handle->real_time.year&0xff)+'0';
	/*月*/
	cmd[12] = (handle->real_time.mouth>>8)+'0';
	cmd[13] = (handle->real_time.mouth&0xff)+'0';
	/*日*/
	cmd[15] = (handle->real_time.day>>8)+'0';
	cmd[16] = (handle->real_time.day&0xff)+'0';
	/*时*/
	cmd[18] = (handle->real_time.hour>>8)+'0';
	cmd[19] = (handle->real_time.hour&0xff)+'0';
	/*分*/
	cmd[21] = (handle->real_time.minute>>8)+'0';
	cmd[22] = (handle->real_time.minute&0xff)+'0';
	/*秒*/
	cmd[24] = (handle->real_time.sec>>8)+'0';
	cmd[25] = (handle->real_time.sec&0xff)+'0';
	/*时区*/
	cmd[27] = (handle->real_time.time_zone>>8)+'0';
	cmd[28] = (handle->real_time.time_zone&0xff)+'0';
	
	a7600c1_send_at_cmd(cmd,32);
	state = a7600c1_wait_at_reply(20);
	return state;
}

uint8_t a7600c1_read_real_time_module(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[11] = "AT+CFUN?\r\n";
	a7600c1_send_at_cmd(cmd,10);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				handle->real_time.year = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-25]);
				handle->real_time.year = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-24]);
				
				handle->real_time.mouth = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-22]);
				handle->real_time.mouth = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-21]);			
				
				handle->real_time.day = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-19]);
				handle->real_time.day = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-18]);				
				
				handle->real_time.hour = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-16]);
				handle->real_time.hour = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-15]);				
				
				handle->real_time.minute = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-13]);
				handle->real_time.minute = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-12]);				

				handle->real_time.sec = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-10]);
				handle->real_time.sec = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-9]);

				handle->real_time.time_zone = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-7]);
				handle->real_time.time_zone = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-6]);				
				
				state = 1;
			}
		}
	}
	return state;
}
/*!
*			\brief AT+CMEE Report mobile equipment error 修改错误报告的详细性
*			
*/
uint8_t a7600c1_change_module_equiment_error_report_format(a7600c1_para *handle,uint8_t error_level)
{
	uint8_t state;
	uint8_t cmd[11] = "AT+CMEE=2\r\n";
	cmd[8] = error_level+'0';
	a7600c1_send_at_cmd(cmd,11);
	state = a7600c1_wait_at_reply(20);
	return state;
}
/*!
*			\brief AT+CPAS Phone activity status	移动终端的活动状态
*			
*/
uint8_t a7600c1_get_ME_activity_status(a7600c1_para *handle)
{
	return 0;
}

/*!
*			\brief AT+SIMEI Set the IMEI for the module 设置模块的imel值
*			
*/
uint8_t a7600c1_set_IMEI(a7600c1_para *handle)
{
	
	return 0;
}

#endif




/****************************AT  						NETWORK**************************************/
#ifdef NETWORK
/*!
*			\briefAT AT+CREG Network registration 网络注册相关
*			
*/
uint8_t a7600c1_network_registration(a7600c1_para *handle)
{
	
	return 0;
}


/*!
*			\briefAT AT+COPS Operator selection	配置选择相关
*			
*/
uint8_t a7600c1_operator_selection(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CUSD Unstructured supplementary service data	非结构化补充服务数据
*			
*/
uint8_t a7600c1_unstructured_supplementary_service_data(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSSN Supplementary service notifications	初级服务通知
*			
*/
uint8_t a7600c1_supplementary_service_notifications(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPOL Preferred operator list 首选运算符列表
*			
*/
uint8_t a7600c1_preferred_operator_list(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+COPN Read operator names 获取操作符的名称
*			
*/
uint8_t a7600c1_read_operator_names(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CNMP Preferred mode selection	优选模式选择
*			
*/
uint8_t a7600c1_preferred_mode_selection(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CNBP Preferred band selection 优选波段选择
*			
*/
uint8_t a7600c1_preferred_band_selection(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPSI Inquiring UE system information 确认用户设备系统的信息
*			
*/
uint8_t a7600c1_inquiring_UE_system_information(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CNSMOD Show network system mode	显示当前网络系统模式
*			
*/
uint8_t a7600c1_read_network_system_mode(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CTZU Automatic time and time zone update 用于取值NITZ的时间与时区更新
*			
*/
uint8_t a7600c1_auto_time_and_time_zone_update(a7600c1_para *handle)
{
	
	return 0;
}


/*!
*			\briefAT AT+CTZR Time and time zone reporting			报告时间以及时区信息
*			
*/
uint8_t a7600c1_report_time_and_time_zone(a7600c1_para *handle)
{
	
	return 0;
}

#endif

/****************************AT  	PACKET		DOMAIN***************************************/
#ifdef PACKET_DOMAIN
/*!
*			\briefAT AT+CGREG Network registration status	网络注册状态
*			
*/
uint8_t a7600c1_read_network_registration_status(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[11] = "AT+CGREG?\r\n";
	a7600c1_send_at_cmd(cmd,11);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				handle->cgreg = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-5]);
				state = 1;
			}
		}
	}
	return state;
}

/*!
*			\briefAT AT+CEREG EPS network registration status 
*			
*/
uint8_t a7600c1_read_esp_network_registration_status(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[11] = "AT+CEREG?\r\n";
	a7600c1_send_at_cmd(cmd,11);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				handle->cereg = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-5]);
				state = 1;
			}
		}
	}
	return state;
}

/*!
*			\briefAT AT+CGATT Packet domain attach or detach 包域附着或者分离 附着网络？
*			
*/
uint8_t a7600c1_packet_domain_attach_or_detach(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[11] = "AT+CGATT?\r\n";
	a7600c1_send_at_cmd(cmd,11);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				handle->cgatt = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-5]);
				state = 1;
			}
		}
	}
	return state;
}

/*!
*			\briefAT AT+CGACT PDP context activate or deactivate PDP上下文激活或者禁用
*			
*/
uint8_t a7600c1_PDP_context_activate_or_deactivate(a7600c1_para *handle)
{
	
	return 0;
}


/*!
*			\briefAT AT+CGDCONT Define PDP context	定义PDP上下文
*			
*/
uint8_t a7600c1_define_PDP_context(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGDSCONT Define Secondary PDP Context	定义辅助PDP上下文
*			
*/
uint8_t a7600c1_define_secondary_PDP_context(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CGTFT Traffic Flow Template	交通流模板
*			
*/
uint8_t a7600c1_traffic_flow_template(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CGQREQ Quality of service profile (requested 服务质量配置文件(请求
*			
*/
uint8_t a7600c1_quality_of_service_profile(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGEQREQ 3G quality of service profile (requested	3G服务质量配置文件(请求
*			
*/
uint8_t a7600c1_3g_quality_of_service_profile(a7600c1_para *handle)
{
	
	return 0;
}


/*!
*			\briefAT AT+CGQMIN Quality of service profile (minimum acceptable) 最低可接受服务质量
*			
*/
uint8_t a7600c1_quality_of_service_profile_min(a7600c1_para *handle)
{
	
	return 0;
}


/*!
*			\briefAT AT+CGEQMIN 3G quality of service profile (minimum acceptable 最低可接收3G服务质量
*			
*/
uint8_t a7600c1_3g_quality_of_service_profile_min(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGDATA Enter data state 进入数据状态
*			
*/
uint8_t a7600c1_enter_data_state(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGPADDR Show PDP address 读pdp地址
*			
*/
uint8_t a7600c1_read_PDP_address(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGCLASS GPRS mobile station class	设置gprs monile station class
*			
*/
uint8_t a7600c1_gprs_mobile_station_class(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGEREP GPRS event reporting gprs 事件报告
*			
*/
uint8_t a7600c1_gprs_event_reporting(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CGAUTH Set type of authentication for PDP-IP connections of GPRS GPRS PDP-IP连接设置的认证类型
*			
*/
uint8_t a7600c1_set_PDP_IP_type_of_authentication(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CPING Ping destination address 	ping目的地地址
*			
*/
uint8_t a7600c1_ping_destination_address(a7600c1_para *handle)
{
	uint8_t state,i;
	uint8_t cmd[48] = "AT+CPING=\"www.baidu.com\",1,4,64,1000,10000,255\r\n";
	a7600c1_send_at_cmd(cmd,48);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'C')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'P')&&(a7600c1_rxdata.a7600c1_rx[i+7] == '3'))
			{
				handle->ping_baidu_result = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i+13]);
				state = 1;
			}
		}
	}
	return state;
}

#endif

/****************************AT  	SIM 			CARD*****************************************/
#ifdef SIM_CARD
/*!
*			\briefAT AT+CICCID Read ICCID from SIM card	读sim卡的iccid号码
*			
*/
uint8_t a7600c1_read_ICCID_from_SIM_card(a7600c1_para *handle)
{
	uint8_t state,i,j;
	uint8_t cmd[48] = "AT+CPING=\"www.baidu.com\",1,4,64,1000,10000,255\r\n";
	a7600c1_send_at_cmd(cmd,48);
	state = a7600c1_wait_at_reply(20);
	if(state == 1)
	{
		state = 0;
		for(i=0;i<a7600c1_rxdata.length;i++)
		{
			if((a7600c1_rxdata.a7600c1_rx[i] == 'O')&&(a7600c1_rxdata.a7600c1_rx[i+1] == 'K'))
			{
				for(j=0;j<20;j++)
				{
					handle->iccid[j] = ascii_to_hex(a7600c1_rxdata.a7600c1_rx[i-24+j]);
				}
				state = 1;
			}
		}
	}
	return state;
}

/*!
*			\briefAT AT+CPIN Enter PIN	检测是否插入sim卡
*			
*/
uint8_t a7600c1_enter_pin(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CLCK Facility lock 设备锁
*			
*/
uint8_t a7600c1_facility_lock(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPWD Change password 修改密码
*			
*/
uint8_t a7600c1_change_password(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CIMI Request international mobile subscriber identity 请求国际身份认证（应该就是电话号
*			
*/
uint8_t a7600c1_read_IMSI(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSIM Generic SIM access 	通用SIM访问
*			
*/
uint8_t a7600c1_generic_sim_access(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CRSM Restricted SIM access	受限制的SIM访问
*			
*/
uint8_t a7600c1_restricted_sim_access(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+SPIC Times remain to input SIM PIN/PUK 输入sim  pin/puk所需要的时间
*			
*/
uint8_t a7600c1_times_remain_to_input_sim_pin_puk(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSPN Get service provider name from SIM 获取sim运营商的名字
*			
*/
uint8_t a7600c1_read_sim_service_provider_name(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+UIMHOTSWAPON Set UIM Hotswap Function On	设置sim卡热插拔功能
*			
*/
uint8_t a7600c1_set_uim_hotswap(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+UIMHOTSWAPLEVEL Set UIM Card Detection Level 设置sim卡的插入检测电平
*			
*/
uint8_t a7600c1_set_uim_card_detection_level(a7600c1_para *handle)
{
	
	return 0;
}

#endif

/****************************AT  	CALL			CONTROL**************************************/
#ifdef CALL_CONTROL
/*!
*			\briefAT AT+CVHU Voice hang up control 话音挂断控制
*			
*/
uint8_t a7600c1_voice_hang_up_control(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CHUP Hang up call	挂断电话	
*			
*/
uint8_t a7600c1_hang_up_call(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CBST Select bearer service type 选择承载业务类型
*			
*/
uint8_t a7600c1_select_bearer_service_type(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CRLP Radio link protocol 无线链路协议
*			
*/
uint8_t a7600c1_radio_link_protocol(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CLCC List current calls 列出当前呼叫
*			
*/
uint8_t a7600c1_list_current_calls(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CEER Extended error report 扩展错误报告
*			
*/
uint8_t a7600c1_extended_error_report(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CCWA Call waiting 呼叫等待
*			
*/
uint8_t a7600c1_call_waiting(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CCFC Call forwarding number and conditions  呼叫转移相关
*			
*/
uint8_t a7600c1_call_forwarding_number_and_conditions(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CLIP Calling line identification presentation 呼叫线路标志表示
*			
*/
uint8_t a7600c1_calling_line_identfication_presentation(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CLIR Calling line identification restriction	呼叫线路识别限制
*			
*/
uint8_t a7600c1_calling_line_identfication_restrication(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+COLP Connected line identification presentation	连接线路标志表示
*			
*/
uint8_t a7600c1_connected_line_identfication_presentation(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+VTS DTMF and tone generation 双音多频以及音调生成
*			
*/
uint8_t a7600c1_DTMF_and_tone_generation(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+VTD Tone duration	音调持续时间
*			
*/
uint8_t a7600c1_tone_duration(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSTA Select type of address 选择地址的种类
*			
*/
uint8_t a7600c1_select_type_of_address(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CMOD Call mode 呼叫模式
*			
*/
uint8_t a7600c1_call_mode(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+VMUTE Speaker mute control	扬声器静音控制
*			
*/
uint8_t a7600c1_speaker_mute_control(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CMUT Microphone mute control	麦克风静音控制
*			
*/
uint8_t a7600c1_microphone_mute_control(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CSDVC Switch voice channel device 交换话音通道装置
*			
*/
uint8_t a7600c1_switch_voice_channel_device(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT AT+CMICGAIN Adjust mic gain	调整麦克增益
*			
*/
uint8_t a7600c1_adjust_mic_gain(a7600c1_para *handle)
{
	
	return 0;
}

/*
*			\briefAT AT+COUTGAIN Adjust out gain	调整输出增益	
*			
*/
uint8_t a7600c1_adjust_out_gain(a7600c1_para *handle)
{
	
	return 0;
}


#endif

/****************************AT  	PHONE			BOOK*****************************************/
#ifdef PHONE_BOOK
/*!
*			\briefAT AT+CPBS Select phonebook memory storage 选择电话簿内存存储
*			
*/
uint8_t a7600c1_select_phonebook_memory_storage(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPBR Read phonebook entries 阅读电话簿条目
*			
*/
uint8_t a7600c1_read_phonebool_entries(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPBF Find phonebook entries 寻找电话簿条目
*			
*/
uint8_t a7600c1_find_phonebool_entries(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPBW Write phonebook entry	写电话簿条目
*			
*/
uint8_t a7600c1_write_phonebool_entries(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CNUM Subscriber number	订阅户号码
*			
*/
uint8_t a7600c1_subscriber_number(a7600c1_para *handle)
{
	
	return 0;
}


#endif





/****************************AT  	PHONE			BOOK*****************************************/
#ifdef SMS
/*!
*			\briefAT AT+CSMS Select message service	选择短信服务
*			
*/
uint8_t a7600c1_select_message_service(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CPMS Preferred message storage 首选短信存储
*			
*/
uint8_t a7600c1_preferred_message_storage(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CMGF Select SMS message format	选择sms短信格式
*			
*/
uint8_t a7600c1_select_sms_message_format(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSCA SMS service centre address	SMS中心服务地址
*			
*/
uint8_t a7600c1_SMS_service_centre_address(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSCB Select cell broadcast message indication 选择小区消息广播
*			
*/
uint8_t a7600c1_select_cell_broadcast_message_indication(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSMP Set text mode parameters	设置文本模式参数
*			
*/
uint8_t a7600c1_set_text_mode_parameters(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CSDH Show text mode parameters	显示文本模式参数
*			
*/
uint8_t a7600c1_show_text_mode_parameters(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CNMA New message acknowledgement to ME/TA 对ME/TA的确认
*			
*/
uint8_t a7600c1_new_message_acknowledgement_to_me_ta(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CNMI New message indications to TE	向TE发送一条新消息提示
*			
*/
uint8_t a7600c1_new_message_indications_TE(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CGSMS Select service for MO SMS messages	为mo sms信息选择服务
*			
*/
uint8_t a7600c1_select_service_for_mo_sms_messages(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CMGL List SMS messages from preferred store	列出来自首选存储区的sms信息
*			
*/
uint8_t a7600c1_list_sms_messages_from_preferred_store(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT AT+CMGR Read message	获取短信
*			
*/
uint8_t a7600c1_read_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT	AT+CMGS Send message 发送短信
*			
*/
uint8_t a7600c1_send_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT	AT+CMSS Send message from storage	从存储器发送消息
*			
*/
uint8_t a7600c1_send_message_from_storage(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT	AT+CMGW Write message to memory	写消息到存储器里面
*			
*/
uint8_t a7600c1_write_message_to_memory(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT	AT+CMGD Delete message	删除消息
*			
*/
uint8_t a7600c1_delete_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT	AT+CMGMT Change message status	修改短信状态
*			
*/
uint8_t a7600c1_change_message_status(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CMVP Set message valid period	设置消息的有效期
*			
*/
uint8_t a7600c1_set_message_valid_period(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CMGRD Read and delete message	读取并且删除短信
*			
*/
uint8_t a7600c1_read_and_delete_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CMGSEX Send message	发送短信
*			
*/
uint8_t a7600c1_send_message_ex(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CMSSEX Send multi messages from storage	从存储器发送多条消息
*			
*/
uint8_t a7600c1_send_multi_messages_from_storage(a7600c1_para *handle)
{
	
	return 0;
}

#endif








/****************************AT  	PHONE			BOOK*****************************************/
#ifdef SERIAL_INTERFACE
/*!
*			\briefAT  AT&D Set DTR function mode	设置DTR功能模式
*			
*/
uint8_t a7600c1_set_DTR_function_mode(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT&C Set DCD function mode	设置DCD功能模式
*			
*/
uint8_t a7600c1_set_DCD_function_mode(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\briefAT  AT+IPR Set local baud rate temporarily	临时设置本体波特率
*			
*/
uint8_t a7600c1_set_local_baud_rate_temporaily(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+IPREX Set local baud rate permanently	永久设置本体波特率
*			
*/
uint8_t a7600c1_set_local_baud_rate_permanently(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+ICF Set control character framing	设置控制字符帧
*			
*/
uint8_t a7600c1_set_control_character_framing(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+IFC Set local data flow control 设置本地数据流控制
*			
*/
uint8_t a7600c1_set_local_data_flow_control(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CSCLK Control UART Sleep	控制串口休眠
*			
*/
uint8_t a7600c1_control_uart_sleep(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CMUX Enable the multiplexer over the UART 在串口是启用复用器
*			
*/
uint8_t a7600c1_enable_the_multiplexer_over_the_uart(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CATR Configure URC destination interface	配置urc目标接口
*			
*/
uint8_t a7600c1_urc_destination_interface(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CFGRI Configure RI pin	配置RI引脚
*			
*/
uint8_t a7600c1_configure_RI_pin(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CURCD Configure the delay time and number of URC	配置URC的延迟时间和次数
*			
*/
uint8_t a7600c1_configure_delay_time_and_number_of_URC(a7600c1_para *handle)
{
	
	return 0;
}

#endif



/****************************AT  						HARDWARE*************************************/
#ifdef HARDWARE
/*!
*			\briefAT  AT+CVALARM Low and high voltage Alarm	高低压报警
*			
*/
uint8_t a7600c1_low_and_high_voltage_alarm(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\briefAT  AT+CVAUXS Set state of the pin named VDD_AUX	设置vdd_aux引脚的状态
*			
*/
uint8_t a7600c1_set_vdd_aux_state(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CVAUXV Set voltage value of the pin named VDD_AUX 设置VDD_AUX的值
*			
*/
uint8_t a7600c1_set_vdd_aux_value(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CADC Read ADC value	读adc的值
*			
*/
uint8_t a7600c1_read_adc_value(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CADC2 Read ADC2 value	读adc2的值
*			
*/
uint8_t a7600c1_read_adc2_value(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CMTE Control the module critical temperature URC alarm	设置模块的临界温度urc报警
*			
*/
uint8_t a7600c1_control_the_module_critical_temperature_urc_alarm(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CPMVT Low and high voltage Power Off			高低压断电（保护？
*			
*/
uint8_t a7600c1_low_and_high_voltage_power_off(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CRIIC Read values from register of IIC device nau8810	从I2C设备nau8810的寄存器中读值
*			
*/
uint8_t a7600c1_read_data_from_nau8810(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CWIIC Write values to register of IIC device nau8810		向I2C设备nau8810的寄存器中写值
*			
*/
uint8_t a7600c1_write_data_to_nau8810(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CBC Read the voltage value of the power supply		读供电电压值
*			
*/
uint8_t a7600c1_read_the_voltage_value_of_the_power_supply(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CPMUTEMP Read the temperature of the module	读模块的温度
*			
*/
uint8_t a7600c1_read_the_temperature_of_the_module(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CGDRT Set the direction of specified GPIO	设置GPIO口的方向
*			
*/
uint8_t a7600c1_set_the_direction_of_specified_gpio(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CGSETV Set the value of specified GPIO	设置GPIO口的值
*			
*/
uint8_t a7600c1_set_the_value_of_specified_gpio(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CGGETV Get the value of specified GPIO	读取GPIO口的值
*			
*/
uint8_t a7600c1_get_the_value_of_specified_gpio(a7600c1_para *handle)
{
	
	return 0;
}
#endif
/****************************AT  	FILE			SYSTEM***************************************/
#ifdef FILE_SYSTEM
/*!
*			\brief	AT+FSCD Select directory as current directory	选择目录作为当前目录
*			
*/
uint8_t a7600c1_select_directory_as_curremt_directory(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+FSMKDIR Make new directory in current directory	在当前目录中创建新目录
*			
*/
uint8_t a7600c1_make_new_directoryin_current_directory(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+FSRMDIR Delete directory in current directory	在当前目录中删除目录
*			
*/
uint8_t a7600c1_delete_directory_in_current_directory(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+FSLS List directories/files in current directory		列出当前目录中的文件夹/文件
*			
*/
uint8_t a7600c1_list_directories_files_in_current_directory(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+FSDEL Delete file in current directory	 	在当前目录中删除文件
*			
*/
uint8_t a7600c1_delete_files_in_current_directory(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+FSRENAME Rename file in current directory	在当前目录中重命名文件
*			
*/
uint8_t a7600c1_rename_files_in_current_directory(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+FSATTRI Request file attributes	请求文件属性
*			
*/
uint8_t a7600c1_request_file_attributes(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+FSMEM Check the size of available memory		检查文件属性存储器的大小
*			
*/
uint8_t a7600c1_check_the_size_of_available_memory(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+FSCOPY Copy an appointed file	复制指定的文件
*			
*/
uint8_t a7600c1_copy_an_appointed_file(a7600c1_para *handle)
{
	
	return 0;
}

#endif

/****************************AT  	FILE			TRANSMISSION*********************************/
#ifdef FILE_TRANSMISSION
/*!
*			\brief	AT+CFTRANRX Transfer a file to EFS	发送文件到efs中
*			
*/
uint8_t a7600c1_transfer_a_file_to_efs(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CFTRANTX Transfer a file from EFS to host	发送文件到host
*			
*/
uint8_t a7600c1_traansfer_a_file_from_efs_to_host(a7600c1_para *handle)
{
	
	return 0;
}

#endif

/****************************AT  	INTERNER	SERVICE**************************************/
#ifdef INTERNER_SERVICE
/*!
*			\brief	AT+CHTPSERV Set HTP server information	设置HTP服务信息
*			
*/
uint8_t a7600c1_set_htp_server_infomation(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CHTPUPDATE Updating date time using HTP protocol 	使用htp协议更新时间
*			
*/
uint8_t a7600c1_updata_time_using_htp_protocol(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CNTP Update system time	更新系统时间
*			
*/
uint8_t a7600c1_updata_system_time(a7600c1_para *handle)
{
	uint8_t state;
	uint8_t cmd[28] = "AT+CNTP=\"time1.aliyun.com\"\r\n";
	uint8_t cmd1[9] = "AT+CNTP\r\n";
	a7600c1_send_at_cmd(cmd,28);
	state = a7600c1_wait_at_reply(100);
	
	a7600c1_send_at_cmd(cmd1,9);
	state = a7600c1_wait_at_reply(100);
	return state;
}
#endif
/****************************AT  						MQTT*****************************************/
#ifdef MQTT	
/*!
*			\brief	AT+CMQTTSTART Start MQTT service	开启MQTT服务
*			
*/
uint8_t a7600c1_start_mqtt_service(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTSTOP Stop MQTT service	停止mqtt服务
*			
*/
uint8_t a7600c1_stop_mqtt_service(a7600c1_para *handle)
{	 
	
	return 0;
}
/*!
*			\brief	AT+CMQTTACCQ Acquire a client	询问用户端
*			
*/
uint8_t a7600c1_acquire_a_client(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTREL Release a client 释放客户端
*			
*/
uint8_t a7600c1_release_a_client(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTSSLCFG Set the SSL context (only for SSL/TLS MQTT)	设置ssl上下文
*			
*/
uint8_t a7600c1_set_ssl_context(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTWILLTOPIC Input the topic of will message	输入信息的主题
*			
*/
uint8_t a7600c1_input_the_topic_of_will_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTWILLMSG Input the will message	输入信息
*			
*/
uint8_t a7600c1_input_the_will_message(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CMQTTCONNECT Connect to MQTT server 连接mqtt服务器
*			
*/
uint8_t a7600c1_connect_mqtt_server(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTDISC Disconnect from server	断开服务器连接
*			
*/
uint8_t a7600c1_disconnect_mqtt_server(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTTOPIC Input the topic of publish message	输入发布消息的主题
*			
*/
uint8_t a7600c1_input_the_topic_of_publish_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTPAYLOAD Input the publish message	输入发布消息
*			
*/
uint8_t a7600c1_input_the_publish_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTPUB Publish a message to server		发布消息到服务器
*			
*/
uint8_t a7600c1_publish_a_message_to_server(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTSUBTOPIC Input the topic of subscribe message		输入订阅消息的主题
*			
*/
uint8_t a7600c1_input_the_topic_of_subscribe_message(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CMQTTUNSUBTOPIC Input the topic of unsubscribe message		输入取消订阅消息的主题
*			
*/
uint8_t a7600c1_input_the_topic_of_unsubscribe_message(a7600c1_para *handle)
{
	
	return 0;
}
/*!
*			\brief	AT+CMQTTUNSUB Unsubscribe a message to server		取消订阅到服务器
*			
*/
uint8_t a7600c1_unsubscribe_a_message_to_server(a7600c1_para *handle)
{
	
	return 0;
}

/*!
*			\brief	AT+CMQTTCFG Configure the MQTT Context		配置MQTT上下文
*			
*/
uint8_t a7600c1_config_mqtt_context(a7600c1_para *handle)
{
	
	return 0;
}


#endif



