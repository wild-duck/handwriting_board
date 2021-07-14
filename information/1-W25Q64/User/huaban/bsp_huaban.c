 /**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   spi flash �ײ�Ӧ�ú���bsp 
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./huaban/bsp_huaban.h"
#include "./font/fonts.h"


//����Һ��ɨ�跽����仯��XY���ؿ��
//����ILI9341_GramScan�������÷���ʱ���Զ�����
uint16_t LCD_X_LENGTH = ILI9341_LESS_PIXEL;
uint16_t LCD_Y_LENGTH = ILI9341_MORE_PIXEL;

//Һ����ɨ��ģʽ����������Ҫ���ڷ���ѡ�������ļ������
//������ѡֵΪ0-7
//����ILI9341_GramScan�������÷���ʱ���Զ�����
//LCD�ճ�ʼ�����ʱ��ʹ�ñ�Ĭ��ֵ
uint8_t LCD_SCAN_MODE = 6;

static sFONT *LCD_Currentfonts = &Font8x16;  //Ӣ������
static uint16_t color1 = WHITE;
static uint16_t color2 = BLACK;


#define      CMD_SetCoordinateX		 		    0x2A	     //����X����
#define      CMD_SetCoordinateY		 		    0x2B	     //����Y����
#define      CMD_SetPixel		 		          0x2C	     //�������

/**
  * @brief  ����LCD�ı�����ɫ,RGB565
  * @param  Color: ָ��������ɫ 
  * @retval None
  */
void color_back(uint16_t color)
{
	color1=color;
}

/**
  * @brief  ����LCD��ǰ��(����)��ɫ,RGB565
  * @param  Color: ָ��ǰ��(����)��ɫ 
  * @retval None
  */
void color_type(uint16_t Color)
{
  color2 = Color;
}

