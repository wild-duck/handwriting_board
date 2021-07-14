/**
  **************************************************************************************
  * @file filter.c
  * @author shaokairu
  * @date 2021.7.11
  * @brief This file provides the filter function
  **************************************************************************************
  */
  
/* Includes --------------------------------------------------------------------------*/
#include "filter.h"

/* Private marco ---------------------------------------------------------------------*/
#define A 0.05   // the coefficient of LPF

/**
  * @brief sort the array in order by using selection sort and only for uint16_t type
  * @param data: the array would be sort
  * @param n: the length of the array, data
  * @param mode: 0 ascending sort
  *              1 descending sort
  * @retval None
  */
void selection_sort(uint16_t data[], uint16_t n, uint16_t mode)
{
    uint16_t i,j,k,t;
    for(i = 0; i < n - 1; i ++)
    {
        k = i;
        for(j = i + 1; j < n; j ++)
        {
            if(mode == 1)   // descending
            {
                if(data[k] < data[j])
                {
                    k = j;
                }
            }
            else if(mode == 0)  // ascending
            {
                if(data[k] > data[j])
                {
                    k = j;
                }
            }
        }
        if(k != i)
        {
            t = data[i];
            data[i] = data[k];
            data[k] = t;
        }
    }
}

/**
  * @brief median filtering function, only for uint16_t type
  * @param data: the array of the data which need to be manipulated
  * @param n: the length of the array
  * @retval processed data
  */
uint16_t median_filtering(uint16_t data[], uint16_t n)
{
    selection_sort( data, n, 1);
    
    return data[(n + 1)/2];
}

/**
  * @brief one order low pass filter
  * @param data: the array of the data which need to be manipulated
  * @param lastdata: the data of last time
  * @retval processed data
  */
uint16_t low_pass_filtering(uint16_t data, uint16_t* lastData)
{
    float nextData;
    
    nextData = data * A + (1 - A) * (*lastData);
    
    *lastData = nextData;
    
    return nextData;
}



/**********************************END OF FILE*****************************************/
