/*
  ����˵��: DS1302��������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include <reg52.h>
#include <intrins.h>

sbit SCK=P1^6;		
sbit SDA=P1^5;		
sbit RST = P1^7;   // DS1302��λ												

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
ds1302����������
1����������#include<ds1302.h>��#include<ds1302.c>
2���ڳ������������:
uchar shijian[]={**,**,**,0,0,0,0};//��-��-ʱ,��-��-����-��
3���ڳ������������к�����
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
		shijian[i]=Read_Ds1302_Byte(add);  //��ȡʱ��

		add=add+2;
	}
	Write_Ds1302_Byte(0x8e,0x80);
}
4����main������ʼ��DS_init����������while������ȡʱ�����DS_get
���������ʾ��ע���롢�֡�ʱ��˳��
*/
