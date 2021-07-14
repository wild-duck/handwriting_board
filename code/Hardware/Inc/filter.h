/**
  **************************************************************************************
  * @file filter.h
  * @author shaokairu
  * @date 2021.7.11
  * @brief This file contains all the functions prototypes for filter. 
  **************************************************************************************
  */
  
/* Define to prevent recursive inclusion ---------------------------------------------*/
#ifndef _FILTER_H
#define _FILTER_H

/* Includes --------------------------------------------------------------------------*/
#include "sys.h"

/* Exported functions prototypes -----------------------------------------------------*/
void selection_sort(uint16_t data[], uint16_t n, uint16_t mode);
uint16_t median_filtering(uint16_t data[], uint16_t n);
uint16_t low_pass_filtering(uint16_t data, uint16_t* lastData);

#endif

/**********************************END OF FILE*****************************************/

