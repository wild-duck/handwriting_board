/**
  **************************************************************************************
  * @file led.c
  * @author shaokairu
  * @date 2021.7.8
  * @brief This file provides all function define of led which is on the stm32 core board
  *        sold by ALIENTEK 
  **************************************************************************************
  */
  
/* Includes --------------------------------------------------------------------------*/
#include "led.h"

/**
  * @brief led gpio initializtion
  * @param None
  * @retval None
  */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOB时钟
	__HAL_RCC_GPIOE_CLK_ENABLE();           	//开启GPIOE时钟
	
    GPIO_Initure.Pin=GPIO_PIN_5; 				//PB5
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_5; 				//PE5
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);	//PB5置1，默认初始化后灯灭
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);	//PE5置1，默认初始化后灯灭
}
