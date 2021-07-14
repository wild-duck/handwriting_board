#ifndef __HUABAN_H
#define __HUABAN_H

#include "stm32f10x.h"
#include "./font/fonts.h"
#include <stdio.h>

/******************************* ���� ILI934 ��ʾ��������ɫ ********************************/
#define      BACKGROUND		                BLACK   //Ĭ�ϱ�����ɫ

#define      WHITE		 		                 0xFFFF	   //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF


//CS(NSS)���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_CS_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_CS_PORT                 GPIOC
#define      ILI9341_CS_PIN                  GPIO_Pin_4

//RD���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_RD_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_RD_PORT                 GPIOC
#define      ILI9341_RD_PIN                  GPIO_Pin_5

//WE���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_WE_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_WE_PORT                 GPIOC
#define      ILI9341_WE_PIN                  GPIO_Pin_6

//RS���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_RS_CLK                  RCC_APB2Periph_GPIOC   
#define      ILI9341_RS_PORT                 GPIOC
#define      ILI9341_RS_PIN                  GPIO_Pin_7

//BK���� Ƭѡѡ��ͨGPIO����
#define      ILI9341_BK_CLK                  RCC_APB2Periph_GPIOD   
#define      ILI9341_BK_PORT                 GPIOD
#define      ILI9341_BK_PIN                  GPIO_Pin_2

//D0-D15���� Ƭѡѡ��ͨGPIO����
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

#define 	  ILI9341_LESS_PIXEL	  							240			//Һ�����϶̷�������ؿ��
#define 	  ILI9341_MORE_PIXEL	 								320			//Һ�����ϳ���������ؿ��

#define      CMD_SetCoordinateX		 		    0x2A	     //����X����
#define      CMD_SetCoordinateY		 		    0x2B	     //����Y����
#define      CMD_SetPixel		 		          0x2C	     //�������

#define      ILI9341_DispWindow_X_Star		    0     //��ʼ���X����
#define      ILI9341_DispWindow_Y_Star		    0     //��ʼ���Y����

/*SPI�ӿڶ���-��β****************************/


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

//���߻�Բ
void ILI9341_DrawLine ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 );
void ILI9341_DrawCircle ( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled );

//��
void ILI9341_Draw_Point(uint16_t x,uint16_t y);

//��Ļ
void ILI9341_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight);
static __inline void ILI9341_FillColor ( uint32_t ulAmout_Point, uint16_t usColor );

//��ɫ
void 	color_back								(uint16_t Color);
void 	color_type								(uint16_t Color);

//�ַ���ʾ
void ILI9341_printf (  uint16_t line,  char * pStr );
void ILI9341_print ( 	uint16_t usX ,uint16_t usY,  char * pStr );
void LCD_ClearLine(uint16_t Line);

/*�ȴ���ʱʱ��*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*��Ϣ���*/

#endif /* __HUABAN_H */