/*��ʱ*/
static void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*
1 .��ʼ��l293D
*/
void ILI9341_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
  //pb3pb4 ������ͨ
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	/* ʹ��SPI������ص�ʱ�� */
 	RCC_APB2PeriphClockCmd ( ILI9341_CS_CLK | ILI9341_RD_CLK | ILI9341_BK_CLK|
													 ILI9341_WE_CLK | ILI9341_RS_CLK | ILI9341_DATE_CLK, ENABLE );
	
  /* ����SPI�� CS���ţ���ͨIO���� */
  GPIO_InitStructure.GPIO_Pin = ILI9341_CS_PIN  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(ILI9341_CS_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = ILI9341_RD_PIN  ;
  GPIO_Init(ILI9341_RD_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_WE_PIN  ;
  GPIO_Init(ILI9341_WE_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_RS_PIN  ;
  GPIO_Init(ILI9341_RS_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_BK_PIN  ;
  GPIO_Init(ILI9341_BK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATE_PIN  ;
  GPIO_Init(ILI9341_DATE_PORT, &GPIO_InitStructure);

  LCD_BK_ON(); 	
}
//д����
void ILI9341_Write_CMD(uint16_t cmd)
{	
	LCD_CS_LOW();
	LCD_RS_LOW();
	LCD_RD_HIGH();

	
	LCD_DATE_OUT(cmd);

	
	LCD_WE_LOW();
	LCD_WE_HIGH();
	LCD_CS_HIGH() ;
}
//д����
void ILI9341_Write_Date (uint16_t date)
{	
	LCD_CS_LOW();
	LCD_RS_HIGH();
	LCD_RD_HIGH();

	
	
	LCD_DATE_OUT(date);

	
	
	LCD_WE_LOW();
	LCD_WE_HIGH();
	LCD_CS_HIGH() ;
}
//������
uint16_t ILI9341_Read_Date (void)
{	
	uint16_t  date;
	
	/*����ģʽ*/
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATE_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(ILI9341_DATE_PORT, &GPIO_InitStructure);
	

	LCD_CS_LOW();
	LCD_RS_HIGH();
	LCD_WE_HIGH();
	LCD_RD_LOW();
	
	date=LCD_DATE_IN();

	
	LCD_RD_HIGH();

	
	LCD_CS_HIGH();

	
	 /* �л���� */
  GPIO_InitStructure.GPIO_Pin = ILI9341_DATE_PIN  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(ILI9341_DATE_PORT, &GPIO_InitStructure);
		
	return date;	
}	

uint16_t  ILI9341_Read_ID(void)
{
	uint16_t temp = 0;
	
	ILI9341_Write_CMD(0xD3);
	
	ILI9341_Read_Date();
	ILI9341_Read_Date();
	
	temp = ILI9341_Read_Date();
	temp  <<= 8;
	temp |= ILI9341_Read_Date();
	
	return temp;
}

/**
  * @brief  ��ʼ��ILI9341��IO����
  * @param  ��
  * @retval ��
  */
 void ILI9341_GPIO_Config ( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;

		/* ʹ�ܸ���IOʱ��*/
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_AFIO, ENABLE );
	
	//��λ����ֱ��ʹ��NRST�������帴λ��ʱ���ʹҺ����λ

	/* ʹ��FSMC��Ӧ��Ӧ�ܽ�ʱ��*/
	RCC_APB2PeriphClockCmd ( 	
													/*�����ź�*/
													ILI9341_CS_CLK|ILI9341_RS_CLK|ILI9341_WE_CLK|
													ILI9341_RD_CLK	|ILI9341_BK_CLK|
													/*�����ź�*/
													ILI9341_DATE_CLK, ENABLE );
	
	//����SWD��ʧ��JTAG (����PB����������jtag�ӿڣ��ĳ�SWD�ӿھͲ����и���)
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
		
	
	/* ����Һ�����Ӧ��������,PORT-D0~D15 */	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_DATE_PIN;
	GPIO_Init ( ILI9341_DATE_PORT, &GPIO_InitStructure );	
		
	/* ����Һ�����Ӧ�Ŀ�����
	 * ��   			:LCD-RD
	 * д   			:LCD-WR
	 * Ƭѡ   		:LCD-CS
	 * ����/���� 	:LCD-DC
	 */
	GPIO_InitStructure.GPIO_Pin = ILI9341_RD_PIN; 
	GPIO_Init (ILI9341_RD_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_WE_PIN; 
	GPIO_Init (ILI9341_WE_PORT, & GPIO_InitStructure );
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_CS_PIN; 
	GPIO_Init ( ILI9341_CS_PORT, & GPIO_InitStructure );  
	
	GPIO_InitStructure.GPIO_Pin = ILI9341_RS_PIN; 
	GPIO_Init ( ILI9341_RS_PORT, & GPIO_InitStructure );
			
	/* ����LCD������ƹܽ�BK*/	
	GPIO_InitStructure.GPIO_Pin = ILI9341_BK_PIN; 
	GPIO_Init ( ILI9341_BK_PORT, &GPIO_InitStructure );
}


/**
 * @brief  ��ʼ��ILI9341�Ĵ���
 * @param  ��
 * @retval ��
 */
void ILI9341_REG_Config ( void )
{	
	/*  Power control B (CFh)  */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xCF  );
	ILI9341_Write_Date ( 0x00  );
	ILI9341_Write_Date ( 0x81  );
	ILI9341_Write_Date ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xED );
	ILI9341_Write_Date ( 0x64 );
	ILI9341_Write_Date ( 0x03 );
	ILI9341_Write_Date ( 0x12 );
	ILI9341_Write_Date ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xE8 );
	ILI9341_Write_Date( 0x85 );
	ILI9341_Write_Date( 0x10 );
	ILI9341_Write_Date( 0x78 );
	
	/*  Power control A (CBh) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xCB );
	ILI9341_Write_Date( 0x39 );
	ILI9341_Write_Date( 0x2C );
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x34 );
	ILI9341_Write_Date( 0x02 );
	
	/* Pump ratio control (F7h) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xF7 );
	ILI9341_Write_Date( 0x20 );
	
	/* Driver timing control B */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xEA );
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xB1 );
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x1B );
	
	/*  Display Function Control (B6h) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xB6 );
	ILI9341_Write_Date( 0x0A );
	ILI9341_Write_Date( 0xA2 );
	
	/* Power Control 1 (C0h) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xC0 );
	ILI9341_Write_Date( 0x35 );
	
	/* Power Control 2 (C1h) */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0xC1 );
	ILI9341_Write_Date( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	ILI9341_Write_CMD( 0xC5 );
	ILI9341_Write_Date( 0x45 );
	ILI9341_Write_Date( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	ILI9341_Write_CMD( 0xC7 );
	ILI9341_Write_Date( 0xA2 );
	
	/* Enable 3G (F2h) */
	ILI9341_Write_CMD( 0xF2 );
	ILI9341_Write_Date( 0x00 );
	
	/* Gamma Set (26h) */
	ILI9341_Write_CMD( 0x26 );
	ILI9341_Write_Date( 0x01 );
	Delay(0xFFFF);
	
	/* Positive Gamma Correction */
	ILI9341_Write_CMD( 0xE0 ); //Set Gamma
	ILI9341_Write_Date( 0x0F );
	ILI9341_Write_Date( 0x26 );
	ILI9341_Write_Date( 0x24 );
	ILI9341_Write_Date( 0x0B );
	ILI9341_Write_Date( 0x0E );
	ILI9341_Write_Date( 0x09 );
	ILI9341_Write_Date( 0x54 );
	ILI9341_Write_Date( 0xA8 );
	ILI9341_Write_Date( 0x46 );
	ILI9341_Write_Date( 0x0C );
	ILI9341_Write_Date( 0x17 );
	ILI9341_Write_Date( 0x09 );
	ILI9341_Write_Date( 0x0F );
	ILI9341_Write_Date( 0x07 );
	ILI9341_Write_Date( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	ILI9341_Write_CMD( 0XE1 ); //Set Gamma
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x19 );
	ILI9341_Write_Date( 0x1B );
	ILI9341_Write_Date( 0x04 );
	ILI9341_Write_Date( 0x10 );
	ILI9341_Write_Date( 0x07 );
	ILI9341_Write_Date( 0x2A );
	ILI9341_Write_Date( 0x47 );
	ILI9341_Write_Date( 0x39 );
	ILI9341_Write_Date( 0x03 );
	ILI9341_Write_Date( 0x06 );
	ILI9341_Write_Date( 0x06 );
	ILI9341_Write_Date( 0x30 );
	ILI9341_Write_Date( 0x38 );
	ILI9341_Write_Date( 0x0F );
	
	/* memory access control set */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0x36 ); 	
	ILI9341_Write_Date( 0xC8 );    /*����  ���Ͻǵ� (���)�����½� (�յ�)ɨ�跽ʽ*/
	Delay(0xFFFF);
	
	/* column address control set */
	ILI9341_Write_CMD( CMD_SetCoordinateX ); 
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0xEF );
	
	/* page address control set */
	Delay(0xFFFF);
	ILI9341_Write_CMD( CMD_SetCoordinateY ); 
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x00 );
	ILI9341_Write_Date( 0x01 );
	ILI9341_Write_Date( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	Delay(0xFFFF);
	ILI9341_Write_CMD( 0x3a ); 
	ILI9341_Write_Date( 0x55 );
	
	/* Sleep Out (11h)  */
	ILI9341_Write_CMD( 0x11 );	
	Delay(0xAFFf<<2 );
	Delay(0xFFFF);
	
	/* Display ON (29h) */
	ILI9341_Write_CMD( 0x29 ); 
		
}


