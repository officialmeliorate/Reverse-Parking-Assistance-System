//uart0 driver

#include"header.h"
#include<lpc21xx.h>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(unsigned int baud)
{
	int a[]={15,60,30,0,15};
	unsigned int pclk=a[VPBDIV]*1000000;
	unsigned int result=0;
	result=pclk/16*baud;
	
	PINSEL0|=0x5;
	U0LCR=0X83;
	U0DLL=result&0xFF;
	U0DLM=(result>>8)&0xFF;
	U0LCR=0X03;
}

void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(s8 *ptr)
{
	while(*ptr != 0)
	{
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}
}

void uart0_rx_string(s8 *ptr,s32 max_bytes)
{
	s32 i;
	for(i=0 ; i<max_bytes ; i++)
	{
		while(RDR == 0);
		ptr[i]=U0RBR;
		if(ptr[i]=='\r')
			break;
	}
	ptr[i]='\0';
}

u8 uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_integer(s32 num)
{
	u8 a[25],i=0;
	if(num==0)
		uart0_tx('0');
	if(num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	while(num>0)
	{
		a[i]=num%10;
		num/=10;
		i++;
	}
	for(i--; a[i] ; i--)
		uart0_tx(a[i]+48);
}

void uart0_tx_float(float num)
{
	u32 i,j;
	if(num==0)
		uart0_tx('0');
	if(num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	i=num;
	uart0_tx_integer(i);
	j=(num-i)*1000000;
	uart0_tx('.');
	uart0_tx_integer(j);
	
}

void uart0_hex(s32 num)
{
	s8 buf[10];
	sprintf(buf,"%X",num);
	uart0_tx_string(buf);
}

void uart0_ascii(u8 temp)
{
	uart0_tx((temp/100)+48);
	uart0_tx(((temp/10)%10)+48);
	uart0_tx((temp%10)+48);
}
