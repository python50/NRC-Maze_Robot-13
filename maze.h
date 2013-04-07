/* 
 * File:   maze.h
 * Author: jason
 *
 * Created on March 30, 2013, 12:14 PM
 */

#ifndef MAZE_H
#define	MAZE_H

void maze_loop();
void maze_interupt();

void maze_debug();

void collect_sensor_data();

void centering_angle();
char centering_state();

void center_straight();
void center_close();
void center_open();

void centering();

char is_branch();
void branching();

typedef struct
{
	char started:1;

	unsigned int lf;
	//unsigned int adv_lf;
	unsigned int lb;
	//unsigned int adv_lb;
	unsigned int right;
	//unsigned int adv_right;
	unsigned int front;
	//unsigned int adv_front;
	int difference;
	//unsigned int adv_difference;

	char angle;

	char dist;
	char dist_state;

} MAZE;

extern MAZE maze;

typedef enum start_state
{
	
	start_done=0,
	start_ready
};

typedef enum dist_state
{
	dist_ok=0,
	dist_close,
	dist_far
};

typedef enum angle_state
{
	ang_vlow=0, //closing
	ang_low,
	ang_ok, //ok
	ang_high,
	ang_vhigh //opening
};


typedef enum center_state
{
	cs_ok,
	cs_ok_close,
	cs_ok_open,
	cs_close,
	cs_close_close,
	cs_close_open,
	cs_far,
	cs_far_close,
	cs_far_open,

};

#endif	/* MAZE_H */

