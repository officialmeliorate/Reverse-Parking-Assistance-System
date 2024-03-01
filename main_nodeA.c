#include <lpc21xx.h>
#include "header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
#define BUZ (1<<21)
#define SW ((IOPIN0>>14)&1)
#define delay                   \
    for (i = 0; i < 65000; i++) \
        ;
u32 flag = 0;
//Assuming RF->Remote frame(Transmitting from Node A to B)
//Assuming DF->Remote frame(Transmitting from Node A to B)  TN--->DF
CAN2 RF,DF;  
int main()
{
    VPBDIV = 0x01; // PCLK = 60MHz
    //IODIR1 = 0xffffffff;
		IODIR0=LED1|LED2|LED3|BUZ;
	
    
    can2_init();
		uart0_init(9600);
		//lcd_init();
	
		//lcd_cmd(0x80);
		//lcd_string("Reverse Parking");
		//lcd_cmd(0xC0);
		//lcd_string("Assist System");
		//delay_ms(10);
	
    config_vic();
    en_CAN_intr();
	
		RF.id=0xAA;
		RF.rtr=1; //Remote Frame
		RF.dlc=1;
	
		IOSET0=LED1|LED2|LED3|BUZ;
    uart0_tx_string("Reverse Parking Assistance System\r\n");
	
    while (1)
    {
					switch (DF.byteA)
					{
						case 0xAB:
							
							if (flag==1)
							{
								uart0_tx_string("Range Less Than 50cm");
								//lcd_string("Range <50cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
							}
							else if (flag==0)
							IOSET0=LED1|LED2|LED3|BUZ;
							break;
							
						case 0xCD:
							
							if (flag==1)
							{
								/*During board connection uncommentthe below code
								
								uart0_tx_string("Range b/w 50cm & 100cm");
								lcd_string("Range 50-100 cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
								delay_ms(100);
								IOSET0=LED1|LED2|LED3|BUZ;
								delay_ms(100);*/
								
								uart0_tx_string("Range b/w 50cm & 100cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
								//delay_ms(10);
								IOSET0=LED1|LED2|LED3|BUZ;
								//delay_ms(10);
							}
							else if (flag==0)
							IOSET0=LED1|LED2|LED3|BUZ;
							break;

							
						case 0xEF:
							
							if (flag==1)
							{
								/*uart0_tx_string("Range b/w 100cm & 200cm");
								lcd_string("Range 100-200 cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
								delay_ms(500);
								IOSET0=LED1|LED2|LED3|BUZ;
								delay_ms(500);*/
								
								uart0_tx_string("Range b/w 100cm & 200cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
								//delay_ms(20);
								IOSET0=LED1|LED2|LED3|BUZ;
								//delay_ms(20);
							}
							else if (flag==0)
							IOSET0=LED1|LED2|LED3|BUZ;
							break;
							
						case 0xAF:
							
							if (flag==1)
							{
								/*uart0_tx_string("Range b/w 200cm & 300cm");
								lcd_string("Range 100-200 cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
								delay_sec(1);
								IOSET0=LED1|LED2|LED3|BUZ;
								delay_sec(1);*/
								
								uart0_tx_string("Range b/w 200cm & 300cm");
								IOCLR0=LED1|LED2|LED3|BUZ;
								//delay_sec(30);
								IOSET0=LED1|LED2|LED3|BUZ;
								//delay_sec(30);
							}
							else if (flag==0)
							IOSET0=LED1|LED2|LED3|BUZ;
							break;
							
						default:
							if (flag==1|flag==0)
							{
							IOSET0=LED1|LED2|LED3|BUZ;
							}		
				}
			}
		}
							
	
		