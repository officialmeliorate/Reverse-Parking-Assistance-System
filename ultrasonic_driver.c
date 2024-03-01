//Ultrasonic Sensor Driver

#include <LPC21xx.h>
#include "header.h"
#define trig (1<<8)             //P0.8
#define echo (IO0PIN&(1<<9)) //P0.9 as EINT3


void us_init()
{
    IO0DIR|=(1<<8);
    T0TCR=0;
    T0PR=59;
}
void send_pulse()
{
    T0TC=0;
	  T0PC=0;
    IO0SET=trig;                            //trig=1
    delay_ms(10);                        //10us delay
    IO0CLR=trig;                            //trig=0
}
unsigned int get_range()
{
    unsigned int get=0;
    send_pulse();
    while(!echo);
    T0TCR=0x01;
    while(echo);
    T0TCR=0;
    get=T0TC;
	if(get<38000)     //UltraSonic Sensor Range: 0 to 644(38k/59=644)
        get=get/59;  //Finding range in centimetres
    else
        get=0;
    return get;
}
