#include "maze.h"
#include "sonic.h"
#include "motor.h"
#include "user.h"

//#define printf //

void message(char m)
{
	signed char pl=motor.power_left;
	signed char pr=motor.power_right;

	motor_left_power(0);
	motor_right_power(0);

	beep_message(m);

	motor_left_power(pl);
	motor_right_power(pr);
}

MAZE maze={0};

int absval(int val)
{
	return (val < 0 ? (-val) : val);
}

void maze_interupt()
{
	maze.started=1;
	asm("nop");
}

void maze_loop()
{
	while (1)
	{

		
		
		
		if (maze.started)
		{

			PORTAbits.RA0=0;
			asm("nop");

			maze.started=start_done;

			collect_sensor_data();

			centering();

			if (is_branch())
				branching();
			maze_debug();
		}

	}
}

void maze_debug()
{
	static char i=0;
	i++;
	if (i==9)
	{
		i=0;

		printf("%s", ENDL);
		printf("LF:\t%d%s", maze.lf, ENDL);
		printf("LB:\t%d%s", maze.lb, ENDL);
		printf("FNT:\t%d%s", maze.front, ENDL);
		printf("RGT:\t%d%s", maze.right, ENDL);
		printf("DIF:\t%d%s", maze.difference, ENDL);

		if (maze.angle==ang_vlow)
			printf("ANG:\tVlow%s", ENDL);
		if (maze.angle==ang_low)
			printf("ANG:\tLow%s", ENDL);
		if (maze.angle==ang_ok)
			printf("ANG:\tOk%s", ENDL);
		if (maze.angle==ang_high)
			printf("ANG:\tHigh%s", ENDL);
		if (maze.angle==ang_vhigh)
			printf("ANG:\tVhigh%s", ENDL);

		if (maze.dist_state==dist_ok)
			printf("DST:\tOK%s", ENDL);
		if (maze.dist_state==dist_close)
			printf("DST:\tClose%s", ENDL);
		if (maze.dist_state==dist_far)
			printf("DST:\tFar%s", ENDL);

	}
}

void collect_sensor_data()
{

	maze.lf		+=ping_lf();
	maze.lf		/=2;
	maze.front	+=ping_front();
	maze.front	/=2;
	maze.lb		+=ping_lb();
	maze.lb		/=2;
	maze.right	+=ping_right();
	maze.right	/=2;
	maze.difference	=maze.lf - maze.lb;
	maze.dist	=maze.lf;

}

void centering_angle()
{
	//angle constant
	#define AC_VLOW	-15
	#define AC_LOW	-5
	#define AC_HIGH	5
	#define AC_VHIGH	15

	//|| VLOW | LOW | OK | HIGH | VHIGH ||
	if (maze.difference < AC_VLOW)
	{
		maze.angle=ang_vlow;
		return;
	}
	if (maze.difference  < AC_LOW)
	{
		maze.angle=ang_low;
		return;
	}
	if (maze.difference < AC_HIGH )
	{
		maze.angle=ang_ok;
		return;
	}
	if (maze.difference < AC_VHIGH)
	{
		maze.angle=ang_high;
		return;
	}
	//if (maze.difference > AC_VHIGH)
	//{
	maze.angle=ang_vhigh;
	return;
	//}
}


char centering_state()
{
	const char dist_close=55;
	const char dist_far=55;

	//Close ?
	if (maze.dist < dist_close)
	{
		maze.dist_state=dist_close;

		if (maze.angle < ang_ok)
			return cs_close_close;
		if (maze.angle > ang_ok)
			return cs_close_open;
		return cs_close;
	}//Far ?
	else if (maze.dist > dist_far)
	{
		maze.dist_state=dist_far;

		if (maze.angle < ang_ok)
			return cs_far_close;
		if (maze.angle > ang_ok)
			return cs_far_open;
		return cs_far;

	}//No, then OK
	else
	{
		maze.dist_state=dist_ok;
		
		if (maze.angle < ang_ok)
			return cs_ok_close;
		if (maze.angle > ang_ok)
			return cs_ok_open;
		return cs_ok;
	}

}

void center_straight()
{
		motor_left_power(50);
		motor_right_power(50);
}

void center_close()
{
		motor_left_power(50 - 8);
		motor_right_power(50);
}

void center_open()
{
		motor_left_power(50);
		motor_right_power(50 - 8);
}

void centering()
{
	//-----------------------------
	//Determine State
	//0 OK
	//1 OK, closing
	//2 OK, opening
	//3 Close, closing
	//4 Close, opening (No action)
	//5 Far, closing (No action)
	//6 Far, opening
	
	centering_angle();
	char state=centering_state();

	//-----------------------------
	//act upon state
	switch (state) {
	case cs_close_open:
	case cs_far_close:
	case cs_ok:
		//No action required yet !
		//message(2);
		center_straight();

		break;

	case cs_close:
	case cs_close_close:

	case cs_ok_close:
		//stop closing onto wall
		//message(1);

		center_open();

		break;


	case cs_far:
	case cs_far_open:

	case cs_ok_open:
		//stop opening onto wall
		//message(3);
		center_close();


		break;

	default:
		message(10);
		break;
	}
}

char is_branch()
{
	//FOR BRANCHING
#define GRACE_TIME (20);
	//grace period timer
	static char grace=GRACE_TIME;
	if (grace)
		grace--;




	if (maze.right > 140 && grace == 0)
	{
		grace=GRACE_TIME;
		return 1;
	}

	if (maze.lf > 140 && grace == 0)
	{
		grace=GRACE_TIME;
		return 1;
	}

	if (maze.front < 80 && grace == 0)
	{
		grace=GRACE_TIME;
		return 1;
	}

	return 0;
}

void branching()
{
	sys_delay_ms(2);

	#define TURN_POWER (60)
	//currently around 10 ticks per second
	#define TURN_ENC (38)
	if (maze.lf > maze.right)
		//Left is open
		motor_set_target(TURN_ENC,-TURN_ENC);
	else
		//Right is open
		motor_set_target(-TURN_ENC,TURN_ENC);
}
