/* 
 * File:   sonic.h
 * Author: jason
 *
 * Created on March 13, 2013, 7:56 PM
 */

#ifndef SONIC_H
#define	SONIC_H

#include "system.h"
#include "user.h"
#include "stdio.h"

#define FRONT_TRIGGER	(PORTDbits.RD3)
#define FRONT_ECHO	(PORTDbits.RD2)
#define LF_TRIGGER	(PORTDbits.RD6)
#define LF_ECHO		(PORTDbits.RD7)
#define LB_TRIGGER	(PORTAbits.RA1)
#define LB_ECHO		(PORTAbits.RA2)

#define RIGHT_TRIGGER	(PORTEbits.RE0)
#define RIGHT_ECHO	(PORTEbits.RE1)

//pings 1 plus PING_AVERAGE times

//SONIC_TIMEOUT MAY NOT BE 0
#define SONIC_TIMEOUT (0xFFFF-1000)

//#define USE_SONIC_AVERAGE
//#define PING_AVERAGE (0)

unsigned int ping_convert(unsigned int value);
unsigned int ping_front();
unsigned int ping_lf();
unsigned int ping_lb();
unsigned int ping_right();

unsigned int p_front();
unsigned int p_lf();
unsigned int p_lb();
unsigned int p_right();

void sonic_test();

#endif	/* SONIC_H */

