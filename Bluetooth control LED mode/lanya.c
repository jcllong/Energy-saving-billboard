#include <reg52.h>

sbit P00=P0^0;sbit P01=P0^1;sbit P02=P0^2;sbit P03=P0^3;sbit P04=P0^4;sbit P05=P0^5;sbit P06=P0^6;
sbit P10=P1^0;sbit P11=P1^1;sbit P12=P1^2;sbit P13=P1^3;sbit P14=P1^4;sbit P15=P1^5;sbit P16=P1^6;
sbit P20=P2^0;sbit P21=P2^1;sbit P22=P2^2;sbit P23=P2^3;sbit P24=P2^4;sbit P25=P2^5;sbit P26=P2^6;
sbit P30=P3^0;sbit P31=P3^1;sbit P32=P3^2;sbit P33=P3^3;sbit P34=P3^4;sbit P35=P3^5;sbit P36=P3^6;
sbit P17=P1^7;sbit P07=P0^7;sbit P27=P2^7;sbit P37=P3^7;

unsigned char flag=0,mode=0;
bit led=0;

void delayms();//paomadeng

void UartInit()		//9600bps@11.0592MHz
{
    SCON = 0x50; // SCON: 模式1, 8-bit UART, 使能接收
    TMOD |= 0x20;
    TH1 = 0xfd; //波特率9600 初值
    TL1 = 0xfd;
    TR1 = 1;
    EA = 1; //打开总中断
    ES = 1; //打开串口中断
}


void send(unsigned char dat)	//通过串口发送到蓝牙模块上，蓝牙模块发送出去一个字节的字符
{
	ES = 0;
	SBUF = dat;
	while (!TI);
	TI = 0;
	ES = 1;
}

/*发送数据*/

void send_str(unsigned char * str)	//通过蓝牙模块发送一个字符串
{
	while (*str != '\0')
		send(*str++);
}

void delayms()
{
	unsigned int i,j;
	for(i=0;i<600;i++)
		for(j=0;j<100;j++);
}

void lanya_panduan()
{
	if(flag == 0)		//判断灯目前是否关了
	{
		led = 0;	//状态灯灭
		send_str("lock successfully!\n");  //发送字符串
	}
	
	if(flag == 1)			//判断反转
	{
  	  led = 1;			//状态灯亮
	}
}

void Usart() interrupt 4			//中断服务函数
{
    unsigned char n; //定义临时变量
    if(RI) //判断是接收中断产生
    {
        RI = 0; //标志位清零
        n = SBUF; //读入缓冲区的值
        switch(n)
        {
					case'0':		//控制正转
						mode = 0;
					break;
					
					case'1':		//控制反转
						mode = 1;
					break;
					
					case'2':		//控制速度为慢
						mode = 2;
					break;
					
					case'3':		//控制速度为中等
						mode = 3;
					break;
        }
        TI = 1;
        SBUF = n; //把接收到的值再发回
    }
   		if(TI) //如果是发送标志位，清零
        TI = 0;
}

void led_mode(){
	unsigned char light1=0x01,light2=0x01,light3=0x01,light4=0x01;
	if(mode==0){
		P10=0;P14=0;P33=0;P37=0;P00=0;P04=0;P20=0;P24=0;delayms();//模式行行灯
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
		P11=0;P15=0;P32=0;P36=0;P01=0;P05=0;P21=0;P25=0;delayms();
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
		P12=0;P16=0;P31=0;P35=0;P02=0;P06=0;P22=0;P26=0;delayms();
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
		P13=0;P17=0;P30=0;P34=0;P03=0;P07=0;P23=0;P27=0;delayms();
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
	}
	if(mode==1){
		P13=0;P17=0;P30=0;P34=0;P03=0;P07=0;P27=0;P23=0;delayms();//模式交叉灯
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
		P14=0;P15=0;P16=0;P17=0;P30=0;P31=0;P32=0;P33=0;P04=0;P05=0;P06=0;P07=0;P27=0;P26=0;P25=0;P24=0;delayms();
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
		P10=P11=P12=P13=P17=P30=P34=P35=P36=P37=0;P00=P01=P02=P03=P07=P27=P23=P22=P21=P20=0;delayms();
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
	}
	if(mode==2){
		P13=0;delayms();P13=1;delayms();//区域灯
		P1=0X00;delayms();P1=~0X00;delayms();
		P1=0X00;P3=0X00;delayms();P1=~0X00;P3=~0X00;delayms();
		P1=0X00;P0=0X00;P2=0X00;P3=0X00;delayms();P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
	}
	if(mode==3){
		P13=0;delayms();P12=0;delayms();P11=0;delayms();P10=0;delayms();//模式蛇形灯
		P00=0;delayms();P01=0;delayms();P02=0;delayms();P03=0;delayms();	
		P07=0;delayms();P06=0;delayms();P05=0;delayms();P04=0;delayms();
		P14=0;delayms();P15=0;delayms();P16=0;delayms();P17=0;delayms();
		P30=0;delayms();P31=0;delayms();P32=0;delayms();P33=0;delayms();
		P24=0;delayms();P25=0;delayms();P26=0;delayms();P27=0;delayms();
    P23=0;delayms();P22=0;delayms();P21=0;delayms();P20=0;delayms();
		P37=0;delayms();P36=0;delayms();P35=0;delayms();P34=0;delayms();		
		P1=~0X00;P0=~0X00;P2=~0X00;P3=~0X00;delayms();
	}
}

void main()
{
    UartInit();
    while(1)
    {
    	lanya_panduan();
			led_mode();
    }
}