#include<reg51.h>
sbit P00=P0^0;sbit P01=P0^1;sbit P02=P0^2;sbit P03=P0^3;sbit P04=P0^4;sbit P05=P0^5;sbit P06=P0^6;
sbit P10=P1^0;sbit P11=P1^1;sbit P12=P1^2;sbit P13=P1^3;sbit P14=P1^4;sbit P15=P1^5;sbit P16=P1^6;
sbit P20=P2^0;sbit P21=P2^1;sbit P22=P2^2;sbit P23=P2^3;sbit P24=P2^4;sbit P25=P2^5;sbit P26=P2^6;
sbit P30=P3^0;sbit P31=P3^1;sbit P32=P3^2;sbit P33=P3^3;sbit P34=P3^4;sbit P35=P3^5;sbit P36=P3^6;
sbit P17=P1^7;sbit P07=P0^7;sbit P27=P2^7;sbit P37=P3^7;
void delayms();//paomadeng
void main()
{
	while(2)
	{
//		unsigned char light1=0x01,light2=0x01,light3=0x01,light4=0x01;
//		P10=0;P14=0;P33=0;P37=0;P00=0;P04=0;P20=0;P24=0;delayms();//模式行行灯
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P11=0;P15=0;P32=0;P36=0;P01=0;P05=0;P21=0;P25=0;delayms();
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P12=0;P16=0;P31=0;P35=0;P02=0;P06=0;P22=0;P26=0;delayms();
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P13=0;P17=0;P30=0;P34=0;P03=0;P07=0;P23=0;P27=0;delayms();
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P13=0;P17=0;P30=0;P34=0;P03=0;P07=0;P27=0;P23=0;delayms();//模式交叉灯
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P14=0;P15=0;P16=0;P17=0;P30=0;P31=0;P32=0;P33=0;P04=0;P05=0;P06=0;P07=0;P27=0;P26=0;P25=0;P24=0;delayms();
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P10=P11=P12=P13=P17=P30=P34=P35=P36=P37=0;P00=P01=P02=P03=P07=P27=P23=P22=P21=P20=0;delayms();
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P13=0;delayms();P13=1;delayms();//区域灯
//		P1=0X00;delayms();P1=~0X00;delayms();
//		P1=0X00;P3=0X00;delayms();P1=~0X00;P3=~0X00;delayms();
//		P1=0X00;P0=0X00;P2=0X00;P3=0X00;delayms();P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
//		P13=0;delayms();P12=0;delayms();P11=0;delayms();P10=0;delayms();//模式蛇形灯
//		P00=0;delayms();P01=0;delayms();P02=0;delayms();P03=0;delayms();	
//		P07=0;delayms();P06=0;delayms();P05=0;delayms();P04=0;delayms();
//		P14=0;delayms();P15=0;delayms();P16=0;delayms();P17=0;delayms();
//		P30=0;delayms();P31=0;delayms();P32=0;delayms();P33=0;delayms();
//		P24=0;delayms();P25=0;delayms();P26=0;delayms();P27=0;delayms();
//    P23=0;delayms();P22=0;delayms();P21=0;delayms();P20=0;delayms();
//		P37=0;delayms();P36=0;delayms();P35=0;delayms();P34=0;delayms();		
//		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
      P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
	}
}

void delayms()
{
	unsigned int i,j;
	for(i=0;i<600;i++)
		for(j=0;j<100;j++);
}
