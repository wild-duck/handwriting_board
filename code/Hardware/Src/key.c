/**
  **************************************************************************************
  * @file key.c
  * @author shaokairu
  * @date 2021.7.8
  * @brief This file provides the function of the key which is on the core board sold
  *        by ALIENTEK  
  **************************************************************************************
  */
  
/* Includes --------------------------------------------------------------------------*/
#include "key.h"
#include "delay.h"

/** @defgroup key function
  * @{
  */

/**
  * @brief key initializtion
  * @param None
  * @retval None
  */
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();           //����GPIOEʱ��

    
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
	GPIO_Initure.Pin=GPIO_PIN_4; //PE2,3,4
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
    
}


// ԭ�ӵĺ���
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //�����ɿ���־
    if(mode==1)key_up=1;    //֧������
    if(key_up&&(KEY0==1||WK_UP==1))
    {
        delay_ms(10);
        key_up=0;
        if(KEY0==1)       return KEY0_PRES;
        else if(WK_UP==1) return WKUP_PRES;          
    }else if(KEY0==0&&WK_UP==0)key_up=1;
    return 0;   //�ް�������
}

/**
  * @}
  */

/**********************************END OF FILE*****************************************/
