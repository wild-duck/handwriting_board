 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   华邦 8M串行flash测试，并将测试信息通过串口1在电脑的超级终端中打印出来
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./huaban/bsp_huaban.h"
#include "./adc/bsp_adc.h"
#include <stdio.h>
#include <string.h>

/*
1.初始化液晶引脚
2.模拟8080时序
	写命令
	写数据
	读数据
3.读取ID测试函数
4.写一个xy特定颜色像素点

*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint32_t ADC_ConvertedValue[NOFCHANEL];

 
uint16_t ADC_ConvertedValueLocal[NOFCHANEL*2];  

uint16_t  ADXY[3][100]={0};
int k=0;
float   z,m;

//Xdefine C0 A2
#define         Xp00  142.861546929988
#define         Xp10  4.98407419949185      
#define         Xp01   -5.00984791642734
#define         Xp20 -0.00406905682409815
#define         Xp11  0.00581749615235295
#define         Xp02  -0.00203423758503009
#define         Xp30  1.38128506216889e-07
#define         Xp21  -9.50880466940976e-07
#define         Xp12  3.76648885851927e-06
#define         Xp03   -2.79535195463090e-06
//Xdefine C0 A3
#define         p00 -296.202970767706
#define         p10  4.86815251950474        
#define         p01   -3.99042118276565
#define         p20  -0.00702093956622412
#define         p11   0.00518120938903531
#define         p02   0.00122657726971700
#define         p30  2.34990474133943e-07
#define         p21  1.18884070951711e-06
#define         p12   8.93096006336612e-06
#define         p03   -1.03631066865919e-05
//Ydefine
#define         Yp00  1228.53044185996
#define         Yp10 -6.27188616617648
#define         Yp01   1.63595773107984
#define         Yp20  0.00750450093269330
#define         Yp11  -0.00295725001627620
#define         Yp02 0.00134286403914364
#define         Yp30  -5.24328679757170e-08
#define         Yp21  -2.04088290487996e-06
#define         Yp12 -1.00833674469202e-05
#define         Yp03  9.65304130219359e-06




// 函数原型声明
void Delay(__IO uint32_t nCount);      //延时


void  Display_XY(uint16_t C0, uint16_t A2, uint16_t A3,float x,float y);//显示XY坐标            //显示目前坐标
void  Display_Coor(float x, float y);//显示点
void  Display_V(float x, float y, float w);//显示电压
void  Clear()//清频幕
{		    int i,j;
	    ILI9341_Init(); //初始化
			color_back(WHITE);
		  ILI9341_Clear(0,160,240,160);//分屏
			color_type(RED);
			for(i=0;i<240;i=i+8)
	    ILI9341_DrawLine(i,160,i,320); //画坐标轴
	    for(j=0;j<160;j+=8)
	    ILI9341_DrawLine(0,160+j,240,160+j);	
	    color_type(BLACK);
	    ILI9341_DrawLine(120,160,120,320);
    	ILI9341_DrawLine(0,240,240,240);

}
void correct1(uint16_t C0, uint16_t A2, uint16_t A3);
void correct2(uint16_t C0, uint16_t A2, uint16_t A3);
void correct3(uint16_t C0, uint16_t A2, uint16_t A3);
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{ 
int i=0,j=0;
uint16_t 	A3,A2,C0;
float x = 0.0,y = 0.0;
	/* 配置串口为：115200 8-N-1 */
	USART_Config();
			
  // ADC 初始化
	ADCx_Init();
	
	color_back(BLACK);
	ILI9341_Init(); //初始化 
		
	color_back(WHITE); 
	ILI9341_Clear(0,160,240,160);//分屏
	

	color_type(RED); 
	for(i=0;i<240;i=i+8)
	ILI9341_DrawLine(i,160,i,320); 
	for(j=0;j<160;j+=8)
	ILI9341_DrawLine(0,160+j,240,160+j);
	color_type(BLACK);
	ILI9341_DrawLine(120,160,120,320);
  ILI9341_DrawLine(0,240,240,240);

		while(1)
	{
		x=0;y=0;

		for(i=0;i<10;i++)
		 {
			ADXY[0][i]=ADC_ConvertedValue[0];
			ADXY[1][i]=ADC_ConvertedValue[1];
			ADXY[2][i]=ADC_ConvertedValue[2];
      Delay(10000);			 
		 } 
		for(i=0;i<10;i++)
		{
			ADXY[0][i+1]=ADXY[0][i+1]+ADXY[0][i];
			ADXY[1][i+1]=ADXY[1][i+1]+ADXY[1][i];
			ADXY[2][i+1]=ADXY[2][i+1]+ADXY[2][i];
		}
			C0=(ADXY[0][9])/10;
			A2=(ADXY[1][9])/10;
			A3=(ADXY[2][9])/10;	

		printf("%d,%d,%d\n",C0,A2,A3);
	
		x = Xp00+Xp10*C0+Xp01*A2+Xp20*C0*C0+Xp11*A2*A2+Xp02*C0*A2+Xp30*C0*C0*C0+Xp21*A2*A2*A2+Xp12*C0*C0*A2+Xp03*A2*A2*C0-z;
	  y = Yp00+Yp10*A2+Yp01*A3+Yp20*A2*A2+Yp11*A3*A3+Yp02*A2*A3+Yp30*A2*A2*A2+Yp21*A3*A3*A3+Yp12*A2*A2*A3+Yp03*A3*A3*A2-m;
    
		if(x>=5)
    x = p00+ p10*C0+ p01*A3+ p20*C0*C0+ p11*A3*A3+p02*C0*A3+p30*C0*C0*C0+p21*A3*A3*A3+p12*C0*C0*A3+p03*A3*A3*C0-z;
		
		Display_XY(C0,A2,A3,x,y);
		Display_V(C0,A2,A3);
		Display_Coor(x,y);
		
		if(C0<=50)
		{Clear();}                                      //清频幕
		if(A2<=100)
		{correct1(C0,A2,A3);}
	}
}


