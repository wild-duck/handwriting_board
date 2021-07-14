
#include <reg52.h>
#include <intrins.h>
#include "LCD_driver.h"
#include"AD8051.h"


#define uint unsigned int
#define uchar unsigned char


signed char x,y, a,b;
uchar Tempx[4],Tempy[4];
uint val1,val2;



void get_xy(void);
void  display_ack(void);


/**********************************************************

  主函数

**********************************************************/
void main(void)
{  	
     uchar i,j;
    P2 = 0xff;
    P0 = 0xff;

    LCD_Init();      //初始化
    Pant(0xff, 0xff,0xff); //清屏

  	LCD_CS = 0;
    ChineseChar(14+30,10,1,colors[2],colors[7],1);	  //手
    ChineseChar(46+30,10,1,colors[2],colors[7],2);	  //写
    ChineseChar(78+30,10,1,colors[2],colors[7],3);	  //绘
    ChineseChar(110+30,10,1,colors[2],colors[7],4);	  //图
	 ChineseChar(142+30,10,1,colors[2],colors[7],5);  //板


	 LCD_ShowChar(40,170,colors[2],colors[7],'x');	     //x	 16*24
	 LCD_ShowChar(56,170,colors[2],colors[7],'=');	     //=	 16*24
	 
	 LCD_ShowChar(136,170,colors[2],colors[7],'m');	     //m	 16*24
	 LCD_ShowChar(152,170,colors[2],colors[7],'m');	     //m	 16*24

	 LCD_ShowChar(40,205,colors[2],colors[7],'y');	     //y	 16*24
	 LCD_ShowChar(56,205,colors[2],colors[7],'=');	     //=	 16*24

	 LCD_ShowChar(136,205,colors[2],colors[7],'m');	     //m	 16*24
	 LCD_ShowChar(152,205,colors[2],colors[7],'m');	     //m	 16*24


	   	 Address_set(0,240,239,399);			  //绿色
     for(i=0;i<160;i++)
	 {
	      for (j=0;j<240;j++)
	   	  {
        	  LCD_Write_COLOR(0x00,0x3f,0x00);	 
	      }
	 }

   	LCD_CS = 1;

	   while(1)	
	  {	  
	         val1=Read_AD(0x02);
			 val2=Read_AD(0x03);
	
			 get_xy();
	
	    	display_ack();
	
	  }  
}



void display_ack()
{	  
     LCD_CS = 0;
      if((x==0)&&(y==0))      
	         ChineseChar(80,65,1,colors[7],colors[4],7);	  //否	 24*24
	  else 
	  {
	       ChineseChar(80,65,1,colors[7],colors[4],6);			 //是
		     
           if(x<0)
		   {	
		         a=0-x;
		         ChineseChar(80,100,1,colors[7],colors[4],8);		  //左
				 if(y>0)
				 { 
				      ChineseChar(80,135,1,colors[7],colors[4],11);	 	     //二
					  	Tempx[0]='-';
					    Tempy[0]='+';
					  b=y;
				 }
				 else if(y<0)
	             {
				      ChineseChar(80,135,1,colors[7],colors[4],12);			 //三
					  	Tempx[0]='-';
					    Tempy[0]='-';
					  b=0-y;
	             }
		   }

	      else if(x>0)
		  {
		        ChineseChar(80,100,1,colors[7],colors[4],9);	  //右
				 a=x;
				 if(y>0)
				 {
			    	  ChineseChar(80,135,1,colors[7],colors[4],10);	         //一
					    Tempx[0]='+';
					    Tempy[0]='+';
					  b=y;
				 }
				 else if(y<0)
				 { 
				      ChineseChar(80,135,1,colors[7],colors[4],13);	 	     //四 
					  	Tempx[0]='+';
					    Tempy[0]='-';
					  b=0-y;
				 }
		  }

		  Tempx[1]=a/10+0x30;		  //x坐标
		  Tempx[2]=a%10+0x30;	
	  	  Tempy[1]=b/10+0x30;				 //y坐标
		  Tempy[2]=b%10+0x30;	
 		
		  LCD_ShowChar(80,170,colors[7],colors[2], Tempx[0]);
		  LCD_ShowChar(96,170,colors[7],colors[2], Tempx[1]);
		  LCD_ShowChar(112,170,colors[7],colors[2], Tempx[2]);

		  LCD_ShowChar(80,205,colors[7],colors[2], Tempy[0]);
		  LCD_ShowChar(96,205,colors[7],colors[2], Tempy[1]);
		  LCD_ShowChar(112,205,colors[7],colors[2], Tempy[2]);

//
//	  	  Address_set(120+2*x-3,320-2*y-3,120+2*x+3,320-2*y+3);		  //-+1=9个点；-+2=25 -+3=49
//		  for(i=0;i<49;i++)
//	         LCD_Write_COLOR(0x00,0x00,0x3f);    //画点   蓝色

          LCD_CS =1 ;
	  }
}


