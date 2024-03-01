#include <lpc21xx.h>
#include "header.h"
extern u32 flag;
extern CAN2 RF;

void CAN_Handler(void) __irq
{
	RF.id=C2RID;
	RF.dlc=(C2RFS>>16)&0xF;
	RF.rtr=(C2RFS>>30)&1;
	if(RF.rtr==0)
	{
		RF.byteA=C2RDA;
		RF.byteB=C2RDB;
	}
	C2CMR|=4;
	if (RF.id==0xAA)
	flag=!flag;
	VICVectAddr=0;
	}

void config_vic (void)
{
	VICIntSelect=0;
	VICVectCntl0=27|(1<<5);
	VICVectAddr0=(int)CAN_Handler;
	VICIntEnable|=(1<<27);
	C2CMR &= ~(0x6);
}

void en_CAN_intr (void)
{
	C2IER=1;
}