//以下为函数
void Delay(__IO uint32_t nCount)//延时
{
  for(; nCount != 0; nCount--);
}


void  Display_XY(	uint16_t C0, uint16_t A2,uint16_t A3,float x,float  y)//显示XY坐标            //显示目前坐标
{
	char a[50] ;
	char b[50] ;
	char c[100] ;
	
	if(x<0&y<0)
	{
	//c库转译int为char
	sprintf(a,"x=%.3f          ",x);
	sprintf(b,"y=%.3f          ",y);
	sprintf(c,"The point is in quadrant  3");
	}
		if(x<0&y>0)
	{
	//c库转译int为char
	sprintf(a,"x=%.3f          ",x);
	sprintf(b,"y=%.3f          ",y);
	sprintf(c,"The point is in quadrant  2");
	}
		if(x>0&y<0)
	{
	//c库转译int为char
	sprintf(a,"x=%.3f          ",x);
	sprintf(b,"y=%.3f          ",y);
	sprintf(c,"The point is in quadrant  4");
	}
		if(x>0&y>0)
	{
	//c库转译int为char
	sprintf(a,"x=%.3f          ",x);
	sprintf(b,"y=%.3f          ",y);
	sprintf(c,"The point is in quadrant  1");
	}
	color_type(RED);
	color_back(BLACK);
	ILI9341_printf(82,a);
	ILI9341_printf(102,b);
	ILI9341_printf(122,c);
	if(C0<=500&A2<=500&A3<=500)
	ILI9341_printf(142,"N0  Brush  touch!");
  else
  {
	ILI9341_printf(142,"OK! Brush  touch.");
	}		
}

void  Display_Coor(float x, float y) //dian
{
	x=8*x;y=8*y;
	x=x+120;
	y=240-y;
	ILI9341_DrawCircle(x,y,2,1);			
}

void  Display_V(float x, float y, float w)//电压
{	
	float 	Vx,Vy,Vc;
	char a[100] ;
	char b[100] ;
	char c[100] ;
			
	Vx = (float)(x/4096.0)*3.3;
	Vy = (float)(y/4096.0)*3.3;//电压计算
	Vc = (float)(w/4096.0)*3.3;
	
	//c库转译int为char
	sprintf(a,"VC0:%.5f      C0=%.f      ",Vx,x);
	sprintf(b,"VA2:%.5f      A2=%.f      ",Vy,y);
	sprintf(c,"VA3:%.5f      A3=%.f      ",Vc,w);
		
	color_type(RED);
	ILI9341_printf(22,a);
	ILI9341_printf(42,b);
	ILI9341_printf(62,c);
	ILI9341_printf(2,"voltage:");	
}

void  correct1(uint16_t C0,uint16_t A2,uint16_t A3)
{
	float x,y;
  ILI9341_printf(82,"start  calibration!");
	Delay(0xffeeee);
	C0=ADC_ConvertedValue[0];
	A2=ADC_ConvertedValue[1];
	A3=ADC_ConvertedValue[2];
  Delay(10000);
	ILI9341_printf(82,"perfect  calibration!");
	Delay(0xffeeee);
	printf("%d\n%d\n",C0,A2);
  x = Xp00+Xp10*C0+Xp01*A2+Xp20*C0*C0+Xp11*A2*A2+Xp02*C0*A2+Xp30*C0*C0*C0+Xp21*A2*A2*A2+Xp12*C0*C0*A2+Xp03*A2*A2*C0;
  y = Yp00+Yp10*A2+Yp01*A3+Yp20*A2*A2+Yp11*A3*A3+Yp02*A2*A3+Yp30*A2*A2*A2+Yp21*A3*A3*A3+Yp12*A2*A2*A3+Yp03*A3*A3*A2;
  printf("%.3f\n%.3f\n",x,y);
	z = x + 6.0;
  m = y ;
}
/*********************************************END OF FILE**********************/
