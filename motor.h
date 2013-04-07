/* 
 * File:   motor.h
 * Author: jason
 *
 * Created on March 20, 2013, 7:00 PM
 */

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


#ifndef MOTOR_H
#define	MOTOR_H

#define _XTAL_FREQ	64000000L

#define MOTOR_RIGHT_FOREWARD	(PORTCbits.RC4)
#define MOTOR_RIGHT_BACKWARD	(PORTCbits.RC5)

#define MOTOR_LEFT_FOREWARD	(PORTDbits.RD4)
#define MOTOR_LEFT_BACKWARD	(PORTDbits.RD5)

#define ENC_RIGHT	(PORTDbits.RD0)
#define ENC_LEFT	(PORTDbits.RD1)


typedef struct
{
	signed char power_left;
	signed char power_right;
	unsigned int encoder_left;
	unsigned int encoder_right;
} MOTOR;

extern MOTOR motor;


void motor_interupt();
void motor_enc_interupt();
void motor_enc_clear();

void motor_set_target(int left, int right);
void motor_left_power(signed char p);
void motor_right_power(signed char p);

#endif	/* MOTOR_H */

