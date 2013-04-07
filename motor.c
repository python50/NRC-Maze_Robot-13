#include "motor.h"
#include "stdio.h"
#include "user.h"

MOTOR motor={0};

void left_on()
{
	if (motor.power_left > 0)
		MOTOR_LEFT_FOREWARD=1;
	else if (motor.power_left < 0)
		MOTOR_LEFT_BACKWARD=1;
}

void left_off()
{
	MOTOR_LEFT_FOREWARD=0;
	asm("nop");
	MOTOR_LEFT_BACKWARD=0;
}

void right_on()
{
	if (motor.power_right > 0)
		MOTOR_RIGHT_FOREWARD=1;
	else if (motor.power_right < 0)
		MOTOR_RIGHT_BACKWARD=1;
}

void right_off()
{
	MOTOR_RIGHT_FOREWARD=0;
	asm("nop");
	MOTOR_RIGHT_BACKWARD=0;
}

char abval(signed char val)
{
	return (val < 0 ? (-val) : val);
}

void motor_interupt()
{
	static signed char left_counter=0;
	static signed char right_counter=0;

	left_counter++;
	right_counter++;

	//Remove sign bit
	if (left_counter >= abval(motor.power_left))
		left_off();
	if (right_counter >= abval(motor.power_right))
		right_off();

	if (left_counter == 100)
	{
		left_counter=0;
		left_on();
	}

	if (right_counter == 100)
	{
		right_counter=0;
		right_on();
	}
}



void motor_enc_interupt()
{
	static char left=0;
	static char right=0;

	if (ENC_RIGHT != right)
	{
		right=ENC_RIGHT;
		motor.encoder_right++;
	}
	if (ENC_LEFT != left)
	{
		left=ENC_LEFT;
		motor.encoder_left++;
	}
}

void motor_enc_clear()
{

	motor.encoder_left=0;
	motor.encoder_right=0;
}

#define MOTOR_ENC_POWER (100)
void motor_set_target(int left, int right)
{
	motor_enc_clear();

	signed char old_left=motor.power_left;
	signed char old_right=motor.power_right;

	if (left < 0)
	{
		motor_left_power(-MOTOR_ENC_POWER);
		left=-left;
	}
	else
		motor_left_power(MOTOR_ENC_POWER);

	if (right < 0)
	{
		motor_right_power(-MOTOR_ENC_POWER);
		right=-right;
	}
	else
		motor_right_power(MOTOR_ENC_POWER);

	while (1)
	{
		if (motor.encoder_left >= left)
		{
			motor_left_power(0);
		}

		if (motor.encoder_right >= right)
		{
			motor_right_power(0);
		}

		if ( !motor.power_left && !motor.power_right)
			break;
	}

	motor_left_power(old_left);
	motor_right_power(old_right);
}

void motor_left_power(signed char p)
{
	motor.power_left=p;

	if (motor.power_left > 99)
		motor.power_left=99;
	if (motor.power_left < -99)
		motor.power_left=-99;
}

void motor_right_power(signed char p)
{
	motor.power_right=p;

	if (motor.power_right > 99)
		motor.power_right=99;
	if (motor.power_right < -99)
		motor.power_right=-99;
}