void get_xy()
{
   
   if ( (val1<5 )&&(val2<4 ) ) 	                                 {x=0;y=0;}
  else if ( (val1>=70  )&&(val1<71  )&&(val2>=53   )&&(val2<55   ) )  	 { x=-60;y=40; }
   else if ( (val1>=71 )&&(val1<72)&&(val2>=51 )&&(val2<52 ) )  	 { x=-50;y=40; }
   else if ( (val1>=70 )&&(val1<72 )&&(val2>=49 )&&(val2<51) )  	 { x=-40;y=40; }
   else if ( (val1>=71 )&&(val1<73)&&(val2>=48 )&&(val2<49 ) )     { x=-30;y=40; }
   else if ( (val1>=70 )&&(val1<71 )&&(val2>=47 )&&(val2<48) )  	 { x=-20;y=40;}
   else if ( (val1>=72 )&&(val1<73)&&(val2>=46 )&&(val2<47 ) )  	 { x=-10;y=40;}
   else if ( (val1>=75 )&&(val1<76 )&&(val2>=45 )&&(val2<47 ) )  	 { x=10;y=40;}
   else if ( (val1>=76 )&&(val1<79 )&&(val2>=44 )&&(val2<45) )  	 { x=20;y=40;}
   else if ( (val1>=79)&&(val1<83 )&&(val2>=44 )&&(val2<45) )  	     { x=30;y=40;}
   else if ( (val1>=85 )&&(val1<87)&&(val2>=43 )&&(val2<44) )  	 { x=40;y=40;}
   else if ( (val1>=91 )&&(val1<92 )&&(val2>=42 )&&(val2<44 ) )  	 { x=50;y=40;}
   else if ( (val1>=100 )&&(val1<102 )&&(val2>=42 )&&(val2<43) )  	 { x=60;y=40; }

   else if ( (val1>=70 )&&(val1<71 )&&(val2>=51)&&(val2<54 ) )  	 { x=-60;y=30; }
   else if ( (val1>=70 )&&(val1<71 )&&(val2>50)&&(val2<51 ) )  	 { x=-50;y=30; }

   else if ( (val1>=70 )&&(val1<71 )&&(val2>=49 )&&(val2<50 ) )  	 { x=-40;y=30;}
   
   else if ( (val1>=70 )&&(val1<71)&&(val2>=49 )&&(val2<50 ) )  	 { x=-30;y=30;}
   else if ( (val1>=71)&&(val1<72)&&(val2>=48 )&&(val2<49 ) )  	 { x=-20;y=30;}
   else if ( (val1>=72 )&&(val1<73)&&(val2>=46)&&(val2<48 ) )  	 { x=-10;y=30;}
//  else if ( (val1>=  )&&(val1<  )&&(val2>=   )&&(val2<   ) )
   else if ( (val1>=74 )&&(val1<76 )&&(val2>=45 )&&(val2<47 ) )  	   {x=10; y=30;}
   else if ( (val1>=76 )&&(val1<78 )&&(val2>=44 )&&(val2<45 ) )  	  {x=20; y=30;}
   else if ( (val1>=78)&&(val1<80 )&&(val2>=43 )&&(val2<44 ) )  	  {x=30; y=30;}
   else if ( (val1>=82 )&&(val1<83 )&&(val2>=42)&&(val2<43 ) )  	  {x=40; y=30;}
   else if ( (val1>=87)&&(val1<88 )&&(val2>=43)&&(val2<44 ) )  	  { x=50;y=30; }
   else if ( (val1>=92)&&(val1<93 )&&(val2>=42)&&(val2<44 ) )  	  { x=60;y=30; }

   else if ( (val1>=69 )&&(val1<70 )&&(val2>=51 )&&(val2<53 ) )  	 { x=-60;y=20; }
   else if ( (val1>=70 )&&(val1<71)&&(val2>=51 )&&(val2<52 ) )  	 { x=-50;y=20; }
   else if ( (val1>=69)&&(val1<70 )&&(val2>=50)&&(val2<51 ) )    { x=-40;y=20;}
   else if ( (val1>=70 )&&(val1<71 )&&(val2>=48 )&&(val2<50 ) )  	 { x=-30;y=20;}
  else if ( (val1>=70  )&&(val1<71  )&&(val2>=47   )&&(val2<48   ) )	 {x=-20;y=20;}
  else if ( (val1>=71  )&&(val1<73  )&&(val2>=46   )&&(val2<47   ) )	  {x=-10;y=20;}
  else if ( (val1>=73  )&&(val1<74  )&&(val2>=45   )&&(val2<46   ) )	 {x=10;y=20;}
  else if ( (val1>=74  )&&(val1<75  )&&(val2>=43   )&&(val2<44   ) )	 {x=20;y=20;}

   else if ( (val1>=76 )&&(val1<78 )&&(val2>=43 )&&(val2<45 ) )  	  {x=30; y=20;}
    else if ( (val1>=78)&&(val1<79 )&&(val2>=43 )&&(val2<45 ) )  	{x=40; y=20;}
  else if ( (val1>=81 )&&(val1<83 )&&(val2>=41 )&&(val2<43 ) )  {x=50; y=20;}
   else if ( (val1>=84 )&&(val1<86 )&&(val2>=41 )&&(val2<44 ) )  	  {x=60; y=20;}

   else if ( (val1>=69 )&&(val1<71 )&&(val2>=49 )&&(val2<50 ) )  	 { x=-60;y=10; }
   else if ( (val1>=69 )&&(val1<70 )&&(val2>=50 )&&(val2<52 ) )  	 { x=-50;y=10; }
   else if ( (val1>=70 )&&(val1<71 )&&(val2>=48 )&&(val2<50 ) )  	 { x=-40;y=10;}
   else if ( (val1>=69)&&(val1<72 )&&(val2>=47 )&&(val2<48 ) )  	 { x=-30;y=10;}

  else if ( (val1>=70  )&&(val1<71  )&&(val2>=47   )&&(val2<49   ) )	 {x=-20;y=10;}
  else if ( (val1>=70  )&&(val1<71  )&&(val2>=45   )&&(val2<47   ) )	 {x=-10;y=10;}
  else if ( (val1>=71  )&&(val1<72  )&&(val2>=44   )&&(val2<46   ) )	 {x=10;y=10;}
  else if ( (val1>=72  )&&(val1<74  )&&(val2>43   )&&(val2<44  ) )	 {x=20;y=10;}

   else if ( (val1>=73 )&&(val1<74 )&&(val2>=41 )&&(val2<43 ) )  	  {x=30; y=10;}
   else if ( (val1>=74 )&&(val1<75 )&&(val2>=42 )&&(val2<43 ) )  	  {x=40; y=10;}
  else if ( (val1>=76 )&&(val1<77 )&&(val2>=41 )&&(val2<43 ) )  	  {x=50; y=10;}
   else if ( (val1>=76 )&&(val1<79 )&&(val2>=41 )&&(val2<43 ) )  	  {x=60; y=10;}


   else if ( (val1>=70 )&&(val1<71 )&&(val2>=48 )&&(val2<50 ) )  	 { x=-60;y=-10; }
   else if ( (val1>=68)&&(val1<70 )&&(val2>=48 )&&(val2<49 ) )  	 { x=-50;y=-10; }
   else if ( (val1>=68 )&&(val1<69 )&&(val2>=49 )&&(val2<50 ) )  	 { x=-40;y=-10;}
   else if ( (val1>=69 )&&(val1<70 )&&(val2>=46 )&&(val2<48 ) )  	 { x=-30;y=-10;}

  else if ( (val1>=68  )&&(val1<69  )&&(val2>=46   )&&(val2<48  ) )	  {x=-20;y=-10;}
  else if ( (val1>=68  )&&(val1<69  )&&(val2>=45   )&&(val2<46   ) )	   {x=-10;y=-10;}
  else if ( (val1>=68  )&&(val1<69  )&&(val2>=43   )&&(val2<44   ) )	  {x=10;y=-10;}
  else if ( (val1>=67  )&&(val1<68  )&&(val2>=43   )&&(val2<45   ) )	 {x=20;y=-10;}

   else if ( (val1>=66 )&&(val1<68 )&&(val2>=42 )&&(val2<44 ) )  	  {x=30; y=-10;}
    else if ( (val1>=64 )&&(val1<67 )&&(val2>=41 )&&(val2<43 ) )    {x=40; y=-10;}
   else if ( (val1>=63 )&&(val1<65 )&&(val2>=40 )&&(val2<43 ) )  	  {x=50; y=-10;}
   else if ( (val1>=62)&&(val1<64 )&&(val2>=40 )&&(val2<41) )  	  {x=60; y=-10;}

 //  else if ( (val1>=68 )&&(val1<70 )&&(val2>=48 )&&(val2<49) )  	  {x=-60; y=-20;}
   else if ( (val1>=69 )&&(val1<70 )&&(val2>=48 )&&(val2<49 ) )  	 { x=-50;y=-20; }
   else if ( (val1>=70 )&&(val1<71 )&&(val2>=48 )&&(val2<49 ) )  	 { x=-40;y=-20;}
   else if ( (val1>=68 )&&(val1<70 )&&(val2>=46 )&&(val2<48 ) )  	  { x=-30;y=-20;}

   else if ( (val1>=68  )&&(val1<69  )&&(val2>=45   )&&(val2<46   ) )	  {x=-20;y=-20;}
 else if ( (val1>=67  )&&(val1<68  )&&(val2>=45   )&&(val2<47   ) )	  {x=-10;y=-20;}
  else if ( (val1>=65  )&&(val1<67  )&&(val2>=44   )&&(val2<45   ) )	  {x=10;y=-20;}
  else if ( (val1>=64  )&&(val1<66  )&&(val2>=42   )&&(val2<44   ) )	  {x=20;y=-20;}

   else if ( (val1>=63 )&&(val1<64 )&&(val2>=42 )&&(val2<43 ) )  	  {x=30; y=-20;}
   else if ( (val1>=60 )&&(val1<62)&&(val2>=40 )&&(val2<43 ) )  	  {x=40; y=-20;}
   else if ( (val1>=57 )&&(val1<58)&&(val2>=40 )&&(val2<42 ) )  	  {x=50; y=-20;}
   else if ( (val1>=56 )&&(val1<57)&&(val2>=39 )&&(val2<40) )  	  {x=60; y=-20;}



   else if ( (val1>=68 )&&(val1<70 )&&(val2>=48 )&&(val2<49 ) )  	  {x=-60; y=-30;}
   else if ( (val1>=68)&&(val1<70 )&&(val2>=47 )&&(val2<48 ) )  	 { x=-50;y=-30; }
   else if ( (val1>=67)&&(val1<70 )&&(val2>=47 )&&(val2<48 ) )  	 { x=-40;y=-30; }
   else if ( (val1>=67 )&&(val1<69 )&&(val2>=46 )&&(val2<47) )     { x=-30;y=-30; }
   else if ( (val1>=67)&&(val1<69 )&&(val2>=45)&&(val2<46) )  	    { x=-20;y=-30;}
   else if ( (val1>=67 )&&(val1<68 )&&(val2>=44 )&&(val2<45 ) )  	 { x=-10;y=-30;}
   else if ( (val1>=64 )&&(val1<66 )&&(val2>=43 )&&(val2<44 ) )  	 { x=10;y=-30;}
   else if ( (val1>=62 )&&(val1<69 )&&(val2>=41 )&&(val2<42 ) )  	 { x=20;y=-30;}
   else if ( (val1>=59 )&&(val1<60 )&&(val2>=41 )&&(val2<42 ) )  	 { x=30;y=-30;}
   else if ( (val1>=56)&&(val1<57 )&&(val2>=40 )&&(val2<42 ) )  	 { x=40;y=-30;}
   else if ( (val1>=52 )&&(val1<54 )&&(val2>=39 )&&(val2<40 ) )  	 { x=50;y=-30;}
   else if ( (val1>=46 )&&(val1<48 )&&(val2>=37 )&&(val2<39 ) )  	 { x=60;y=-30;}

   else if ( (val1>=68 )&&(val1<70 )&&(val2>=47)&&(val2<48 ) )  	  {x=-60; y=-40;}
   else if ( (val1>=68 )&&(val1<70 )&&(val2>=48 )&&(val2<49 ) )  	  { x=-50;y=-40; }
   else if ( (val1>=67)&&(val1<69)&&(val2>=46 )&&(val2<48) )        { x=-40;y=-40;}
   else if ( (val1>=67 )&&(val1<68 )&&(val2>=45 )&&(val2<46 ) )  	  { x=-30;y=-40;}
   else if ( (val1>=67 )&&(val1<68 )&&(val2>=44 )&&(val2<45 ) )  	  { x=-20;y=-40;}
   else if ( (val1>=66 )&&(val1<67 )&&(val2>=44 )&&(val2<46 ) )  	  { x=-10;y=-40;}
   else if ( (val1>=63 )&&(val1<65)&&(val2>=43 )&&(val2<44) )  	  {x=10; y=-40;}
   else if ( (val1>=62 )&&(val1<63 )&&(val2>=41 )&&(val2<43 ) )  	  {x=20; y=-40;}
   else if ( (val1>=58 )&&(val1<60 )&&(val2>=41 )&&(val2<42 ) )  	  { x=30;y=-40;}
   else if ( (val1>=53 )&&(val1<55)&&(val2>=40 )&&(val2<42 ) )  	  {x=40; y=-40;}
   else if ( (val1>=48)&&(val1<49)&&(val2>=37 )&&(val2<38 ) )  	  {x=50; y=-40;}
   else if ( (val1>=38 )&&(val1<39 )&&(val2>=35 )&&(val2<37 ) )  	  {x=60; y=-40;}
}
