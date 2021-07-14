#include<reg52.h>
#include<intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit SDA=P2^0;
sbit SCL=P2^1;

#define AddWr 0x90   //写数据地址 
#define AddRd 0x91   //读数据地址

void delay(void)
{
    _nop_(); _nop_();
	_nop_(); _nop_();
	_nop_(); _nop_();
	_nop_(); _nop_();	
}

void init_I2C(void)		  //初始化函数
{
   	  SDA=1;   //把线全部释放，置为1
	  delay();
	  SCL=1;
	  delay();
}


void I2C_start(void)	 //起始信号 函数
{
	SDA=1;
	delay();
	SCL=1;				  /*SCL高电平时，SDA出现下降沿*/
	delay();
	SDA=0;
	delay();
}

void I2C_stop()     //停止信号  函数
{
    SDA=0;
	delay();
	SCL=1;					/*SCL高电平时，SDA出现上升沿*/
	delay();
	SDA=1;
	delay();
}

void ack()		//应答信号
{
   uchar i=0;

   SCL=1; 			  //SCL高电平时检测  SDA是否被拉低，或者超时未反应  都视为应答了
   delay();
   while((SDA==1)&&(i++)<250);   //有应答时跳出while语句

   SCL=0;           //应答完以后，第九个时钟结束
   delay();
}

void noack()		//非应答信号
{
    SDA=1;
	delay();
	SCL=1;
	delay();
	SCL=0;
	delay();
}

void  I2C_write_byte(uchar date)		   //  写入   主机向EEPROM发送1字节 8位	date
{
     uchar i,temp;
	 temp=date;
	
	 for(i=0;i<8;i++)
	 {
	      SCL=0;			//保证数据是在SCL=0时改变，否则会被认为是起始信号或停止信号
	      delay();
		  if(temp&0x80)		//为真时，最高位为1
      		    SDA=1;
		  else  
		        SDA=0;
		  temp=temp<<1;		  //左移后，判断次高位
		  delay();

		  SCL=1;			  //使数据稳定
		  delay();
	  }
		 

	 SCL=0;			//送完8个数据，释放总线，为应答信号做准备
	 delay();
	 SDA=1;         
	 delay();
}

uchar I2C_read_byte(void)		   //读取   主机从EEPROM读取1字节 date
{
    uchar i,date;

	SCL=0;	   //释放总线
	delay();
	SDA=1;   
	delay();

	for(i=0;i<8;i++)			//循环8次把SDA依次出现的8个数 读进来放进date里
	{
	    SCL=1;				   //  SCL=1 时读取？
		delay();
		date=(date<<1)|SDA;
		SCL=0;
		delay();
	}
	return date;
}
/*
void write_I2C(uchar addr,uchar date)		//在指定地址写数据
{
    I2C_start();
	I2C_write_byte(0xa0);   //1010 000 0	 设备地址+0  写入标志
	ack();
	I2C_write_byte(addr);      //写首地址 8位地址
	ack();
	I2C_write_byte(date);   //写数据
	ack();
	I2C_stop();
}

uchar read_I2C(uchar addr)		  //在指定地址读取一个数据
{
    uchar date;

	I2C_start();   
	I2C_write_byte(0xa0);   // 主机发送设备地址，向EEPROM写入  1010 000 0	 设备地址+0  写入标志
	ack();
	I2C_write_byte(addr);      //发送要读取数据的首地址	  
	ack();

	I2C_start();
	I2C_write_byte(0xa1);   //1010 000 0	 发送设备地址+1  读取标志
	ack();
	date=I2C_read_byte();
    noack();
	I2C_stop();

	return date;
}
*/


/*******************************************************************
             读AD转值程序		 主机 把AD中的数据 读出 （器件地址）
输入参数 Chl 表示需要转换的通道，范围从0-3
返回值范围0-255
*******************************************************************/
uchar Read_AD(unsigned char Chl)
{ 
    unsigned char Val;
	I2C_start();   
	I2C_write_byte(AddWr);   // 主机发送设备地址，向EEPROM写入  1001 000 0	 设备地址+0  写入标志
	ack();
	I2C_write_byte(0x40|Chl);      //发送要读取数据的首地址	 第几通道 
	ack();

	I2C_start();
	I2C_write_byte(AddWr+1);   //1010 000 0	 发送设备地址+1  读取标志
	ack();
	Val=I2C_read_byte();
    noack();
	I2C_stop();

	return Val;
}


