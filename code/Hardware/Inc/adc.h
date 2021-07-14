/**
  **************************************************************************************
  * @file timer.c
  * @author shaokairu
  * @date 2021.7.8
  * @brief This file contains all the functions prototypes for adc library.
  **************************************************************************************
  */
  
/* Define to prevent recursive inclusion ---------------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes --------------------------------------------------------------------------*/
#include "sys.h"

/* Exported functions prototypes -----------------------------------------------------*/
void ADC1_Init(void); 
u16  Get_Adc(u32 ch);
u16 Get_Adc_Average(u32 ch,u8 times);
float Change_Adc_Voltage(float adcValue);

#endif 

/**********************************END OF FILE*****************************************/
