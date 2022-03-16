#include<reg52.h> //ͷ�ļ�
#include <intrins.h>
#include<ds1302.c>
#include<ds1302.h>
#define uchar unsigned char
#define uint unsigned int
	
void DS_init(void);
void DS_get(void);

uchar code tab1[]={"  :  :  "};		//ʱ����ʾ�Ĺ̶��ַ�
uchar code tab2[]={"  :  :    :  :  "};		//������ʾ�Ĺ̶��ַ�
sbit LCD_EN=P2^5;   //Һ��ʹ���ź�
sbit LCD_RS=P2^7;   //����/����ѡ���
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
  shijian[i]=Read_Ds1302_Byte(add);  //��ȡʱ��

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

void write_com(uchar com)          //����
{
   LCD_RS=0;        //ѡ��д����
   P0=com;
   delay_ms(5);
   LCD_EN=1;        //ʹ���ź�
   LCD_EN=0;         //�ر�ʹ��
}

void write_data(uchar date)          //����
{
  LCD_RS=1;        //ѡ��д����
  P0=date;
  delay_ms(5);
  LCD_EN=1;
  LCD_EN=0;
}

void init()
{
  LCD_EN=0;
  write_com(0x38);         //00111000        ����16*2��ʾ��5*7���� 8Ϊ���ݽӿ�
  write_com(0x0c);   //00001100        ���ÿ���ʾ������ʾ���
  write_com(0x06);         // 00000110        дһ���ַ����ַָ��� 1
  write_com(0x01);         //00000001        ��ʾ��0������ָ������
  write_com(0x84);//������ʾ�̶����Ŵӵ�һ�е�1��λ��֮��ʼ��ʾ
	for(i=0;i<8;i++)
	{
	write_data(tab1[i]);//��Һ����д������ʾ�Ĺ̶����Ų���
	//delay(3);
	}
	write_com(0x80+0x40);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
	for(j=0;j<16;j++)
	{
	write_data(tab2[j]);//д��ʾʱ��̶����ţ�����ð��
	//delay(3);	
	}
}

void write_sfm(uchar add,uchar dat)//��LCDд��ǰʱ����,����ʾλ�üӡ���ʾ���ݣ���������
{
	uchar gw,sw;
	gw=dat%10;//ȡ�ø�λ����
	sw=dat/10;//ȡ��ʮλ����
	write_com(0x84+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
	write_data(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
	write_data(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��				
}

void write_nao(uchar add,uchar dat)//��LCDд����ʱ����,����ʾλ�üӡ���ʾ���ݣ���������
{
	uchar gw,sw;
	gw=dat%10;//ȡ�ø�λ����
	sw=dat/10;//ȡ��ʮλ����
	write_com(0xc0+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
	write_data(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
	write_data(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��				
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

void Timer0Init(void)		//100΢��@12.000MHz
{
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
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


void main(void) //������
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