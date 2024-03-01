extern void delay_sec(unsigned int);
extern void delay_ms(unsigned int);

extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_integer(int);
extern void lcd_float(float,int);

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;

extern void uart0_init(u32);
extern void uart0_tx(u8);
extern void uart0_tx_string(s8 *);
extern void uart0_rx_string(s8* , s32);
extern u8 uart0_rx(void);
extern void uart0_tx_integer(s32);
extern void uart0_tx_float(float);
extern void uart0_ascii(u8 temp);
#include<stdio.h>
extern void uart0_hex(s32);

typedef struct CAN2_MSG
{
	u32 id;
	u32 dlc;
	u32 rtr;
	u32 byteA;
	u32 byteB;
}CAN2;

extern void can2_init (void);
extern void can2_tx (CAN2 m1);
extern void can2_rx (CAN2 *);

extern void config_vic (void);
extern void en_CAN_intr (void);

