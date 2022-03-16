/*
  程序说明: DS1302驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include <reg52.h>
#include <intrins.h>

sbit SCK=P1^6;		
sbit SDA=P1^5;		
sbit RST = P1^7;   // DS1302复位												

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
	
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
  Write_Ds1302((dat/10<<4)|(dat%10));	
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
	unsigned int dat1=0,dat2=0;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	dat1=temp/16;
	dat2=temp%16;
	temp=dat1*10+dat2;
	return (temp);	
	
}

/*
ds1302操作方法：
1、程序增加#include<ds1302.h>，#include<ds1302.c>
2、在程序中增加语句:
uchar shijian[]={**,**,**,0,0,0,0};//秒-分-时,日-月-星期-年
3、在程序中增加下列函数：
void DS_init(void)
{
	unsigned char i,add;
	add=0x80;
	Write_Ds1302_Byte(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302_Byte(add,shijian[i]);
		add=add+2;
	}
	Write_Ds1302_Byte(0x8e,0x80);
}

void DS_get(void)
{
	unsigned char i,add;
	add=0x81;
	Write_Ds1302_Byte(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		shijian[i]=Read_Ds1302_Byte(add);  //提取时间

		add=add+2;
	}
	Write_Ds1302_Byte(0x8e,0x80);
}
4、在main函数初始化DS_init函数，并在while函数提取时间参数DS_get
用数码管显示，注意秒、分、时的顺序。
*/
