#include "f2407_c.h"

/* Sytem Definitions */
#define D1_MAXTEMP	350
#define D1_MINTEMP 120
#define D2_MAXTEMP 350
#define D2_MINTEMP 120
#define LAS_MAXTEMP 360
#define LAS_MINTEMP 120
#define MIN_STEP -999    
#define MAX_STEP 999
		
//#############################
//#define ENV_MAXTEMP 350
#define ENV_MAXTEMP 400
//#############################
#define ENV_MINTEMP 120

#define BEEPER_BIT	0x0020

#define pwm_per  2000			/* period, 20KHz PWM, 40MHz CPUCLK 	*/
#define HALF 1000				/* 50% DUTY CYCLE 					*/
#define MAX_AMPS 300.0
#define MAX_CNTS 1000
#define INV_MAX_AMPS (1.0/500)
#define MAX_DISPLAY_AMPS 200

#define GATE (*PADATDIR & 0x0008)
#define KEYSW_ON (*PADATDIR & 0x0020)
#define VALUE_LENGTH 6

