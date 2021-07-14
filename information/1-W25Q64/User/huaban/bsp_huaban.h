#ifndef __HUABAN_H
#define __HUABAN_H

#include "stm32f10x.h"
#include "./font/fonts.h"
#include <stdio.h>

/******************************* 定义 ILI934 显示屏常用颜色 ********************************/
#define      BACKGROUND		                BLACK   //默认背景颜色

#define      WHITE		 		                 0xFFFF	   //白色
#define      BLACK                         0x0000	   //黑色 
#define      GREY                          0xF7DE	   //灰色 
#define      BLUE                          0x001F	   //蓝色 
#define      BLUE2                         0x051F	   //浅蓝色 
#define      RED                           0xF800	   //红色 
#define      MAGENTA                       0xF81F	   //红紫色，洋红色 
#define      GREEN                         0x07E0	   //绿色 
#define      CYAN                          0x7FFF	   //蓝绿色，青色 
#define      YELLOW                        0xFFE0	   //黄色 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF


//CS(NSS)引脚 片选选普通GPIO即可
#define      ILI9341_CS_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_CS_PORT                 GPIOC
#define      ILI9341_CS_PIN                  GPIO_Pin_4

//RD引脚 片选选普通GPIO即可
#define      ILI9341_RD_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_RD_PORT                 GPIOC
#define      ILI9341_RD_PIN                  GPIO_Pin_5

//WE引脚 片选选普通GPIO即可
#define      ILI9341_WE_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_WE_PORT                 GPIOC
#define      ILI9341_WE_PIN                  GPIO_Pin_6

//RS引脚 片选选普通GPIO即可
#define      ILI9341_RS_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_RS_PORT                 GPIOC
#define      ILI9341_RS_PIN                  GPIO_Pin_7

//BK引脚 片选选普通GPIO即可
#define      ILI9341_BK_CLK                  RCC_APB2Periph_GPIOD   
#define      ILI9341_BK_PORT                 GPIOD
#define      ILI9341_BK_PIN                  GPIO_Pin_2

//D0-D15引脚 片选选普通GPIO即可
#define      ILI9341_DATE_CLK                RCC_APB2Periph_GPIOB 
#define      ILI9341_DATE_PORT               GPIOB
#define      ILI9341_DATE_PIN                GPIO_Pin_All  


#define  		LCD_BK_ON()     						  GPIO_ResetBits( ILI9341_BK_PORT, ILI9341_BK_PIN )
#define  	  LCD_BK_OFF()      						GPIO_SetBits( ILI9341_BK_PORT, ILI9341_BK_PIN )

#define  		LCD_CS_HIGH()     						GPIO_SetBits( ILI9341_CS_PORT, ILI9341_CS_PIN )
#define  	  LCD_CS_LOW()      						GPIO_ResetBits( ILI9341_CS_PORT, ILI9341_CS_PIN )

#define  		LCD_RD_HIGH()     						GPIO_SetBits( ILI9341_RD_PORT, ILI9341_RD_PIN )
#define  	  LCD_RD_LOW()      						GPIO_ResetBits( ILI9341_RD_PORT, ILI9341_RD_PIN )

#define  		LCD_WE_HIGH()     						GPIO_SetBits( ILI9341_WE_PORT, ILI9341_WE_PIN )
#define  	  LCD_WE_LOW()      						GPIO_ResetBits( ILI9341_WE_PORT, ILI9341_WE_PIN )

#define  		LCD_RS_HIGH()     						GPIO_SetBits( ILI9341_RS_PORT, ILI9341_RS_PIN )
#define  	  LCD_RS_LOW()      						GPIO_ResetBits( ILI9341_RS_PORT, ILI9341_RS_PIN )

#define  		LCD_DATE_OUT(date)     			  ILI9341_DATE_PORT->ODR = date
#define  		LCD_DATE_IN()                 GPIO_ReadInputData( ILI9341_DATE_PORT  )

#define 	  ILI9341_LESS_PIXEL	  							240			//液晶屏较短方向的像素宽度
#define 	  ILI9341_MORE_PIXEL	 								320			//液晶屏较长方向的像素宽度

#define      CMD_SetCoordinateX		 		    0x2A	     //设置X坐标
#define      CMD_SetCoordinateY		 		    0x2B	     //设置Y坐标
#define      CMD_SetPixel		 		          0x2C	     //填充像素

#define      ILI9341_DispWindow_X_Star		    0     //起始点的X坐标
#define      ILI9341_DispWindow_Y_Star		    0     //起始点的Y坐标

/*SPI接口定义-结尾****************************/


void ILI9341_GPIO_Init(void);
uint16_t  ILI9341_Read_ID(void);
void ILI9341_Init(void);
void ILI9341_GramScan ( uint8_t ucOption );
void ILI9341_Open_Window(uint16_t x,uint16_t y,uint16_t width,uint16_t heigh);
void ILI9341_Draw_Rect(uint16_t x,uint16_t y,uint16_t width,uint16_t heigh);


void 	LCD_SetFont											(sFONT *fonts);
sFONT *LCD_GetFont											(void);
void 	LCD_ClearLine										(uint16_t Line);
void 	LCD_SetColors										(uint16_t TextColor, uint16_t BackColor);
void 	LCD_GetColors										(uint16_t *TextColor, uint16_t *BackColor);
void                     ILI9341_SetPointPixel           ( uint16_t usX, uint16_t usY );
uint16_t                 ILI9341_GetPointPixel           ( uint16_t usX , uint16_t usY );

//画线画圆
void ILI9341_DrawLine ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 );
void ILI9341_DrawCircle ( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled );

//点
void ILI9341_Draw_Point(uint16_t x,uint16_t y);

//屏幕
void ILI9341_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight);
static __inline void ILI9341_FillColor ( uint32_t ulAmout_Point, uint16_t usColor );

//颜色
void 	color_back								(uint16_t Color);
void 	color_type								(uint16_t Color);

//字符显示
void ILI9341_printf (  uint16_t line,  char * pStr );
void ILI9341_print ( 	uint16_t usX ,uint16_t usY,  char * pStr );
void LCD_ClearLine(uint16_t Line);

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/

#endif /* __HUABAN_H */

