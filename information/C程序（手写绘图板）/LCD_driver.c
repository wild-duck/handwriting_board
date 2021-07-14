#include <reg52.h>
#include"LCD_driver.h"
#include"chinese.h"
#include"char.h"

uint colors[]=
{
  0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff  //颜色数据
};


void LCD_Init(void)
{
    LCD_REST=1;
	    delayms(5);	
		LCD_REST=0;
		delayms(5);
		LCD_REST=1;
		delayms(5);
	
		LCD_CS =0;  //打开片选使能
		                                                                                                                                                                                                                                                       
     	delayms(10);
	
        LCD_Write_COM(0x00,0x83);           
        LCD_Write_DATA(0x00,0x02);  //TESTM=1 
             
        LCD_Write_COM(0x00,0x85);  
        LCD_Write_DATA(0x00,0x03);  //VDC_SEL=011
        LCD_Write_COM(0x00,0x8B);  
        LCD_Write_DATA(0x00,0x01);
        LCD_Write_COM(0x00,0x8C);  
        LCD_Write_DATA(0x00,0x93); //STBA[7]=1,STBA[5:4]=01,STBA[1:0]=11
        
        LCD_Write_COM(0x00,0x91);  
        LCD_Write_DATA(0x00,0x01); //DCDC_SYNC=1
        
        LCD_Write_COM(0x00,0x83);  
        LCD_Write_DATA(0x00,0x00); //TESTM=0
         //Gamma Setting

        LCD_Write_COM(0x00,0x3E);  
        LCD_Write_DATA(0x00,0xB0);
        LCD_Write_COM(0x00,0x3F);  
        LCD_Write_DATA(0x00,0x03);
        LCD_Write_COM(0x00,0x40);  
        LCD_Write_DATA(0x00,0x10);
        LCD_Write_COM(0x00,0x41);  
        LCD_Write_DATA(0x00,0x56);
        LCD_Write_COM(0x00,0x42);  
        LCD_Write_DATA(0x00,0x13);
        LCD_Write_COM(0x00,0x43);  
        LCD_Write_DATA(0x00,0x46);
        LCD_Write_COM(0x00,0x44);  
        LCD_Write_DATA(0x00,0x23);
        LCD_Write_COM(0x00,0x45);  
        LCD_Write_DATA(0x00,0x76);
        LCD_Write_COM(0x00,0x46);  
        LCD_Write_DATA(0x00,0x00);
        LCD_Write_COM(0x00,0x47);  
        LCD_Write_DATA(0x00,0x5E);
        LCD_Write_COM(0x00,0x48);  
        LCD_Write_DATA(0x00,0x4F);
        LCD_Write_COM(0x00,0x49);  
        LCD_Write_DATA(0x00,0x40);	
//**********Power On sequence************
        
        LCD_Write_COM(0x00,0x17);  
        LCD_Write_DATA(0x00,0x91);
       
        LCD_Write_COM(0x00,0x2B);  
        LCD_Write_DATA(0x00,0xF9);
        delayms(10);
        
        LCD_Write_COM(0x00,0x1B);  
        LCD_Write_DATA(0x00,0x14);
        
        LCD_Write_COM(0x00,0x1A);  
        LCD_Write_DATA(0x00,0x11);
              
        LCD_Write_COM(0x00,0x1C);  
        LCD_Write_DATA(0x00,0x06);	  //0d
        
        LCD_Write_COM(0x00,0x1F);  
        LCD_Write_DATA(0x00,0x42);
        delayms(20);
        
        LCD_Write_COM(0x00,0x19);  
        LCD_Write_DATA(0x00,0x0A);
     
        LCD_Write_COM(0x00,0x19);  
        LCD_Write_DATA(0x00,0x1A);
        delayms(40);
        
        
        LCD_Write_COM(0x00,0x19);  
        LCD_Write_DATA(0x00,0x12);
        delayms(40);
        
        LCD_Write_COM(0x00,0x1E);  
        LCD_Write_DATA(0x00,0x27);
        delayms(100);	   
        
        
       //**********DISPLAY ON SETTING***********
        
        LCD_Write_COM(0x00,0x24);  
        LCD_Write_DATA(0x00,0x60);
        
        LCD_Write_COM(0x00,0x3D);  
        LCD_Write_DATA(0x00,0x40);
        
        LCD_Write_COM(0x00,0x34);  
        LCD_Write_DATA(0x00,0x38);
        
        LCD_Write_COM(0x00,0x35);  
        LCD_Write_DATA(0x00,0x38);
        
        LCD_Write_COM(0x00,0x24);  
        LCD_Write_DATA(0x00,0x38);
        delayms(40);
        
        LCD_Write_COM(0x00,0x24);  
        LCD_Write_DATA(0x00,0x3C);
        
        LCD_Write_COM(0x00,0x16);  
        LCD_Write_DATA(0x00,0x1C);
        
        LCD_Write_COM(0x00,0x01);  
        LCD_Write_DATA(0x00,0x06);
        
        LCD_Write_COM(0x00,0x55);  
        LCD_Write_DATA(0x00,0x00); 
	

		LCD_Write_COM(0x00,0x02);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x03);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x04);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x05);           
		LCD_Write_DATA(0x00,0xef);
		
		LCD_Write_COM(0x00,0x06);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x07);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x08);           
		LCD_Write_DATA(0x00,0x01);
		LCD_Write_COM(0x00,0x09);           
	    LCD_Write_DATA(0x00,0x8f);
	
	    LCD_Write_COM(0x00,0x22);  

	
	LCD_CS =1; 
}  