/**
 * @brief  ����ILI9341��GRAM��ɨ�跽�� 
 * @param  ucOption ��ѡ��GRAM��ɨ�跽�� 
 *     @arg 0-7 :������ѡֵΪ0-7��˸�����
 *
 *	����������0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
 *				���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
 *		
 *	����0��2��4��6 ģʽ��X��������Ϊ240��Y��������Ϊ320
 *	����1��3��5��7 ģʽ��X��������Ϊ320��Y��������Ϊ240
 *
 *	���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����
 *	���� 3 ģʽΪ����ͷ����ʹ�õķ���
 *	���� 0 ģʽΪBMPͼƬ��ʾ����ʹ�õķ���
 *
 * @retval ��
 * @note  ����ͼ����A��ʾ���ϣ�V��ʾ���£�<��ʾ����>��ʾ����
					X��ʾX�ᣬY��ʾY��

------------------------------------------------------------
ģʽ0��				.		ģʽ1��		.	ģʽ2��			.	ģʽ3��					
					A		.					A		.		A					.		A									
					|		.					|		.		|					.		|							
					Y		.					X		.		Y					.		X					
					0		.					1		.		2					.		3					
	<--- X0 o		.	<----Y1	o		.		o 2X--->  .		o 3Y--->	
------------------------------------------------------------	
ģʽ4��				.	ģʽ5��			.	ģʽ6��			.	ģʽ7��					
	<--- X4 o		.	<--- Y5 o		.		o 6X--->  .		o 7Y--->	
					4		.					5		.		6					.		7	
					Y		.					X		.		Y					.		X						
					|		.					|		.		|					.		|							
					V		.					V		.		V					.		V		
---------------------------------------------------------				
											 LCD��ʾ��
								|-----------------|
								|			Ұ��Logo		|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|-----------------|
								��Ļ���棨��240����320��

 *******************************************************/
