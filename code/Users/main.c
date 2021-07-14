/**
  **************************************************************************************
  * @file main.c
  * @author shaokairu
  * @date 2021.7.8
  * @brief This file includes the main program body
  **************************************************************************************
  */

/* Includes --------------------------------------------------------------------------*/
#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "adc.h"
#include "key.h"
#include "exti.h"
#include "timer.h"
#include "lcd.h"
#include "plot.h"
#include "fitted.h"
#include "filter.h"

/* Exported variables ------------------------------------------------------------------*/
uint16_t Ladc1=0, Ladc2=0, Ladc3=0;
uint8_t penState = 0;   // 0 pen up, 1 pen down
double x, y;   // axis position

/**
  *@brief The application entry point.
  *@param None
  *@retval int
  */
int main(void)
{
    uint8_t i;
    /* MCU Configuration--------------------------------------------------------------*/
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Configure the system clock */
    Stm32_Clock_Init(RCC_PLL_MUL9);
    
    /* Initialize all configured peripherals */
    delay_init(72);
    uart_init(115200);
    LED_Init();
    KEY_Init();
    ADC1_Init();
    EXTI_Init();
    TIM3_Init(719, 199);
    LCD_Init();   
    
    /* Pragram begin configuration----------------------------------------------------*/
    /* Drawing Area Set*/
    POINT_COLOR = RED;
    LCD_Clear(BLUE);
    
    LCD_Fill( 0, 0, 239, 160, WHITE);
    
    LCD_DrawRectangle( 0, 0, 239, 160);     // plot border
    LCD_DrawRectangle( 1, 1, 238, 159); 
    LCD_DrawRectangle( 12, 8, 227, 152);    // drawing border
    LCD_DrawRectangle( 66, 44, 173, 116);   // high-accuracy border
    LCD_DrawLine( 0, 80, 239, 80);          // centre line
    LCD_DrawLine( 119, 0, 119, 160);
    
    /* Drawing Paramter List */
    BACK_COLOR = BLUE;
    LCD_ShowString( 42, 161,240, 24, 24, "Paramter List");
    
    POINT_COLOR = BROWN;
    LCD_DrawRectangle( 14, 185, 225, 315);  // border
    LCD_DrawRectangle( 15, 186, 224, 314);
    LCD_DrawRectangle( 16, 187, 223, 313);
    LCD_Fill( 17, 188, 222, 312, WHITE);    // background
    
    POINT_COLOR = BLACK;
    BACK_COLOR = WHITE;
    LCD_ShowString( 20, 190, 240, 16, 16, "ADC1: ");    // paramter location
    LCD_ShowString( 20, 206, 240, 16, 16, "ADC2: ");
    LCD_ShowString( 20, 222, 240, 16, 16, "ADC3: ");
    LCD_ShowString( 20, 238, 240, 16, 16, "x: ");
    LCD_ShowString( 70, 238, 240, 16, 16, "mm");
    LCD_ShowString( 20, 254, 240, 16, 16, "y: ");
    LCD_ShowString( 70, 254, 240, 16, 16, "mm");
    POINT_COLOR = MAGENTA;
    LCD_ShowString( 20, 270, 240, 16, 16, "pen up      ");
    POINT_COLOR = BLACK;
    
    // draw_point_graph( -7, 0,119, 80, CYAN);  // drawing point 
    
    /* Infinite loop */
    while(1)
    {
        LCD_ShowNum( 56, 190, Ladc1, 6, 16);  // paramter display
        LCD_ShowNum( 56, 206, Ladc2, 6, 16);
        LCD_ShowNum( 56, 222, Ladc3, 6, 16); 
        
        /* detemine whether the pen is down */
        POINT_COLOR = MAGENTA;
        if(Ladc3 > 695)
        {
            LCD_ShowString( 20, 270, 240, 16, 16, "pen down");
            penState = 1;
        }
        else
        {
            LCD_ShowString( 20, 270, 240, 16, 16, "pen up      ");
            penState = 0;
        }
        POINT_COLOR = BLACK;
        
        //printf("%d\r\n", Ladc1);
        
        if(penState == 1)
        {
            delay_ms(500);
            x = fitted_position_x(Ladc1 - Ladc3, Ladc2); 
            y = - fitted_position_y(Ladc1 - Ladc3, Ladc2);   // because 
            printf("%lf,%lf\r\n",x,y);
            if(x < 0)
            {
                LCD_ShowString( 35, 238, 240, 16, 16, "-");
                LCD_ShowNum( 40, 238, -x, 3, 16);
            }
            else
            {
                LCD_ShowString( 35, 238, 240, 16, 16, " ");
                LCD_ShowNum( 40, 238, x, 3, 16);
            }
            if( y< 0)
            {
                LCD_ShowString( 40, 254, 240, 16, 16, "-");
                LCD_ShowNum( 40, 254, -y, 3, 16); 
            }
            else
            {
                LCD_ShowString( 40, 254, 240, 16, 16, " ");
                LCD_ShowNum( 40, 254, y, 3, 16);
            }
            draw_point_graph( x, y, 119, 80, BLACK);
        }
    }
}

/**********************************END OF FILE*****************************************/