void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<120;j++);
}

void LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{
    LCD_DataPortH=VH;	  //高位P1口
	LCD_DataPortL=VL;	  //低位P0口	
	LCD_WR=0;
	LCD_WR=1; 
}



void LCD_Write_COM(char VH,char VL)	 //发送命令
{	
    LCD_RS=0;
	LCD_Writ_Bus(VH,VL);
}


void LCD_Write_DATA(char VH,char VL)	//发送数据
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}

void LCD_Write_DATA18(char x,char y ,char VH,char VL)	//发送数据
{
    LCD_RS=1;
	DB17 = x;
	DB16 = y;
	LCD_Writ_Bus(VH,VL);
}



 void LCD_Write_COLOR(char V1,char V2,char V3)	//发送数据
{
	LCD_RS=1;  
	DB17 = (V1 >> 5) & 0x01;   
	DB16 = (V1 >> 4) & 0X01;
	LCD_DataPortH=  ((V2 >> 2) & 0x0f)+((V1 << 4)& 0xf0);	  //高位P1口
	LCD_DataPortL= ((V2 << 6)& 0xc0) + (V3 & 0x3f);	  //低位P0口	
	LCD_WR=0;
	LCD_WR=1; 
    	
}	   


void Pant(char V1,char V2,char V3)
{
	int i,j;
	LCD_CS =0;  //打开片选使能
	Address_set(0,0,239,399);
    for(i=0;i<400;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 LCD_Write_COLOR(V1,V2,V3);
	    }

	  }
     LCD_CS =1;  //关闭片选使能
}


void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{  

    LCD_Write_COM(0x00,0x02);LCD_Write_DATA(x1,x1>>8);   //开始X
	LCD_Write_COM(0x00,0x03);LCD_Write_DATA(x1>>8,x1);

	LCD_Write_COM(0x00,0x06);LCD_Write_DATA(y1,y1>>8);	  //开始Y
	LCD_Write_COM(0x00,0x07);LCD_Write_DATA(y1>>8,y1);

    LCD_Write_COM(0x00,0x04);LCD_Write_DATA(x2,x2>>8);   //结束X
	LCD_Write_COM(0x00,0x05);LCD_Write_DATA(x2>>8,x2);

	LCD_Write_COM(0x00,0x08);LCD_Write_DATA(y2,y2>>8);   //结束Y
	LCD_Write_COM(0x00,0x09);LCD_Write_DATA(y2>>8,y2);

	LCD_Write_COM(0x00,0x22);							 
}


/**********************************************************

  写汉字子函数

**********************************************************/
void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c)
{
   int e=0,i,j;
   int  ed;
   
   uint  ncols;
   uint  nrows;
   uint  nbytes;

   uchar *pfont;
   uchar *pchar;
   uchar *fonttable[]={(uchar *)hz16,(uchar *)hz24 , (uchar *)hz32};
   
   pfont=(uchar *)fonttable[size];

   if(size==0)
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;	 //(16*16)/8
   }
   else
   if(size==1)
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;  //(24*24)/8
   }
   else
   if(size==2)
   {
     ncols =32-1;
     nrows =32-1;
     nbytes =132;   //(32*32)/8
   }
   
   pchar=pfont + (nbytes*(c-1));

   Address_set(x,  y, x+nrows,y+ncols);
   
   for(i=0;i<nbytes;i++)
   {
     ed=*pchar++;
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else
	 e=8;
     
     for(j=0;j<e;j++)
     {// unsigned char temp;
	  if((ed>>j)&0x01)
      { 
       	//temp = 	For_color&0x00ff
	   LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	  }
     else
     {
       LCD_Write_DATA( Bk_color>>8 ,  Bk_color);  //backcolor
	 }
	}
  }
}

/*********************************************************/

/**********************************************************

  字符显示子函数

**********************************************************/
void LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch)
{       
   uchar temp , Bytes;
   uchar pos,t;
   uint  CHAR_W,CHAR_H;

   
   //CHAR_W = 8;         //8*16
   //CHAR_H = 16;

     CHAR_W = 16;         //16*24
     CHAR_H = 24;

   if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))
   return;
   
   Address_set(x, y, x+CHAR_W-1, y+CHAR_H-1);
   ch = ch-32;                       //按照ASCII编码顺序的到相应字母的编码
   Bytes = (CHAR_W*CHAR_H)/8;
   for(pos=0;pos<Bytes;pos++)  //CHAR_H 	(CHAR_W*CHAR_H)/8
   {
     // temp= Font8x16[ch][pos];

	  //temp= Font16x24[ch][pos];
	  temp= Font16x24[ch][pos];
      
      for(t=0;t<8;t++) //CHAR_W
      {                 
	    if(temp&0x80)
	    LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	    else 
	    LCD_Write_DATA(Bk_color>>8 , Bk_color );  //backcolor
        temp<<=1; 
      }
	  
   }
}  

/**********************************************************
 显示字符串子函数

 x,y:起点坐标  
 *p:字符串起始地址

**********************************************************/
void LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p)
{         
   while(*p!='\0')
   {       
     LCD_ShowChar(x,y,For_color,Bk_color,*p);
    // x+=8;
	 x+=16;
     p++;
   }
}