void ILI9341_GramScan ( uint8_t ucOption )
{	
	//������飬ֻ������0-7
	if(ucOption >7 )
		return;
	
	//����ģʽ����LCD_SCAN_MODE��ֵ����Ҫ���ڴ�����ѡ��������
	LCD_SCAN_MODE = ucOption;
	
	//����ģʽ����XY��������ؿ��
	if(ucOption%2 == 0)	
	{
		//0 2 4 6ģʽ��X�������ؿ��Ϊ240��Y����Ϊ320
		LCD_X_LENGTH = ILI9341_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9341_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7ģʽ��X�������ؿ��Ϊ320��Y����Ϊ240
		LCD_X_LENGTH = ILI9341_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9341_LESS_PIXEL; 
	}

	//0x36��������ĸ�3λ����������GRAMɨ�跽��	
	ILI9341_Write_CMD ( 0x36 ); 
	ILI9341_Write_Date ( 0x08 |(ucOption<<5));//����ucOption��ֵ����LCD��������0-7��ģʽ
	ILI9341_Write_CMD ( CMD_SetCoordinateX ); 
	ILI9341_Write_Date ( 0x00 );		/* x ��ʼ�����8λ */
	ILI9341_Write_Date ( 0x00 );		/* x ��ʼ�����8λ */
	ILI9341_Write_Date ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x ���������8λ */	
	ILI9341_Write_Date ( (LCD_X_LENGTH-1)&0xFF );				/* x ���������8λ */

	ILI9341_Write_CMD ( CMD_SetCoordinateY ); 
	ILI9341_Write_Date ( 0x00 );		/* y ��ʼ�����8λ */
	ILI9341_Write_Date ( 0x00 );		/* y ��ʼ�����8λ */
	ILI9341_Write_Date ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y ���������8λ */	 
	ILI9341_Write_Date ( (LCD_Y_LENGTH-1)&0xFF );				/* y ���������8λ */

	/* write gram start */
	ILI9341_Write_CMD ( CMD_SetPixel );	
}

