#include<reg52.h> //头文件
#include <intrins.h>
#include<ds1302.c>
#include<ds1302.h>
#define uchar unsigned char
#define uint unsigned int
	
void DS_init(void);
void DS_get(void);

uchar code tab1[]={"  :  :  "};		//时间显示的固定字符
uchar code tab2[]={"  :  :    :  :  "};		//闹钟显示的固定字符
sbit LCD_EN=P2^5;   //液晶使能信号
sbit LCD_RS=P2^7;   //数据/命令选择端
sbit LCD_WR=P2^6;
sbit P10=P1^0;
sbit P11=P1^1;
sbit P12=P1^2;
sbit P13=P1^3;
sbit P23=P2^3;
sbit P30=P2^0;
sbit P24=P2^4;
sbit P27=P2^7;
uchar s7=0,s6=0,s4=0,s71=0,mode=0,add1=0,add2=0;
uchar shijian[]={55,59,23,0,0,0,0};
uchar n_shi1=0,n_fen1=0,n_miao1=0;
uchar n_shi2=0,n_fen2=0,n_miao2=5;
uint tt=0,miao=0,i,j;
uchar jia=0,jian=0;
bit shan=0,flag=0,f1=0;


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

void delayms(uint ms)
{
   uint i,j;
	for(i=0;i<ms;i++)
	   for(j=0;j<840;j++);
}


void delay_ms(uint ms)
{
  uint x,y;
  for(x=ms;x>0;x--)
    for(y=110;y>0;y--);
}

void write_com(uchar com)          //命令
{
   LCD_RS=0;        //选择写命令
   P0=com;
   delay_ms(5);
   LCD_EN=1;        //使能信号
   LCD_EN=0;         //关闭使能
}

void write_data(uchar date)          //数据
{
  LCD_RS=1;        //选择写数据
  P0=date;
  delay_ms(5);
  LCD_EN=1;
  LCD_EN=0;
}

void init()
{
  LCD_EN=0;
  write_com(0x38);         //00111000        设置16*2显示，5*7点阵 8为数据接口
  write_com(0x0c);   //00001100        设置开显示，不显示光标
  write_com(0x06);         // 00000110        写一个字符后地址指针加 1
  write_com(0x01);         //00000001        显示清0，数据指针清零
  write_com(0x84);//日历显示固定符号从第一行第1个位置之后开始显示
	for(i=0;i<8;i++)
	{
	write_data(tab1[i]);//向液晶屏写日历显示的固定符号部分
	//delay(3);
	}
	write_com(0x80+0x40);//时间显示固定符号写入位置，从第2个位置后开始显示
	for(j=0;j<16;j++)
	{
	write_data(tab2[j]);//写显示时间固定符号，两个冒号
	//delay(3);	
	}
}

void write_sfm(uchar add,uchar dat)//向LCD写当前时分秒,有显示位置加、现示数据，两个参数
{
	uchar gw,sw;
	gw=dat%10;//取得个位数字
	sw=dat/10;//取得十位数字
	write_com(0x84+add);//er是头文件规定的值0x80+0x40
	write_data(0x30+sw);//数字+30得到该数字的LCD1602显示码
	write_data(0x30+gw);//数字+30得到该数字的LCD1602显示码				
}

void write_nao(uchar add,uchar dat)//向LCD写闹钟时分秒,有显示位置加、现示数据，两个参数
{
	uchar gw,sw;
	gw=dat%10;//取得个位数字
	sw=dat/10;//取得十位数字
	write_com(0xc0+add);//er是头文件规定的值0x80+0x40
	write_data(0x30+sw);//数字+30得到该数字的LCD1602显示码
	write_data(0x30+gw);//数字+30得到该数字的LCD1602显示码				
}

void key_scan()
{
   if(P10==0)
	 {
	   delayms(5);//s7
		 if(P10==0)
		 {
			 if(s4==0){
		   if(s71==0) s71=1;
			 else	if(s71==1) s71=2;
			 else if(s71==2) s71=3;
			 else if(s71==3) s71=0;
			 }
			 else if(s4>0){
				 if(s7==0) s7=1;
			 else	if(s7==1) s7=2;
			 else if(s7==2) s7=3;
			 else if(s7==3) s7=0;
			 }				 
		 }
		 while(!P10);
	 }
   else if(P11==0)
	 {
	   delayms(5);
		 if(P11==0) //s6
		 {
			 jia=1;		 
		 }
		 while(!P11);
	 }
   else if(P12==0)
	 {
	   delayms(5); //s5
		 if(P12==0)
		 {
		    jian=1;//P32=1;
		 }
		 while(!P12);
	 }
	 
	 else if(P13==0)
	 {
	   delayms(5);
		 if(P13==0)//s4
		 {
			 if(s4==0) s4=1;
			 else if(s4==1) s4=2;
			 else if(s4==2) s4=0;
		 } 
		 while(!P13);
	 	 }
  
}

void ban_init(){
	P23=1;P30=1;P24=1;P27=0;
}

void Timer0Init(void)		//100微秒@12.000MHz
{
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	ET0=1;
	EA=1;
	TR0=1;
}


