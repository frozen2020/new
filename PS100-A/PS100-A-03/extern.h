#ifndef __YUCO_H__
#define __YUCO_H__
#pragma once

/*** Constant Definitions ***/
ioport char port00;			/*display control register			*/
ioport char port01;		   /* display data reg					 */

extern char msg1[];
extern char msg2[];		
extern char msg3[];
extern char msg4[];
extern char msg5[];
extern char msg6[];
extern char msg7[];
extern char msg8[];
extern char msg9[];
extern char msg10[];
extern char msg11[];
extern char msg12[];
extern char msg13[];
extern char msg14[];
extern char msg15[];
extern char msg16[];
extern char msg17[];
extern char msg18[];
extern char msg19[];
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
extern char msg20[];
extern char msg21[];
extern char msg22[];
extern char msg23[];
extern char msg24[];
extern char msg25[];
extern char msg26[];
extern char msg27[];
extern char msg28[];
extern char msg29[];
extern char msg30[];
extern char msg31[];
extern char msg32[];
extern char msg33[];
extern unsigned short SIGN_FUN8SET, SIGN_FUN12SET,securityenable,SecurityIniting;
extern float INITCUR,INITCUR2;
extern unsigned short TimeC_Sec,TimeC_Min,TimeC_2Min,TimeC_8Min,Sign_2Min,Sign_8Min;
extern unsigned short FirstStemp;
extern unsigned short InitingError,JumpInit;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
extern unsigned short TEMPTBL1[51]; 
extern long LASER_TEMP, ENVIR_TEMP, LHT_PG, LHT_IG, LHT_OLDI, LHT_I, LHT_D, LHT_DG;
extern short Iindex, FUNCTION, OLD_ERROR_L, Sctr, T1, T2, T4, T5, T6, ENIVR,T9,T10,T11,T12,T13,T14,T15;
extern unsigned short QSWEXT, SHTON, RESET, PLACE, BEEPER, BTIME, KEY,LOOP,MOTORSTART,MOTORCOUNT;
extern unsigned short REMLOC, QSWON,QSWEN, ADJUST, UPDRAT, EXTDCUR,EXTDCUR2, EXTD,EXTFREQ, FREQ, FCTR;
extern unsigned long PWMTime, PULSERATE, DIODECUR, DIODECUR2, INTEST, wt, Diode_SetPt,Diode_SetPt2, DATA, DUMMY; //++ , PWMTime
extern float D1_ACT, D1_SET,D2_ACT,D2_SET, LASSET,LASACT, D1_ERROR, D1_PROP, D1_INT, D1_DIF, RES_D1, RDIF, RDELTA; 
extern float OLD_ERROR, OLD_D1_INT, OLD_ACT, INTLIMIT;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern float FanLaser_ERROR, FanLaser_PROP, FanLaser_INT, FanLaser_DIF; 
extern float FanLaser_OLD_ERROR, OLD_FanLaser_INT;
extern short FanLaser_OUT, FanLaser_OUT_OLD;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern unsigned short ADTIMER, TFLAG, LASER_SET,DIODESELECT;  
extern short D1_OUT, D1_SUM, ENVIR, RES_ENVIR, EXRFP, TPFLAG, RES_LASER_TEMP;
extern float Kp, Ki, Kd,LASERPOWER;
extern short smooth, D1_OUT_OLD;
extern short adTimerVar, OLD_KEYSW_ON;
extern short WriteFlag, DIMAX;
extern unsigned int Time;
extern long TEMP,STEPCOUNT;
extern short ENVACT, ENVSET, XTL1ACT, XTL1SET, XTL2ACT, XTL2SET,POS_OLD,POS_NEW;
extern char chr; 
extern char HOLD[6];
extern long DspTmr;
extern char TURN_ON[];
extern char TURN_OFF[];
extern char ERROR[];
extern char msg_globe[];
extern char OKK[];
extern char OKOKOK[];
extern char ZERO;
extern char EQUAL;
extern char NEW_LINE;
extern char QUESTION;
extern char EMPTY[];
extern char QSW[];
extern char SHT[];
extern char EXT[];
extern char PRF[];
extern char PWM[];
extern char TEV[];
extern char TLA[];
extern char TK1[];
extern char TK2[];
extern char TDI[];
extern char IDI[];
//extern char PKP[];--xiao
//extern char PKI[];--xiao
//extern char PKD[];--xiao
extern char RST[];

extern char DIO[];
extern char FPS[];
extern char FPL[];
extern char DCL[];

extern unsigned short DIODECUR_ACT,DIODECUR_ACT2;
extern short gate, gate_pre;
extern short fps_index;
extern short fps[];
extern short RF_GATE_ON;
extern short fps_index_count;

extern short RF_OFF;
extern short FPS_ON,FPS_ON_SET;
extern short FPS_LEVEL,FPS_LEVEL_SET;
extern short MODE_SEL;
extern short MODE_DONE;
extern short clearWarning, wrf,index;

#endif