void ILI9341_Init(void)
{
	ILI9341_GPIO_Init();
	ILI9341_REG_Config();
	ILI9341_GramScan (6);
	ILI9341_Draw_Rect(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
}

void ILI9341_Open_Window(uint16_t x,uint16_t y,uint16_t width,uint16_t heigh)
{
	ILI9341_Write_CMD(CMD_SetCoordinateX);
	ILI9341_Write_Date((x&0xFF00) >> 8);
	ILI9341_Write_Date((x&0xFF));
	ILI9341_Write_Date(((x+width-1)&0xFF00) >> 8);
	ILI9341_Write_Date(((x+width-1)&0xFF));
	
	ILI9341_Write_CMD(CMD_SetCoordinateY);
	ILI9341_Write_Date((y&0xFF00) >> 8);
	ILI9341_Write_Date((y&0xFF));
	ILI9341_Write_Date(((y+heigh-1)&0xFF00) >> 8);
	ILI9341_Write_Date(((y+heigh-1)&0xFF));
}


void ILI9341_Draw_Rect(uint16_t x,uint16_t y,uint16_t width,uint16_t heigh)
{
	uint32_t i;
	
	ILI9341_Open_Window(x,y,width,heigh);
	ILI9341_Write_CMD(CMD_SetPixel);
	for(i=0;i<width*heigh;i++)
	{
		ILI9341_Write_Date(color1);
	}
}

void ILI9341_Draw_Point(uint16_t x,uint16_t y)
{
	ILI9341_Open_Window(x,y,1,1);
	ILI9341_Write_CMD(CMD_SetPixel);
	ILI9341_Write_Date(color2);
	
}

/**
 * @brief  �� ILI9341 ��ʾ����ʹ�� Bresenham �㷨��Բ
 * @param  usX_Center �����ض�ɨ�跽����Բ�ĵ�X����
 * @param  usY_Center �����ض�ɨ�跽����Բ�ĵ�Y����
 * @param  usRadius��Բ�İ뾶����λ�����أ�
 * @param  ucFilled ��ѡ���Ƿ�����Բ
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg 0 :����Բ
  *     @arg 1 :ʵ��Բ
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_DrawCircle ( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled )
{
	int16_t sCurrentX, sCurrentY;
	int16_t sError;
	
	
	sCurrentX = 0; sCurrentY = usRadius;	  
	
	sError = 3 - ( usRadius << 1 );     //�ж��¸���λ�õı�־
	
	
	while ( sCurrentX <= sCurrentY )
	{
		int16_t sCountY;
		
		
		if ( ucFilled ) 			
			for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ ) 
			{                      
				ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCountY );           //1���о����� 
				ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCountY );           //2       
				ILI9341_SetPointPixel ( usX_Center - sCountY,   usY_Center + sCurrentX );           //3
				ILI9341_SetPointPixel ( usX_Center - sCountY,   usY_Center - sCurrentX );           //4
				ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCountY );           //5    
        ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCountY );           //6
				ILI9341_SetPointPixel ( usX_Center + sCountY,   usY_Center - sCurrentX );           //7 	
        ILI9341_SetPointPixel ( usX_Center + sCountY,   usY_Center + sCurrentX );           //0				
			}
		
		else
		{          
			ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCurrentY );             //1���о�����
			ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCurrentY );             //2      
			ILI9341_SetPointPixel ( usX_Center - sCurrentY, usY_Center + sCurrentX );             //3
			ILI9341_SetPointPixel ( usX_Center - sCurrentY, usY_Center - sCurrentX );             //4
			ILI9341_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCurrentY );             //5       
			ILI9341_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCurrentY );             //6
			ILI9341_SetPointPixel ( usX_Center + sCurrentY, usY_Center - sCurrentX );             //7 
			ILI9341_SetPointPixel ( usX_Center + sCurrentY, usY_Center + sCurrentX );             //0
    }			
		
		
		sCurrentX ++;

		
		if ( sError < 0 ) 
			sError += 4 * sCurrentX + 6;	  
		
		else
		{
			sError += 10 + 4 * ( sCurrentX - sCurrentY );   
			sCurrentY --;
		} 			
	}	
}


/**
 * @brief  �趨ILI9341�Ĺ������
 * @param  usX �����ض�ɨ�跽���¹���X����
 * @param  usY �����ض�ɨ�跽���¹���Y����
 * @retval ��
 */
static void ILI9341_SetCursor ( uint16_t usX, uint16_t usY )	
{
	ILI9341_Open_Window ( usX, usY, 1, 1 );
}


/**
 * @brief  ��ILI9341��ʾ������ĳһ��ɫ������ص�
 * @param  ulAmout_Point ��Ҫ�����ɫ�����ص������Ŀ
 * @param  usColor ����ɫ
 * @retval ��
 */
static __inline void ILI9341_FillColor ( uint32_t ulAmout_Point, uint16_t usColor )
{
	uint32_t i = 0;
	
	
	/* memory write */
	ILI9341_Write_CMD ( CMD_SetPixel );	
		
	for ( i = 0; i < ulAmout_Point; i ++ )
		ILI9341_Write_Date ( usColor );
		
	
}


/**
 * @brief  ��ILI9341��ʾ����ĳһ������ĳ����ɫ��������
 * @param  usX �����ض�ɨ�跽���´��ڵ����X����
 * @param  usY �����ض�ɨ�跽���´��ڵ����Y����
 * @param  usWidth �����ڵĿ��
 * @param  usHeight �����ڵĸ߶�
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight )
{
	ILI9341_Open_Window ( usX, usY, usWidth, usHeight );
	ILI9341_FillColor ( usWidth * usHeight, color1 );		
	
}


/**
 * @brief  ��ILI9341��ʾ����ĳһ����ĳ����ɫ�������
 * @param  usX �����ض�ɨ�跽���¸õ��X����
 * @param  usY �����ض�ɨ�跽���¸õ��Y����
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_SetPointPixel ( uint16_t usX, uint16_t usY )	
{	
	if ( ( usX < LCD_X_LENGTH ) && ( usY < LCD_Y_LENGTH ) )
  {
		ILI9341_SetCursor ( usX, usY );
		
		ILI9341_FillColor ( 1, color2 );
	}
	
}


/**
 * @brief  ��ȡILI9341 GRAN ��һ����������
 * @param  ��
 * @retval ��������
 */
static uint16_t ILI9341_Read_PixelDate ( void )	
{	
	uint16_t usR=0, usG=0, usB=0 ;

	
	ILI9341_Write_CMD ( 0x2E );   /* ������ */
	
	usR = ILI9341_Read_Date (); 	/*FIRST READ OUT DUMMY Date*/
	
	usR = ILI9341_Read_Date ();  	/*READ OUT RED Date  */
	usB = ILI9341_Read_Date ();  	/*READ OUT BLUE Date*/
	usG = ILI9341_Read_Date ();  	/*READ OUT GREEN Date*/	
	
  return ( ( ( usR >> 11 ) << 11 ) | ( ( usG >> 10 ) << 5 ) | ( usB >> 11 ) );
	
}


/**
 * @brief  ��ȡ ILI9341 ��ʾ����ĳһ����������������
 * @param  usX �����ض�ɨ�跽���¸õ��X����
 * @param  usY �����ض�ɨ�跽���¸õ��Y����
 * @retval ��������
 */
uint16_t ILI9341_GetPointPixel ( uint16_t usX, uint16_t usY )
{ 
	uint16_t usPixelDate;

	
	ILI9341_SetCursor ( usX, usY );
	
	usPixelDate = ILI9341_Read_PixelDate ();
	
	return usPixelDate;
	
}


/**
 * @brief  �� ILI9341 ��ʾ������ʾһ��Ӣ���ַ�
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽���¸õ����ʼY����
 * @param  cChar ��Ҫ��ʾ��Ӣ���ַ�
 * @note ��ʹ��LCD_SetBackColor��LCD_type��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_prin( uint16_t usX, uint16_t usY, const char cChar )
{
	uint8_t  byteCount, bitCount,fontLength;	
	uint16_t ucRelativePositon;
	uint8_t *Pfont;
	
	//��ascii���ƫ�ƣ���ģ������ASCII���ǰ32����ͼ�η��ţ�
	ucRelativePositon = cChar - ' ';
	
	//ÿ����ģ���ֽ���
	fontLength = (LCD_Currentfonts->Width*LCD_Currentfonts->Height)/8;
		
	//��ģ�׵�ַ
	/*ascii���ƫ��ֵ����ÿ����ģ���ֽ����������ģ��ƫ��λ��*/
	Pfont = (uint8_t *)&LCD_Currentfonts->table[ucRelativePositon * fontLength];
	
	//������ʾ����
	ILI9341_Open_Window ( usX, usY, LCD_Currentfonts->Width, LCD_Currentfonts->Height);
	
	ILI9341_Write_CMD ( CMD_SetPixel );			

	//���ֽڶ�ȡ��ģ����
	//����ǰ��ֱ����������ʾ���ڣ���ʾ���ݻ��Զ�����
	for ( byteCount = 0; byteCount < fontLength; byteCount++ )
	{
			//һλһλ����Ҫ��ʾ����ɫ
			for ( bitCount = 0; bitCount < 8; bitCount++ )
			{
					if ( Pfont[byteCount] & (0x80>>bitCount) )
						ILI9341_Write_Date ( color2 );			
					else
						ILI9341_Write_Date ( color1 );
			}	
	}	
}