void Timer0(void) interrupt 1
{
	TH0=0XFC;
	TL0=0X18;
	tt++;
	if(tt==1000&&P30==0)
	{
		tt=0;P30=1;
	}
}


void main(void) //主函数
{
	Timer0Init();
	ban_init();
	LCD_WR=0;
	init();  
	DS_init(); 
	while(1){
	DS_get();
	write_sfm(add1,shijian[2]);
	write_sfm(add1+3,shijian[1]);
	write_sfm(add1+6,shijian[0]);
	write_nao(add2,n_shi1);
	write_nao(add2+3,n_fen1);
	write_nao(add2+6,n_miao1);
	write_nao(add2+8,n_shi2);
	write_nao(add2+11,n_fen2);
	write_nao(add2+14,n_miao2);
	key_scan();
	if((shijian[2]==n_shi1)&&(shijian[1]==n_fen1)&&(shijian[0]==n_miao1))
		{
			P23=0;P24=0;f1=1;P30=0;tt=0;
		}
	if(((shijian[2]==n_shi2)&&(shijian[1]==n_fen2)&&(shijian[0]==n_miao2)&&(f1==1))){
			f1=0;P23=1;P30=0;P24=1;tt=0;
		}
	if(s71==1){
		if(shijian[0]%2==0){
		write_com(0x84);write_data(0x20);
		write_com(0x85);write_data(0x20);
		}
		if(jia==1){
			jia=0;
			if(shijian[2]==23) shijian[2]=0;
			else shijian[2]++;DS_init();
			}
		if(jian==1){
			jian=0;
			if(shijian[2]==0) shijian[2]=23;
			else shijian[2]--;DS_init();
			}
	 }
	else if(s71==2){
		if(shijian[0]%2==0){
		write_com(0x87);write_data(0x20);
		write_com(0x88);write_data(0x20);
		}
		if(jia==1){
				jia=0;
				if(shijian[1]==59) shijian[1]=0;
				else shijian[1]++;DS_init();
			}
			if(jian==1){
				jian=0;
				if(shijian[1]==0) shijian[1]=59;
				else shijian[1]--;DS_init();
			}
	 }
	else if(s71==3){
		if(shijian[0]%2==0){
		write_com(0x8a);write_data(0x20);
		write_com(0x8b);write_data(0x20);
		}
		if(jia==1){
				jia=0;
				if(shijian[0]==59) shijian[0]=0;
				else shijian[0]++;DS_init();
			}
			if(jian==1){
				jian=0;
				if(shijian[0]==0) shijian[0]=59;
				else shijian[0]--;DS_init();
			}
	  }
	 if(s4==1){
			if(s7==1){
				if(shijian[0]%2==0){
				write_com(0xc0);write_data(0x20);
				write_com(0xc1);write_data(0x20);
				}
				if(jia==1){
					jia=0;
					if(n_shi1==23) n_shi1=0;
					else n_shi1=n_shi1+1;
				}
				if(jian==1){
					jian=0;
					if(n_shi1==0) n_shi1=23;
					else n_shi1--;
				}
			}
			else if(s7==2){
				if(shijian[0]%2==0){
				write_com(0xc3);write_data(0x20);
				write_com(0xc4);write_data(0x20);
				}
				if(jia==1){
					jia=0;
					if(n_fen1==59) n_fen1=0;
					else n_fen1++;
				}
				if(jian==1){
					jian=0;
					if(n_fen1==0) n_fen1=59;
					else n_fen1--;
				}	
			}
			else if(s7==3){
				if(shijian[0]%2==0){
				write_com(0xc6);write_data(0x20);
				write_com(0xc7);write_data(0x20);
				}
				if(jia==1){
				jia=0;
					if(n_miao1==59) n_miao1=0;
					else n_miao1++;
				}
				if(jian==1){
					jian=0;
					if(n_miao1==0) n_miao1=59;
					else n_miao1--;
				}	
		  }
		 }
		 else if(s4==2){
			if(s7==1){
				if(shijian[0]%2==0){
				write_com(0xc8);write_data(0x20);
				write_com(0xc9);write_data(0x20);
				}
				if(jia==1){
					jia=0;
					if(n_shi2==23) n_shi2=0;
					else n_shi2++;
				}
				if(jian==1){
					jian=0;
					if(n_shi2==0) n_shi2=23;
					else n_shi2--;
				}
			}
			else if(s7==2){
				if(shijian[0]%2==0){
				write_com(0xcb);write_data(0x20);
				write_com(0xcc);write_data(0x20);
				}
				if(jia==1){
					jia=0;
					if(n_fen2==59) n_fen2=0;
					else n_fen2++;
				}
				if(jian==1){
					jian=0;
					if(n_fen2==0) n_fen2=59;
					else n_fen2--;
				}	
			}
			else if(s7==3){
				if(shijian[0]%2==0){
				write_com(0xce);write_data(0x20);
				write_com(0xcf);write_data(0x20);
				}
				if(jia==1){
				jia=0;
					if(n_miao2==59) n_miao2=0;
					else n_miao2++;
				}
				if(jian==1){
					jian=0;
					if(n_miao2==0) n_miao2=59;
					else n_miao2--;
				}	
		  }
		}
	}
}