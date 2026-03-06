/*!
*			\file led.c
*			\brief led的驱动函数
*/

#include "led.h"

/*!
*		\brief led gpio init
*/
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
		
	/*Configure GPIO pins :  PC12 PC13 PC14 PC15*/
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	/* Set LED state*/
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

}
/*!
*		\brief set led state
*		\input led 				在led.h中有宏定义
*					 led_state 	在led.h中有宏定义
*/
void set_led_state( uint16_t led, GPIO_PinState led_state)
{
	HAL_GPIO_WritePin(GPIOC, led			,	 led_state);
}