/**
 * @brief  �� ILI9341 ��ʾ������ʾӢ���ַ���
 * @param  line �����ض�ɨ�跽�����ַ�������ʼY����
  *   ��������ʹ�ú�LINE(0)��LINE(1)�ȷ�ʽָ���������꣬
  *   ��LINE(x)����ݵ�ǰѡ�������������Y����ֵ��
	*		��ʾ������ʹ��LINE��ʱ����Ҫ��Ӣ���������ó�Font8x16
 * @param  pStr ��Ҫ��ʾ��Ӣ���ַ������׵�ַ
 * @note ��ʹ��LCD_SetBackColor��LCD_type��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_printf (  uint16_t line,  char * pStr )
{
	uint16_t usX = 0;
	
	while ( * pStr != '\0' )
	{
		if ( ( usX - ILI9341_DispWindow_X_Star + LCD_Currentfonts->Width ) > LCD_X_LENGTH )
		{
			usX = ILI9341_DispWindow_X_Star;
			line += LCD_Currentfonts->Height;
		}
		
		if ( ( line - ILI9341_DispWindow_Y_Star + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = ILI9341_DispWindow_X_Star;
			line = ILI9341_DispWindow_Y_Star;
		}
		
		ILI9341_prin ( usX, line, * pStr);
		
		pStr ++;
		
		usX += LCD_Currentfonts->Width;
		
	}
	
}



/**
 * @brief  �� ILI9341 ��ʾ������ʾӢ���ַ���(��Y�᷽��)
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽�����ַ�����ʼY����
 * @param  pStr ��Ҫ��ʾ��Ӣ���ַ������׵�ַ
 * @note ��ʹ��LCD_SetBackColor��LCD_type��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_print(	 uint16_t usX,uint16_t usY ,  char * pStr )
{	
	while ( * pStr != '\0' )
	{
		if ( ( usY - ILI9341_DispWindow_Y_Star + LCD_Currentfonts->Height ) >LCD_Y_LENGTH  )
		{
			usY = ILI9341_DispWindow_Y_Star;
			usX += LCD_Currentfonts->Width;
		}
		
		if ( ( usX - ILI9341_DispWindow_X_Star + LCD_Currentfonts->Width ) >  LCD_X_LENGTH)
		{
			usX = ILI9341_DispWindow_X_Star;
			usY = ILI9341_DispWindow_Y_Star;
		}
		
		ILI9341_prin( usX, usY, * pStr);
		
		pStr ++;
		
		usY += LCD_Currentfonts->Height;		
	}	
}


/**
  * @brief  ����Ӣ����������
  * @param  fonts: ָ��Ҫѡ�������
	*		����Ϊ����ֵ֮һ
  * 	@arg��Font24x32;
  * 	@arg��Font16x24;
  * 	@arg��Font8x16;
  * @retval None
  */
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}

