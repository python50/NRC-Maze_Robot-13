/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "system.h"
#include "user.h"
#include <stdio.h>

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

unsigned long systick=0;

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
	//Right Sonic
	//RA2
	TRISA=0b00000100;

	//JP1 & JP2
	TRISB=0b00110000;

	//enable RX TX drive
	//RC6 & 7
	TRISC=0b11000000;
	//Front Sonic
	//RD2
	//Left Sonic
	//RD7
	// Enc A and B
	//RD0 & 1
	TRISD=0b10000111;

	//RIGHT sonic
	//RE1
	TRISE=0b00000010;

	ANSELA=0;
	ANSELB=0;
	ANSELC=0;
	ANSELD=0;
	ANSELE=0;

	PORTA=0;
	PORTB=0;
	PORTC=0;
	PORTD=0;
	PORTE=0;

	init_uart();
	
	#define ESCAPE_CHAR "\x1B"
	printf("%s[2JBOOTING...%s", ESCAPE_CHAR,ENDL);

	init_sonic_timer();
	init_motor_timer();
	//init_motor_enc_timer();

	//enable interupts
	GIE=1;
	PEIE=1;
}

void init_uart()
{
	//9600 baud
	//25-16mhz
	//103-64mhz
	SPBRG1=103;
	SPEN1=1;
	TXEN1=1;
	CREN1=1;
}

void init_sonic_timer()
{
	/*configure timer for a 1us period
	 16mhz
	 div 4 (prescaler)
	 div 4 (instruction clock)
	 =1Mhz*/
	TMR0ON=0;
	T08BIT=0;
	T0CS=0;
	PSA=0;
	T0PS0=1;
	T0PS1=0;
	T0PS2=0;
}
void start_sonic_timer()
{
	//Stop timer
	TMR0ON=0;
	//Clear hardware counter
	TMR0H=0;
	TMR0L=0;
	//start timer
	TMR0ON=1;
}

unsigned int stop_sonic_timer()
{
	unsigned int value;
	value=TMR0L;
	value+=TMR0H<<8;
	return value;
}

void init_motor_timer()
{
	/*Timer 1 - motor control
	 16 bit at 16mhz
	 no prescaler
	 62500 hertz
	 */

	TMR1ON=1;

	TMR1IE=1;
}


void init_motor_enc_timer()
{
	T2CKPS0=1;
	T2CKPS1=1;

	TMR2IE=1;
	TMR2ON=1;
}



void beep(char tone)
{
	#define TMULTI (50)

	for(char i=0;i < 200;i++)
	{
		SPEAKER=~SPEAKER;
		for(char j=0;j < TMULTI*tone;j++);
	}
}

void beep_message(char m)
{
	for(char c=0;c < m;c++)
	{
		beep(5);
		for(char i=0xFF-100;i;i++)
			__delay_ms(1);
	}
}



void putch(char c)
{
	while(!TRMT1){}
	TXREG=c;
}

char getche()
{

	while (!RC1IF) {
	}

	char value=RCREG1;
	putch(value);

	return value;
}

void sys_delay_ms(unsigned long ticks)
{
	unsigned long old=systick+ticks;
	while (old > systick) { }
}