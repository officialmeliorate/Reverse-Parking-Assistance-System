#include <lpc21xx.h>
#include "header.h"

#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
#define delay                   \
    for (i = 0; i < 65000; i++) \
        ;
				
unsigned int range = 0, i;
u32 flag = 0;
CAN2 RF,DF;
int main()
{
    VPBDIV = 0x01; // PCLK = 60MHz
    IODIR0 = LED1|LED2|LED3;
	
	  can2_init();
    us_init();
    uart0_init(9600);
    config_vic();
    en_CAN_intr();
	
    uart0_tx_string("Reverse Parking Assistance System\r\n");
    while (1)
    {
        if (RF.id==0xAA)
        {
            while (flag == 1)
            {
                uart0_tx_string("Inside loop condn\r\n");
								IOSET0=LED1|LED2|LED3;
								range=get_range();
								IOCLR0=LED1|LED2|LED3;
								DF.id=0xBB;
								DF.rtr=0;  //Data Frame
								DF.dlc=1;
								if (range<50)
								{
									DF.byteA=0xAB;
								}
								else if (range>=50 && range<100)
								{
									DF.byteA=0xCD;
								}
								else if (range>=100 && range<200)
								{
									DF.byteA=0xEF;
								}
								else if (range>=200 && range<300)
								{
									DF.byteA=0xAF;
								}
								can2_tx(DF);
								delay_ms(500);
								
            }
        }
				else{
        flag = 0;
				}
    }
}