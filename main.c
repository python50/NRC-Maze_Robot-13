/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "sonic.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "motor.h"
#include "maze.h"
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
char buf[80];

/* i.e. uint8_t <variable_name>; */

void set_power()
{
	printf("Enter power: ");

	gets(buf);
	signed char power=atoi(buf);
	motor_left_power(power);
	motor_right_power(power);

	printf("Power Set To %d %s", power, ENDL);
}

void time_turn_test()
{
	printf("Enter turn time: ");

	gets(buf);
	int time=atoi(buf);

	for (char i=1; i; i++)
		__delay_ms(12);

	//Right is open
	motor_left_power(50);
	motor_right_power(-50);

	for (char i=0; i < time; i++)
		__delay_ms(10);

	motor_left_power(0);
	motor_right_power(0);
}

void encoder_test()
{

	sys_delay_ms(10);
}

void turn_enc_test()
{
	printf("Enter Left Encoder Ticks (50/rev): ");
	gets(buf);
	int left=atoi(buf);

	printf("Enter right Encoder Ticks (50/rev): ");
	gets(buf);
	int right=atoi(buf);

	motor_set_target(left, right);
}

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/
#define JP1 (PORTBbits.RB5)
#define JP2 (PORTBbits.RB4)

void main(void)
{
	/* Configure the oscillator for the device */
	ConfigureOscillator();

	/* Initialize I/O and Peripherals for application */
	InitApp();

	/* TODO <INSERT USER APPLICATION CODE HERE> */



	PORTAbits.RA0=1;
	__delay_ms(10);
	PORTAbits.RA0=0;

	beep(1);

	if (!JP1)
	{
		printf("STARTING MAZE%s", ENDL);
		maze_loop();
	}



	unsigned int i=0;
	while (1)
	{
		printf("MAZE ROBOT FIRMWARE BY JASON WHITE%s", ENDL);
		printf("COPYRIGHT 2013 (C) JASON WHITE <JASON@JSWHITE.NET>%s", ENDL);

		printf("1: Sonic Test%s", ENDL);
		printf("2: Turn Enc Test%s", ENDL);
		printf("3: Set Motor Power%s", ENDL);
		printf("4: Time Turn Test%s", ENDL);
		printf("5: Encoder Test%s", ENDL);

		printf("> ");
		gets(buf);
		if (strcmp(buf, "1") == 0)
			sonic_test();
		else if (strcmp(buf, "2") == 0)
			turn_enc_test();
		else if (strcmp(buf, "3") == 0)
			set_power();
		else if (strcmp(buf, "3") == 0)
			set_power();
		else if (strcmp(buf, "4") == 0)
			time_turn_test();
		else if (strcmp(buf, "4") == 0)
			encoder_test();
		else
			printf("COMMAND ERROR%s%s", ENDL, ENDL);
		printf("OK%s%s", ENDL, ENDL);

	}

}

