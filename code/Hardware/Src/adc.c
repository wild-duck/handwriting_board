/**
  **************************************************************************************
  * @file adc.c
  * @author shaokairu
  * @date 2021.7.8
  * @brief This file provides the function of adc 
  **************************************************************************************
  */
  
/* Includes --------------------------------------------------------------------------*/
#include "adc.h"
#include "delay.h"

/* Private handle --------------------------------------------------------------------*/
ADC_HandleTypeDef ADC1_Handler;		//ADC句柄

/**
  * @brief adc1 initialise
  * @param None
  * @retval None
  */
void ADC1_Init(void)
{ 
	RCC_PeriphCLKInitTypeDef ADC_CLKInit;
	
	ADC_CLKInit.PeriphClockSelection=RCC_PERIPHCLK_ADC;			//ADC外设时钟
	ADC_CLKInit.AdcClockSelection=RCC_ADCPCLK2_DIV6;			//分频因子6时钟为72M/6=12MHz
	HAL_RCCEx_PeriphCLKConfig(&ADC_CLKInit);					//设置ADC时钟
	
    ADC1_Handler.Instance=ADC1;
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //右对齐
    ADC1_Handler.Init.ScanConvMode=DISABLE;                      //非扫描模式
    ADC1_Handler.Init.ContinuousConvMode=DISABLE;                //关闭连续转换
    ADC1_Handler.Init.NbrOfConversion=1;                         //1个转换在规则序列中 也就是只转换规则序列1 
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;             //禁止不连续采样模式
    ADC1_Handler.Init.NbrOfDiscConversion=0;                     //不连续采样通道数为0
    ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //软件触发
    HAL_ADC_Init(&ADC1_Handler);                                 //初始化 
	
	HAL_ADCEx_Calibration_Start(&ADC1_Handler);					 //校准ADC
}

/**
  * @brief adc driver initialise, three channels,ch1\2\3, are set up
  * @param hadc: adc handle
  * @retval None
  * @note the function will be called by HAL_ADC_Init()
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC1_CLK_ENABLE();            //使能ADC1时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟
	
    GPIO_Initure.Pin=GPIO_PIN_1;            //PA1
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //模拟
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}

/**
  * @brief get the value of adc
  * @param ch: ADC_CHANNEL_x  (x: 0~16)
  * @retval adc value
  */
uint16_t Get_Adc(uint32_t ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;
    
    ADC1_ChanConf.Channel=ch;                                   //通道
    ADC1_ChanConf.Rank=1;                                       //第1个序列，序列1
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_239CYCLES_5;      //采样时间               
    HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC1_ChanConf);        //通道配置
	
    HAL_ADC_Start(&ADC1_Handler);                               //开启ADC
	
    HAL_ADC_PollForConversion(&ADC1_Handler,10);                //轮询转换
 
	return (u16)HAL_ADC_GetValue(&ADC1_Handler);	        	//返回最近一次ADC1规则组的转换结果
}


/**
  * @brief get the average of the adc
  * @param ch: ADC_CHANNEL_x  (x: 0~16)
  * @param timess: the times of getting adc
  * @retval the average of the adc
  */
uint16_t Get_Adc_Average(uint32_t ch,uint8_t times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_us(50);
	}
	return temp_val/times;
} 

/**
  * @brief Convert the value of the adc to the voltage value 
  * @param adcValue: the value of adc captured by MCU or other
  * @retval the voltage value
  */
float Change_Adc_Voltage(float adcValue)
{
    return adcValue*3.3/4096;
}

/**********************************END OF FILE*****************************************/
