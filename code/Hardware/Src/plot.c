/*
 ***************************************************************************************
 * @file plot.c
 * @author shaokairu
 * @date 2021.5.29
 * @brief This file provides all the functions of drawing plot library, and this file 
 *        must used with file "lcd.c".
 ***************************************************************************************
 * @version 2021.7.8 加入了绘制"回"形图表的函数，为手写板设计
 ***************************************************************************************
 */
 
/* Includes --------------------------------------------------------------------------*/
#include "lcd.h"
#include "plot.h"

/**
  *@brief 创建坐标系图表
  *@param x0,y0 图表区域的左上角顶点坐标
  *@param x1,y1 图表区域的右下角顶点坐标
  *@param title 图表的表头
  *@retval None
  */
void chart_plot(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t* title)
{
    uint8_t i=0;
    
    POINT_COLOR = RED;
    LCD_DrawRectangle(x0, y0, x1, y1);
    while (*(title + i) != 0)
    {
        i++;
    }
    i--;
    LCD_ShowString((x1-x0-i*8)/2, y1+1, 240, 16, 16, title);
    
    // 建立坐标系
    POINT_COLOR = BLACK;
    LCD_DrawLine(x0 + 20, y1 - 20, x1 - 10, y1 - 20);   // x轴
    LCD_DrawLine(x1 - 10, y1 - 20, x1 - 13, y1 - 17);   // x轴箭头
    LCD_DrawLine(x1 - 10, y1 - 20, x1 - 13, y1 - 23);
    LCD_DrawLine(x0 + 20, y1 - 20, x0 + 20, y0 + 20);   // y轴
    LCD_DrawLine(x0 + 20, y0 + 20, x0 + 17, y0 + 23);   // y轴箭头
    LCD_DrawLine(x0 + 20, y0 + 20, x0 + 23, y0 + 23);
    
    // 刻度
    LCD_ShowString(x0 + 10, y1 - 18, 240, 16, 16, "O");
}

/**
  * @brief 将缓存数组的值显示在图表上
  * @param x0，y0: 原点在屏幕上的位置
  * @retval None
  */
void curve_graph(uint16_t x0, uint16_t y0, uint32_t point[][2], uint16_t num)
{
    uint16_t i, px0, py0, px1, py1;
    
    POINT_COLOR = BLUE;
    for (i = 0; i < num-1; i++)
    {
        px0 = x0 + point[i][0];
        py0 = y0 - point[i][1] * 3;
        px1 = x0 + point[i + 1][0];
        py1 = y0 - point[i + 1][1] * 3;
        LCD_DrawLine(px0, py0, px1, py1);
    }
}

/**
  * @brief displaying area for hand-writing board
  * @param None
  * @retval None
  */
void hui_graph(void)
{
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
}

void draw_point_graph(int px, int py,uint16_t cx, uint16_t cy, uint32_t pointColor)
{
    uint16_t x, y,i, j;
    
    x = px + cx;
    y = py + cy;
    
    if(x <= 227 && x>= 12 && y >= 8 && y <= 152)    // pen limit
    {
        POINT_COLOR = pointColor;
        for(i = x - 1; i <= x + 1; i ++)
        {
            for(j = y - 1; j <= y + 1; j ++)
            {
                LCD_DrawPoint( i, j);
            }
        }
        POINT_COLOR = BLACK;
    }
    else
    {
        printf("pen out\r\n");
    }
}

/********************************* END OF FILE ****************************************/