/**
  * @brief  ��ȡ��ǰ��������
  * @param  None.
  * @retval ���ص�ǰ��������
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}


/**
  * @brief  ����LCD��ǰ��(����)��������ɫ,RGB565
  * @param  TextColor: ָ��ǰ��(����)��ɫ
  * @param  BackColor: ָ��������ɫ
  * @retval None
  */
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor) 
{
  color2 = TextColor; 
  color1 = BackColor;
}

/**
  * @brief  ��ȡLCD��ǰ��(����)��������ɫ,RGB565
  * @param  TextColor: �����洢ǰ��(����)��ɫ��ָ�����
  * @param  BackColor: �����洢������ɫ��ָ�����
  * @retval None
  */
void LCD_GetColors(uint16_t *TextColor, uint16_t *BackColor)
{
  *TextColor = color2;
  *BackColor = color1;
}


/**
  * @brief  ���ĳ������
  * @param  Line: ָ��Ҫɾ������
  *   ��������ʹ�ú�LINE(0)��LINE(1)�ȷ�ʽָ��Ҫɾ�����У�
  *   ��LINE(x)����ݵ�ǰѡ�������������Y����ֵ����ɾ����ǰ����߶ȵĵ�x�С�
  * @retval None
  */
void LCD_ClearLine(uint16_t Line)
{
  ILI9341_Clear(0,Line,LCD_X_LENGTH,((sFONT *)LCD_GetFont())->Height);	/* ��������ʾȫ�� */

}

