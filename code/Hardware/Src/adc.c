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
ADC_HandleTypeDef ADC1_Handler;		//ADC���

/**
  * @brief adc1 initialise
  * @param None
  * @retval None
  */
void ADC1_Init(void)
{ 
	RCC_PeriphCLKInitTypeDef ADC_CLKInit;
	
	ADC_CLKInit.PeriphClockSelection=RCC_PERIPHCLK_ADC;			//ADC����ʱ��
	ADC_CLKInit.AdcClockSelection=RCC_ADCPCLK2_DIV6;			//��Ƶ����6ʱ��Ϊ72M/6=12MHz
	HAL_RCCEx_PeriphCLKConfig(&ADC_CLKInit);					//����ADCʱ��
	
    ADC1_Handler.Instance=ADC1;
    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //�Ҷ���
    ADC1_Handler.Init.ScanConvMode=DISABLE;                      //��ɨ��ģʽ
    ADC1_Handler.Init.ContinuousConvMode=DISABLE;                //�ر�����ת��
    ADC1_Handler.Init.NbrOfConversion=1;                         //1��ת���ڹ��������� Ҳ����ֻת����������1 
    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;             //��ֹ����������ģʽ
    ADC1_Handler.Init.NbrOfDiscConversion=0;                     //����������ͨ����Ϊ0
    ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //�������
    HAL_ADC_Init(&ADC1_Handler);                                 //��ʼ�� 
	
	HAL_ADCEx_Calibration_Start(&ADC1_Handler);					 //У׼ADC
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
    __HAL_RCC_ADC1_CLK_ENABLE();            //ʹ��ADC1ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_1;            //PA1
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
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
    
    ADC1_ChanConf.Channel=ch;                                   //ͨ��
    ADC1_ChanConf.Rank=1;                                       //��1�����У�����1
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_239CYCLES_5;      //����ʱ��               
    HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC1_ChanConf);        //ͨ������
	
    HAL_ADC_Start(&ADC1_Handler);                               //����ADC
	
    HAL_ADC_PollForConversion(&ADC1_Handler,10);                //��ѯת��
 
	return (u16)HAL_ADC_GetValue(&ADC1_Handler);	        	//�������һ��ADC1�������ת�����
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
