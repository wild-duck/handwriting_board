#include<reg52.h>
#include<intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit SDA=P2^0;
sbit SCL=P2^1;

#define AddWr 0x90   //д���ݵ�ַ 
#define AddRd 0x91   //�����ݵ�ַ

void delay(void)
{
    _nop_(); _nop_();
	_nop_(); _nop_();
	_nop_(); _nop_();
	_nop_(); _nop_();	
}

void init_I2C(void)		  //��ʼ������
{
   	  SDA=1;   //����ȫ���ͷţ���Ϊ1
	  delay();
	  SCL=1;
	  delay();
}


void I2C_start(void)	 //��ʼ�ź� ����
{
	SDA=1;
	delay();
	SCL=1;				  /*SCL�ߵ�ƽʱ��SDA�����½���*/
	delay();
	SDA=0;
	delay();
}

void I2C_stop()     //ֹͣ�ź�  ����
{
    SDA=0;
	delay();
	SCL=1;					/*SCL�ߵ�ƽʱ��SDA����������*/
	delay();
	SDA=1;
	delay();
}

void ack()		//Ӧ���ź�
{
   uchar i=0;

   SCL=1; 			  //SCL�ߵ�ƽʱ���  SDA�Ƿ����ͣ����߳�ʱδ��Ӧ  ����ΪӦ����
   delay();
   while((SDA==1)&&(i++)<250);   //��Ӧ��ʱ����while���

   SCL=0;           //Ӧ�����Ժ󣬵ھŸ�ʱ�ӽ���
   delay();
}

void noack()		//��Ӧ���ź�
{
    SDA=1;
	delay();
	SCL=1;
	delay();
	SCL=0;
	delay();
}

void  I2C_write_byte(uchar date)		   //  д��   ������EEPROM����1�ֽ� 8λ	date
{
     uchar i,temp;
	 temp=date;
	
	 for(i=0;i<8;i++)
	 {
	      SCL=0;			//��֤��������SCL=0ʱ�ı䣬����ᱻ��Ϊ����ʼ�źŻ�ֹͣ�ź�
	      delay();
		  if(temp&0x80)		//Ϊ��ʱ�����λΪ1
      		    SDA=1;
		  else  
		        SDA=0;
		  temp=temp<<1;		  //���ƺ��жϴθ�λ
		  delay();

		  SCL=1;			  //ʹ�����ȶ�
		  delay();
	  }
		 

	 SCL=0;			//����8�����ݣ��ͷ����ߣ�ΪӦ���ź���׼��
	 delay();
	 SDA=1;         
	 delay();
}

uchar I2C_read_byte(void)		   //��ȡ   ������EEPROM��ȡ1�ֽ� date
{
    uchar i,date;

	SCL=0;	   //�ͷ�����
	delay();
	SDA=1;   
	delay();

	for(i=0;i<8;i++)			//ѭ��8�ΰ�SDA���γ��ֵ�8���� �������Ž�date��
	{
	    SCL=1;				   //  SCL=1 ʱ��ȡ��
		delay();
		date=(date<<1)|SDA;
		SCL=0;
		delay();
	}
	return date;
}
/*
void write_I2C(uchar addr,uchar date)		//��ָ����ַд����
{
    I2C_start();
	I2C_write_byte(0xa0);   //1010 000 0	 �豸��ַ+0  д���־
	ack();
	I2C_write_byte(addr);      //д�׵�ַ 8λ��ַ
	ack();
	I2C_write_byte(date);   //д����
	ack();
	I2C_stop();
}

uchar read_I2C(uchar addr)		  //��ָ����ַ��ȡһ������
{
    uchar date;

	I2C_start();   
	I2C_write_byte(0xa0);   // ���������豸��ַ����EEPROMд��  1010 000 0	 �豸��ַ+0  д���־
	ack();
	I2C_write_byte(addr);      //����Ҫ��ȡ���ݵ��׵�ַ	  
	ack();

	I2C_start();
	I2C_write_byte(0xa1);   //1010 000 0	 �����豸��ַ+1  ��ȡ��־
	ack();
	date=I2C_read_byte();
    noack();
	I2C_stop();

	return date;
}
*/


/*******************************************************************
             ��ADתֵ����		 ���� ��AD�е����� ���� ��������ַ��
������� Chl ��ʾ��Ҫת����ͨ������Χ��0-3
����ֵ��Χ0-255
*******************************************************************/
uchar Read_AD(unsigned char Chl)
{ 
    unsigned char Val;
	I2C_start();   
	I2C_write_byte(AddWr);   // ���������豸��ַ����EEPROMд��  1001 000 0	 �豸��ַ+0  д���־
	ack();
	I2C_write_byte(0x40|Chl);      //����Ҫ��ȡ���ݵ��׵�ַ	 �ڼ�ͨ�� 
	ack();

	I2C_start();
	I2C_write_byte(AddWr+1);   //1010 000 0	 �����豸��ַ+1  ��ȡ��־
	ack();
	Val=I2C_read_byte();
    noack();
	I2C_stop();

	return Val;
}


