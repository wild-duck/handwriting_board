
#define uchar unsigned char
#define uint unsigned int



#define  LCD_DataPortH P1     //高8位数据口,8位模式下只使用高8位 
#define  LCD_DataPortL P0     //低8位数据口	,8位模式下低8位可以不接线

sbit LCD_REST  = P3^2;    //RST 引脚定义
sbit LCD_WR   =  P2^5;	 //WR  引脚定义
sbit LCD_RS   =  P2^6;	 //RS  引脚定义
sbit LCD_CS   =  P2^7;	 //CS  引脚定义 

sbit           DB16=  P3^3;
sbit           DB17=  P3^4;

#define  LCD_SIZE_X		240
#define  LCD_SIZE_Y		400

extern  uint colors[];

void LCD_Init(void);
void LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p);
void LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch);
void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c);
void delayms(int count) ;
void LCD_Write_DATA18(char x,char y ,char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Write_COM(char VH,char VL);
void LCD_Write_DATA(char VH,char VL);
void LCD_Write_COLOR(char V1,char V2,char V3);
void Pant(char V1,char V2,char V3);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);



