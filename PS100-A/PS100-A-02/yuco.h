#include "constants.h"

#ifndef __YUCO_H__
#define __YUCO_H__
#pragma once

/*** Constant Definitions ***/
ioport char port00;			/*display control register			*/
ioport char port01;		   /* display data reg					 */

/*** messages ***/
/*            0000000000111111111122222222223333333333 */	//MAIN MENU
/******       0123456789012345678901234567890123456789 */
char msg1[]= "    PS100-A A14      IS1= 0.0A IA1= 0.0A";
/******       666666777777777788888888889999999999AAAA */
/******       4567890123456789012345678901234567890123 */
//char msg2[]= " PRF = 20.0KHz  LOC  QS INT  SHTTER OFF";		
char msg2[]= " PRF = 20.0KHz,   %  QS INT SHT OFF  LOC";		
/*             0000000000111111111122222222223333333333 */	// FUNCTION 1
/******        0123456789012345678901234567890123456789 */
char msg3[]=  "  DIODE HOUR METER         HOURS IN USE";


//  ----------  CURRENT AND TEMPERATURE SETTING MENUES -------

/*             0000000000111111111122222222223333333333 */	// FUNCTION 3
/******        0123456789012345678901234567890123456789 */
char msg4[]=  " SEED LD TEMPERATURE ACT=25.0  SET=25.0";

/*             0000000000111111111122222222223333333333 */	// FUNCTION 4
/******        0123456789012345678901234567890123456789	*/
char msg5[]=  "  ENVIR TEMPERATURE  ACT=25.0  SET=25.0";

/*             0000000000111111111122222222223333333333	*/	// FUNCTION 5
/******        0123456789012345678901234567890123456789	*/
char msg6[]=  "  DIODE TEMPERATURE  ACT=      SET=";

/*             0000000000111111111122222222223333333333	*/	// FUNCTION 6
/******        0123456789012345678901234567890123456789	*/
char msg7[]=  "CRYSTAL1 TEMPERATURE ACT=      SET=";

/*             0000000000111111111122222222223333333333	*/	// FUNCTION 7
/******        0123456789012345678901234567890123456789	*/
char msg8[]=  "CRYSTAL2 TEMPERATURE ACT=      SET=";

/*             0000000000111111111122222222223333333333 */	// FUNCTION 8
/******        0123456789012345678901234567890123456789	*/
char msg9[]=  "DIODE CURRENT  -->  QSWITCH CONTROL -->";

//     -------- ERROR MESSAGES ------

/*            0000000000111111111122222222223333333333 */
/******       0123456789012345678901234567890123456789 */
char msg10[]= "  !!! WARNING !!!    ENVIRONMENTAL TEMP";

/*             0000000000111111111122222222223333333333 */
/******        0123456789012345678901234567890123456789 */
char msg11[]= "  !!! WARNING !!!    LASER HEAD TEMP";

/*             0000000000111111111122222222223333333333 */
/******        0123456789012345678901234567890123456789 */
char msg12[]= " !!! WARNING !!!     INTERLOCK OPEN";

/*             0000000000111111111122222222223333333333 */
/******        0123456789012345678901234567890123456789 */
char msg13[]= "  !!! WARNING !!!    PUMP DIODE1 TEMP";

/******        9999999 */
/******        0123456 */
char msg14[]= "TOO HIGH";

/******        9999999 */
/******        0123456 */
char msg15[]= "TOO LOW";
/******       66666677777777778888 */
/******       45678901234567890123 */
char msg16[]= "CLEARED -- RESET --";

/*             0000000000111111111122222222223333333333*/
/******        0123456789012345678901234567890123456789 */
char msg17[]= " SYSTEM INITIALIZING     PLEASE WAIT";

/*             0000000000111111111122222222223333333333 */	// FUNCTION 2
/******        0123456789012345678901234567890123456789 */
char msg18[]= "FIRST PULSE SUPRESS MODE=0 LEVEL=0  ";

char msg19[]= "CURRENT LIMIT=      CURRENT INIT2=  ";    //tang

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/******        0123456789012345678901234567890123456789 */
char msg20[]= "EN1 =     EN2 =     CURRENT INIT1=";
char msg21[]= "   OF TEMPERATURE    OF1=      OF2=";
/******        0123456789012345678901234567890123456789 */
char msg30[]= "  !!! WARNING !!!    PUMP DIODE2 TEMP";
char msg23[]= "  !!! WARNING !!!         OF2 TEMP";
/******       45678901234567890123 */
char msg24[]= "--PLEASE RESTART---";
/******        0123456789012345678901234567890123456789 */
char msg25[]= "   DATA READ ERROR";
char msg26[]= " PRESS EXIT TO STOP   PROGRESS  IN    S ";
char msg27[]= "                      Seed Power=      ";
char msg28[]= "  SEED LD CURRENT    ACT=      SET=";
char msg29[]= " LASER TEMPERATURE   ACT=      SET=";
char msg31[]= "  DATA WRITE ERROR";
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

