#include"header.h"
#include<lpc21xx.h>
#include<math.h>
#define RS 1<<17
#define RW 1<<18
#define EN 1<<19

void lcd_data(unsigned char data)
{
	IOCLR1=0x00FE0000;
	unsigned int temp;
	temp=(data&0xF0)<<16;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
	
	
	IOCLR1=0x00FE0000;
	temp=(data&0x0F)<<20;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;	
}
void lcd_cmd(unsigned char cmd)
{
	
	IOCLR1=0x00FE0000;
	unsigned int temp;
	temp=(cmd&0xF0)<<16;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
	
	
	IOCLR1=0x00FE0000;
	temp=(cmd&0x0F)<<20;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	delay_ms(2);
	IOCLR1=EN;
}

void lcd_init(void)
{
	IODIR1|=0x00FE0000;
	PINSEL2=0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x028);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
}

void lcd_string(char *ptr)
{
	while(*ptr != 0)
	{
		lcd_data(*ptr);
		ptr++;
		delay_ms(50);
	}
}
void lcd_integer(int num)
{
	int a[10],i=0;
	if(num==0)
		lcd_data('0');
	if(num<0)
	{
		lcd_data('-');
		num=-num;
	}
	while(num>0)
	{
		a[i]=num%10+48;
		num/=10;
		i++;
	}
	for(--i ; i>=0 ; i--)
	{
		lcd_data(a[i]);
	}
}
void lcd_float(float f,int places)
{
	int num1,a[10];
	int num=f;
	lcd_integer(num);
	lcd_data('.');
	num1=((f-num)*(pow(10,places)));
	lcd_integer(num1);
}
int a[]={0x17,0x14,0x14,0x1F,0x05,0x05,0x1D,0x00};
void cgram_init(void)
{
	lcd_cmd(0x40);
	for(int i=0 ; i<=7 ; i++)
	{
		lcd_data(a[i]);
	}
}
