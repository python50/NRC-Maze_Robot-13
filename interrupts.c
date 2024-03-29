/******************************************************************************/
/*Files to Include                                                            */
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
#include "stdlib.h"
#include "stdio.h"
#endif

#include "user.h"
#include "motor.h"
#include "maze.h"
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */

#if defined(__XC) || defined(HI_TECH_C)
void interrupt high_isr(void)
#elif defined (__18CXX)
#pragma code high_isr=0x08
#pragma interrupt high_isr
void high_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif

{
	/* This code stub shows general interrupt handling.  Note that these
	conditional statements are not handled within 3 seperate if blocks.
	Do not use a seperate if block for each interrupt flag to avoid run
	time errors. */


	/* TODO Add High Priority interrupt routine code here. */

	/* Determine which flag generated the interrupt */
	if (TMR1IF)
	{
		TMR1IF=0; /* Clear Interrupt Flag 1 */
		
		TMR1H=0xFF;
		TMR1L=0x00;

		if (SPEAKER)
			SPEAKER=0;

		motor_interupt();
		motor_enc_interupt();

		static unsigned int i=0;
		i++;

		#define S_TICK	(62500/10)
		if (i==S_TICK)
		{
			i=0;
			asm("nop");
			systick++;
			asm("nop");
			maze.started=1;
			asm("nop");
			PORTAbits.RA0=1;
			asm("nop");
		}

	} else if (TMR2IF)
	{
		TMR2IF=0; /* Clear Interrupt Flag 1 */

	}


}

/* Low-priority interrupt routine */
#if defined(__XC) || defined(HI_TECH_C)
void low_priority interrupt low_isr(void)
#elif defined (__18CXX)
#pragma code low_isr=0x18
#pragma interruptlow low_isr
void low_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif
{

	/* This code stub shows general interrupt handling.  Note that these
	conditional statements are not handled within 3 seperate if blocks.
	Do not use a seperate if block for each interrupt flag to avoid run
	time errors. */

#if 0

	/* TODO Add Low Priority interrupt routine code here. */

	/* Determine which flag generated the interrupt */
	if (<Interrupt Flag 1 >)
	{
		<Interrupt Flag 1=0 >; /* Clear Interrupt Flag 1 */
	} else if (<Interrupt Flag 2 >)
	{
		<Interrupt Flag 2=0 >; /* Clear Interrupt Flag 2 */
	} else
	{
		/* Unhandled interrupts */
	}

#endif

}