/**
 * @brief  �� ILI9341 ��ʾ����ʹ�� Bresenham �㷨���߶� 
 * @param  usX1 �����ض�ɨ�跽�����߶ε�һ���˵�X����
 * @param  usY1 �����ض�ɨ�跽�����߶ε�һ���˵�Y����
 * @param  usX2 �����ض�ɨ�跽�����߶ε���һ���˵�X����
 * @param  usY2 �����ض�ɨ�跽�����߶ε���һ���˵�Y����
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9341_DrawLine ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 )
{
	uint16_t us; 
	uint16_t usX_Current, usY_Current;
	
	int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int32_t lIncrease_X, lIncrease_Y; 	
	
	
	lDelta_X = usX2 - usX1; //������������ 
	lDelta_Y = usY2 - usY1; 
	
	usX_Current = usX1; 
	usY_Current = usY1; 
	
	
	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; //���õ������� 
	
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;//��ֱ�� 
	
	else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 

	
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;//ˮƽ�� 
	
	else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 

	
	if (  lDelta_X > lDelta_Y )
		lDistance = lDelta_X; //ѡȡ�������������� 
	
	else 
		lDistance = lDelta_Y; 

	
	for ( us = 0; us <= lDistance + 1; us ++ )//������� 
	{  
		ILI9341_SetPointPixel ( usX_Current, usY_Current );//���� 
		
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 
		
		if ( lError_X > lDistance ) 
		{ 
			lError_X -= lDistance; 
			usX_Current += lIncrease_X; 
		}  
		
		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			usY_Current += lIncrease_Y; 
		} 
		
	}  
	
	
}   

/*********************************************END OF FILE**********************/
