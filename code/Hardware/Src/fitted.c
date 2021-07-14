/**
  **************************************************************************************
  * @file fitted.c
  * @author shaokairu
  * @date 2021.7.10
  * @brief This file provides the fitted function
  **************************************************************************************
  */
  
/* Includes --------------------------------------------------------------------------*/
#include "fitted.h"
#include "math.h"

/* Private macro ---------------------------------------------------------------------*/
#define DIM 4

/* Private define --------------------------------------------------------------------*/
/* fitted function coefficient */
double py[DIM][DIM]={
                        {  1.760359099168356e+4,   -39.460913770597486,     0.029171985684019, -7.093508584157673e-6},
                        {    -54.85701903673827,      0.09159038173238, -3.831345502089454e-5,                     0},
                        {     0.031144401943405, -2.801513461694372e-5,                     0,                     0},
                        { -1.662851774514397e-6,                     0,                     0,                     0}
                    };  
double px[DIM][DIM]={
                        { 4.567859109016506e+3,  -12.070032428600754,     0.010447127582831, -2.931213502668813e-6},
                        {   -4.804017457787141,    0.009751051028361, -5.006132181913513e-6,                     0},
                        {   -0.005136964949169, 4.091042992890025e-6,                     0,                     0},
                        { 1.652366564557850e-6,                    0,                     0,                     0}
                    };


/**
  * @brief Linear model built by matlab
  * @param x,y the value of mcu sampling
  * @retval the location of x axis
  */
double fitted_position_x(uint16_t x, uint16_t y)
{
    uint8_t i, j;
    double z=0;
    
    for(i = 0; i < DIM; i ++)
    {
        for(j = 0; j < DIM; j ++)
        {
            if(px[i][j] != 0)
            {
                z += px[i][j] * pow( x, i) * pow( y, j);
            }
        }
    }
    
    return z;
}

/**
  * @brief Linear model built by matlab
  * @param x,y the value of mcu sampling
  * @retval the location of y axis
  */
double fitted_position_y(uint16_t x, uint16_t y)
{
    uint8_t i, j;
    double z=0;
    
    for(i = 0; i < DIM; i ++)
    {
        for(j = 0; j < DIM; j ++)
        {
            if(py[i][j] != 0)
            {
                z += py[i][j] * pow( x, i) * pow( y, j);
            }
        }
    }
    
    return z;
}

/**********************************END OF FILE*****************************************/