unsigned short TEMPTBL1[51]= {9999, 9880, 9390, 8935, 8500, 8085, 7700,
								7330, 6980, 6650, 6335, 6040, 5760, 5495,
								5240, 5000, 4773, 4557, 4351, 4157, 3971,
								3795, 3628, 3469, 3318, 3174, 3037, 2907,
								2783, 2665, 2552, 2445, 2343, 2246, 2153,
								2064, 1980, 1900, 1823, 1749, 1679, 1612,
								1549, 1488, 1429, 1374, 1320, 1269, 1221,
								1174, 1129}; 

long LASER_TEMP, ENVIR_TEMP, LHT_PG, LHT_IG, LHT_OLDI, LHT_I, LHT_D, LHT_DG;
/*  float THOLD, TEMP;														*/
short Iindex, FUNCTION, OLD_ERROR_L, Sctr, T1, T2, T4, T5, T6, ENIVR,T9,T10,T11,T12,T13,T14,T15;
unsigned short QSWEXT, SHTON, RESET, PLACE, BEEPER, BTIME, KEY,LOOP;
unsigned short REMLOC, QSWON, QSWEN, ADJUST, UPDRAT, EXTDCUR,EXTDCUR2, DIODESELECT, EXTD,EXTFREQ, FREQ, FCTR;
unsigned long PWMTime, PULSERATE, DIODECUR,DIODECUR2, INTEST, wt, Diode_SetPt,Diode_SetPt2, DATA, DUMMY; //++ PWMTime
float D1_ACT, D1_SET,D2_ACT,D2_SET ,LASACT,LASSET, D1_ERROR, D1_PROP, D1_INT, D1_DIF, RES_D1, RDIF, RDELTA;
float OLD_ERROR, OLD_D1_INT, OLD_ACT, INTLIMIT;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
float FanLaser_ERROR, FanLaser_PROP, FanLaser_INT, FanLaser_DIF,Laserptemp,Laserptemp2;
float FanLaser_OLD_ERROR, OLD_FanLaser_INT;
short FanLaser_OUT, FanLaser_OUT_OLD;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
unsigned short ADTIMER, TFLAG, LASER_SET,Laserpi;  
short D1_OUT, D1_SUM, ENVIR, RES_ENVIR, EXRFP, TPFLAG, RES_LASER_TEMP;
float Kp, Ki, Kd,LASERPOWER;
short smooth, D1_OUT_OLD;
short adTimerVar, OLD_KEYSW_ON;
short WriteFlag, DIMAX;
unsigned int Time;
long TEMP;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//short ENVACT, ENVSET, D2_ACT, LASSET, XTL1ACT, XTL1SET, XTL2ACT, XTL2SET;
short ENVACT, ENVSET, XTL1ACT, XTL1SET, XTL2ACT, XTL2SET;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
char chr; 
char HOLD[6];
long DspTmr;

char TURN_ON[]="000001";
char TURN_OFF[]="000000";
char ERROR[]="ERROR ";
char msg_globe[6]="123456";
char OKK[]="OKK";
char QSW[]="QSW";
char SHT[]="SHT";
char EXT[]="EXT";
char PRF[]="PRF";
char PWM[]="PWM";
char TEV[]="TEV";
char TLA[]="TLA";
char TK1[]="TK1";
char TK2[]="TK2";
char TDI[]="TDI";
char IDI[]="IDI";
//char PKP[]="PKP";--xiao
//char PKI[]="PKI";--xiao
//char PKD[]="PKD";--xiao
char RST[]="RST";

char DIO[]="DIO";
char FPS[]="FPS";
char FPL[]="FPL";
char DCL[]="DCL";

char OKOKOK[]="OKOKOK";
char ZERO='0';
char EQUAL='=';
char NEW_LINE='\n';
char QUESTION='?';
char EMPTY[]="";
unsigned short DIODECUR_ACT, DIODECUR_ACT2;
short gate, gate_pre;
short fps_index=9;
short fps[10];
short RF_GATE_ON=2000;
short fps_index_count;
short RF_OFF;
short FPS_ON,FPS_ON_SET;
short FPS_LEVEL,FPS_LEVEL_SET;
short MODE_SEL;
short MODE_DONE;
short clearWarning;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
unsigned short SIGN_FUN8SET, securityenable,SecurityIniting;
float INITCUR,INITCUR2;
unsigned short TimeC_Sec,TimeC_Min,TimeC_2Min,TimeC_8Min,Sign_2Min,Sign_8Min;
unsigned short FirstStemp;
unsigned short InitingError,JumpInit;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
short wrf,index;
#endif
