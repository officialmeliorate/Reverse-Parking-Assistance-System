//Delay_Driver_Code

//Here we are using Timer1(T1) in LPC2129

#include<lpc21xx.h>

//////For Seconds Delay//////
void delay_sec(unsigned int sec)
{
	int a[]={15,60,30,0,15};
	unsigned int pclk=0;
	/*if(VPBDIV==3)
		lcd_string("Error");*/
	pclk=a[VPBDIV]*1000000;
	T1PC=0;
	T1PR=pclk-1;
	T1TC=0;
	T1TCR=1;
	while(T1TC<sec);
	T1TCR=0;
}	


//////For Milli-seconds Delay//////
void delay_ms(unsigned int ms)
{
	int a[]={15,60,30,0,15};
	unsigned int pclk=0;
	/*if(VPBDIV==3)
		lcd_string("Error");*/
	pclk=a[VPBDIV]*1000;
	T1PC=0;
	T1PR=pclk-1;
	T1TC=0;
	T1TCR=1;
	while(T1TC<ms);
	T1TCR=0;
}	
