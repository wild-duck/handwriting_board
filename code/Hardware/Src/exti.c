/**
  **************************************************************************************
  * @file exti.c
  * @author shaokairu
  * @date 2021.7.8
  * @brief This file provides the function of the external interrupt 
  **************************************************************************************
  */
  
/* Includes --------------------------------------------------------------------------*/
#include "exti.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "plot.h"
#include "adc.h"
#include "filter.h"
#include "fitted.h"

/* Public variables ------------------------------------------------------------------*/
extern uint16_t Ladc1;
extern uint16_t Ladc2;
extern uint16_t Ladc3;
extern int x, y;
extern uint8_t penState;

/* Private variables -----------------------------------------------------------------*/
uint8_t i;


/** @brief external interrupt function
  * @{
  */
  
/**
  * @brief external interrupt initialise, PA0,PA4
  * @param None
  * @retval None
  */
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();               //开启GPIOE时钟
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_4; 				//PE4
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;     	//上升沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
    
    //中断线0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
    
    //中断线4-PE4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);   	//抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);         	//使能中断线4
}


/**
  * @defgroup interrupt service function
  * @{
  */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);		//调用中断处理公用函数
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);		//调用中断处理公用函数
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);		//调用中断处理公用函数
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);		//调用中断处理公用函数
}

/**
  * @}
  */

//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号

/**
  * @brief  EXTI line detection callback
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  * @note All things of the interrupt program execution should be added in this function
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(5);      //消抖
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
            if(WK_UP==1) 
            {
                printf("PA0 press down\r\n");
				hui_graph();    // clear graph
            }
            break;
        case GPIO_PIN_4:
            if(KEY0==1)  
            {
                // printf("PE4 press down\r\n");                       
				printf("%d,%d,%d\r\n", Ladc1, Ladc2, Ladc3); 
            }
            break;
    }
}

/**********************************END OF FILE*****************************************/
