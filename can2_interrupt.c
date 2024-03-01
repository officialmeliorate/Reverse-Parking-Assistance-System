/* External interrupt is assigned to Switch */

#include <lpc21xx.h>
#include "header.h"
#define SW ((IOPIN0>>14)&1)
extern CAN2 DF,RF;
extern u32 flag;

void CAN_Handler(void) __irq
{
	uart0_tx_string("Interrupted\r\n");   //CAN Receiver Code
	DF.id=C2RID;
	DF.dlc=(C2RFS>>16)&0xF;
	DF.rtr=(C2RFS>>30)&1;
	if(DF.rtr==0) //if dataframe
	{
		DF.byteA=C2RDA;
		DF.byteB=C2RDB;
		uart0_tx_integer(DF.byteA);
	}
	C2CMR|=4; //For releasing receiver buffer
	VICVectAddr=0;
	}

__irq void SW1_INT (void)
{
	while (SW==1);
	flag=!flag;
	can2_tx(RF);
	 EXTINT |= 0x6;  
	 VICVectAddr = 0;
}

void config_vic (void)
{
	VICIntSelect=0;
	VICVectCntl0=27|(1<<5);  //CAN2 interrupt no is 27
	VICVectAddr0=(int)CAN_Handler;
	VICIntEnable|=(1<<27);
	C2CMR &= ~(0x6);
	
  EXTMODE = 0x6;  
  EXTPOLAR &= ~(0x6);
  PINSEL0 |= 0xA0000000;
  
  VICIntSelect &= ~(1<<15);            // EINT2 selected as IRQ 16 and EINT1 as IRQ 15
  VICVectAddr5 = (unsigned int) SW1_INT;
  VICVectCntl5 = (1<<5) | 15;
  VICIntEnable = (1<<15);
  EXTINT &= ~(0x6);
}

void en_CAN_intr (void)
{
	C2IER=1;
}

