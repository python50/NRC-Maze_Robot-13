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

#include "sonic.h"
#include "system.h"
#include "user.h"

unsigned int ping_convert(unsigned int value)
{
	return value / 60 + 4;
}

unsigned int ping_front()
{
	unsigned int value=p_front();
#ifdef USE_SONIC_AVERAGE
	for(char i=0;i!=PING_AVERAGE;i++)
		value=(value+p_front())/2;
#endif
	return value;
}

unsigned int p_front()
{
	unsigned int value=0;

	FRONT_TRIGGER=1;
	__delay_us(15);
	FRONT_TRIGGER=0;

	unsigned int i=SONIC_TIMEOUT;
	while (!FRONT_ECHO && i++)
	{
	}
	start_sonic_timer();
	i=SONIC_TIMEOUT;
	while (FRONT_ECHO && i++)
	{
	}

	value=stop_sonic_timer();

	return ping_convert(value);
}

unsigned int ping_lf()
{
	unsigned int value=p_lf();
#ifdef USE_SONIC_AVERAGE
	for(char i=0;i!=PING_AVERAGE;i++)
		value=(value+p_lf())/2;
#endif
	return value;
}

unsigned int p_lf()
{

	unsigned int value=0;

	LF_TRIGGER=1;
	__delay_us(15);
	LF_TRIGGER=0;


	unsigned int i=SONIC_TIMEOUT;
	while (!LF_ECHO && i++)
	{
	}
	start_sonic_timer();
	i=SONIC_TIMEOUT;
	while (LF_ECHO && i++)
	{
	}

	value=stop_sonic_timer();

	return ping_convert(value);
}


unsigned int ping_lb()
{
	unsigned int value=p_lb();
#ifdef USE_SONIC_AVERAGE
	for(char i=0;i!=PING_AVERAGE;i++)
		value=(value+p_lb())/2;
#endif
	return value;
}

unsigned int p_lb()
{

	unsigned int value=0;

	LB_TRIGGER=1;
	__delay_us(15);
	LB_TRIGGER=0;


	unsigned int i=SONIC_TIMEOUT;
	while (!LB_ECHO && i++)
	{
	}
	start_sonic_timer();
	i=SONIC_TIMEOUT;
	while (LB_ECHO && i++)
	{
	}
	value=stop_sonic_timer();

	return ping_convert(value);
}

unsigned int ping_right()
{
	unsigned int value=p_right();
#ifdef USE_SONIC_AVERAGE
	for(char i=0;i!=PING_AVERAGE;i++)
		value=(value+p_right())/2;
#endif
	return value;
}

unsigned int p_right()
{

	unsigned int value=0;

	RIGHT_TRIGGER=1;
	__delay_us(15);
	RIGHT_TRIGGER=0;

	//THIS IS A POTENTIAL TRAP !!!
	unsigned int i=SONIC_TIMEOUT;
	while (!RIGHT_ECHO && i++)
	{
	}
	start_sonic_timer();
	i=SONIC_TIMEOUT;
	while (RIGHT_ECHO && i++)
	{
	}
	value=stop_sonic_timer();

	return ping_convert(value);
}

void sonic_test()
{
	for (char i=0; i != 1; i++)
	{
		ping_lf();
		ping_lb();
		ping_front();
		ping_right();
	}

}