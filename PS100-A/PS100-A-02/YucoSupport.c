#include "constants.h"
#include "extern.h"
#include "Proto.h"

void Initialize()
{

	/* Setup the core interrupts									*/
	*IMR = 0x0000;			/* clear the IMR register			*/
    *IFR = 0x003F;			/* clear pending core interrupts 	*/
	/* Configure the System Control and Status registers			*/
    *SCSR1 = 0x00ED;
    *SCSR2 = (*SCSR2 | 0x000A) & 0x000F; 
	/* Disable the watchdog timer									*/
    *WDCR  = 0x00E8;    
	/* SETUP EXTERNAL MEMORY SPACE									*/
    WSGR = 0x01ff;
	/* Setup shared I/O pins 										*/
    *MCRA = 0x3543;
	/* group A pins:
	   0=SCITXD 1=SCIRXD 2=IOPA2 3=IOPA3 4=IOPA4 5=IOPA5 6=PWM1 7=IOPA7														
	   8=PWM3 9=IOPB1 10=PWM5 11=IOPB3 12=T1PWM 13=T2PWM 14=IOPB6 15=IOPB7 
	*/
    *MCRB = 0xFF0C;
	/* group B pins:
 	   0-7=IOPC0-7 8=IOPD0 9-15=RESERVED							
	*/
    *MCRC = 0x0C2B; /* iope1 rf driver power control */
	/* group C pins:
	   0=CLKOUT 1=PWM7 2=IOPE2 3=IOPE2 4=IOPE4 5=PWM11 6=IOPE6 7=IOPE7
	   8=IOPF0 9=IOPF1 10=A3PWM 11=A4PWM 12=IOPF4 13=IOPF5 14=IOPF6 15=RESERVED 
	*/
	/* Configure IOPA0,6,7 AS OUTPUTS AND IOPAI-5 AS INPUTS 		*/
	*PADATDIR = 0xC180;
	/* IOPORTA:
	   0=SCITXD 1=SCIRXD 2-5=dig inputs 0-3=outputs 6=TE1PWM 7=LED1   
	*/	
	/* Configure IOPB0-7 AS OUTPUTS 								*/
	*PBDATDIR = 0xFFCA;
	/* IOPORTB:
	   0=TE2PWM 1=LED2 2=TE3PWM 3=LED3 4=TE4PWM 5=PRFPWM 6-7=dig outputs 0-1 
	*/ 
	/* Configure IOPC0-3 AS OUTPUTS AND IOPC4-7 PINS as INPUTS 		*/
    *PCDATDIR = 0xF0F0;
	/* IOPORTC: 
	   0-3 KEYBOARD COLUMN STROBE OUTPUTS 0-3
	   4-7 KEYBOARD ROW STROBE INPUTA 4-7							
	*/
	/* Configure IOPD0 PIN  AS OUTPUT 								*/
    *PDDATDIR = 0x0100;
	/* IOPORTD OUTPUT NOT USED										*/
	/*** Configure IOPE0-7 PINS AS OUTPUTS  						*/
    *PEDATDIR = 0xFF52;
	/* Configure IOPF0-6 PINS AS OUTPUTS							*/
    *PFDATDIR = 0xFC14;
	/* IOPORTE:
	   0=output nc 1=anaout O 2=digout 2 3=anaout 1
	   4=digout 3 5=anaout 2 6=out nc 								
	*/
	/* Setup timers 1 and 2, and the PWM configuration 				*/
    *GPTCONA = 0x0046; /* GEN. PURPOSE TIMER CONTROL REGISTER A */
    *GPTCONB = 0x605A; /* GEN. PURPOSE TIMEN CONTROL REGISTER B */ 
	/* Timer 1: SET UP PULSE WIDTH CONTROL REGISTERS AND COUNTERS	*/
    *T1CNT = 0x0000;           /* clear timer counter 			*/
    *T1PR = pwm_per;           /* set timer period 				*/
    *DBTCONA = 0x0000;         /* deadband unit A off 			*/
    *ACTRA = 0x0AAA;           /* PWM1,3,5 ACTIVE HIGH 			*/
    *T1CON = 0x9042;           /* configure T1CON register		*/
    *CMPR1 = HALF;
    *CMPR2 = HALF;
    *T1CMPR = 0;
    *T1CMPR = 0;
    *COMCONA = 0xAA00;         /* COMPARE CONTROL REGISTER A 	*/
    *COMCONB = 0xAA00;         /* COMPARE CONTROL REGISTER B 	*/
	/* COMCONx ALL COMPARE FUNCTIONS ACTIVE HIGH ON COMPARE	*/	    
	/* timer 2: configure pwm */
    *T2CNT = 0x0000;           /* clear counter */
    *T2CON = 0x9042;  
    *T2PR = 1600;
    *T2CMPR =PWMTime;
	/* Timer 3: configure to clock the PWM PERIOD */
    *T3CNT = 0x0000;           /* clear timer counter */
    *T3PR = pwm_per;           /* set timer period */
    *DBTCONB = 0x0000;         /* deadband unit B off */
    *ACTRB = 0x0A9A;           /* PWM7,9,11 pin set active HIGH */     
    *T3CON = 0x9042;           /* configure T3CON register */ 
	*CMPR4 = 0;
	*CMPR5 = 0;
	*CMPR6 = 0;
    *T3CMPR = 0;	    
	/* timer 4:   */
    *T4CNT = 0x0000;
    *T4CON = 0x9042;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    
	*T4PR = pwm_per;           /* set timer period 				*///tanga2
		*T4CMPR =0;   //tanga2
	//*T4PR  = 100;
	//*T4CMPR = 100;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    
	/*** Setup the event manager interrupts ***/
    *EVAIFRA = 0x078F;         /* clear all EVA group A interrupts */
    *EVAIFRB = 0x078F;         /* clear all EVA group B interrupts */
    *EVAIFRC = 0x078F;         /* clear all EVA group C interrupts */
    *EVAIMRA = 0x0080;         /* enable desired EVA group A interrupts */
    *EVAIMRB = 0x0000;         /* enable desired EVA group B interrupts */
    *EVAIMRC = 0x0000;         /* enable desired EVA group C interrupts */
    *EVAIFRA = 0x078F;         /* clear all EVB group A interrupts */
    *EVBIFRB = 0x078F;         /* clear all EVB group B interrupts */
    *EVBIFRC = 0x078F;         /* clear all EVB group C interrupts */
    *EVBIMRA = 0x0000;         /* enable desired EVB group A interrupts */
    *EVBIMRB = 0x0000;         /* enable desired EVB group B interrupts */
    *EVBIMRC = 0x0000;         /* enable desired EVB group C interrupts */	
	/*** set up  and calibrate adc  ***/
    *ADCTRL1 = 0x0F90;        /*set prescaller and cascade mode */
    *ADCTRL2 = 0x4000;        /*set soc and interrupt mode */
    *MAX_CONV = 0x000F;       /*set for 8 conversions */
    *CHSELSEQ1 = 0x3210;      /*four conversions of channels 0 - 3 */
    *CHSELSEQ2 = 0x7654;      /*four conversions of channels 4 - 7 */ 
    *CHSELSEQ3 = 0x3210;      /*four conversions of channels 0 - 3 */
    *CHSELSEQ4 = 0x7654;      /*four conversions of channels 4 - 7 */ 
	*SPICTL = 0x0E;
	*SPICCR = 0x87;
	*SPIBRR = 0x39;	
	/***************** set up external interrupts *****************/
	*XINT1CR = 0x8000;
	*XINT2CR = 0x8000;
   	
	//RS232
	sciInit();	
	/*** initialize variables ***/
	wrf = 0;
	ReadData();
		QSWEN =1; //tang
	// DIMAX, PULSERATE, D2_SET. ENVSET, D1_SET, Time 
	if( (DIMAX < 0) || (DIMAX > 480) ) {
		DIMAX = 100;
		wrf = 1;
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if( (INITCUR < 0) || (INITCUR > DIMAX) ) {
		INITCUR = 100;
		wrf = 1;
	}
	if( (securityenable< 0) || (securityenable > 11) ) {
		securityenable=0;
		wrf = 1;
	}

	if( (INITCUR2 < 0) || (INITCUR2 > DIMAX) ) {
		INITCUR2 = 100;
		wrf = 1;
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if( (PULSERATE < 10) || (PULSERATE > 120000) ) {     //原为100000
		PULSERATE = 20000;
		wrf = 1;
	}
	/* TEMPTBL1[0] = 15 Degrees C, 2738 = 38 Degrees C */
	if( (D2_SET > 350) || (D2_SET < 200) ) {                    //D2_SET
		D2_SET = 350;
		wrf = 1;
	}
		/* TEMPTBL1[0] = 15 Degrees C, 2738 = 38 Degrees C */
	if( (LASSET > LAS_MAXTEMP) || (LASSET < LAS_MINTEMP) ) {                    //D2_SET
		LASSET = 250;
		wrf = 1;
	}
	/* TEMPTBL1[0] = 15 Degrees C, TEMPTBL1[0] = 32 Degrees C */
	//#############################################
	//if( (ENVSET > 450) || (ENVSET < 150) ) {
    //	ENVSET = 350;
	//	wrf = 1;
	//}
	if( (ENVSET > 550) || (ENVSET < 150) ) {
		ENVSET = 400;
		wrf = 1;
	}
	//#############################################
	if( (D1_SET < 200) || (D1_SET > 350) ) {
		D1_SET = 250;
		wrf = 1;
	}
	if( (PWMTime < 20) || (PWMTime > 380) ) {
		PWMTime = 20;
		wrf = 1;
	}
	if( wrf ) {
		WriteData();
		wrf = 0;
	}	
	UPDRAT = 0;
	QSWEXT = 0;
	QSWON = 0;
	SHTON = 0;
	REMLOC = 0;
	FUNCTION = 0;
	DIODECUR=DIODECUR2 = 0;
	INTEST = 0;
	FUNCTION = 0;
	TPFLAG = 0;
	RESET = 0;
	ADTIMER = 2000;
	RDELTA = 0.1;
	ADJUST = 250;
	D1_PROP = 1;
	D1_INT = 0;
	D1_DIF = 0;
	Kp = 268;
	Ki = 0.2;
	Kd = 5;
	OLD_D1_INT = 0.0;
	OLD_ERROR = 0.0;
	smooth = 500;
	D1_OUT_OLD = 0;
	OLD_KEYSW_ON = 0;
	EXTDCUR =EXTDCUR2= 0;
	WriteFlag = 1;
	ENVIR = 5000;
	LHT_PG = 100;
	LHT_IG = 10;
	LHT_DG = 500;
	OLD_ERROR_L = 0;
	LHT_OLDI = 0;
	D2_SET = 300;
	DIODESELECT=0;
	T1=T2=T4=T5=T6=0;
	*T2PR = (40000000 / PULSERATE);	  
	pulseRateAction();  
	/*** setup interrupts ***/
    *IMR = 0x0007;	
	/*** Enable global interrupts ***/
    *ADCTRL2 = *ADCTRL2 | 0x2000;  /* start adc */
    wt=0;
    asm(" CLRC INTM");         /* enable global interrupts */
    gate=0;
    gate_pre=0;
    fps[9]=0;
    fps[8]=200;
    fps[7]=400;
    fps[6]=600;
    fps[5]=800;
    fps[4]=1000;
    fps[3]=1200;
    fps[2]=1400;
	fps[1]=2000;
	fps[0]=2000;
	fps_index_count=fps_index;	
//	*EVAIMRB = 0x0002;  //enable T2Compare interrupt	
	RF_OFF=0;
//	FPS_ON=0;
	FPS_LEVEL=100;
	MODE_SEL=1;	
	*PEDATDIR = *PEDATDIR | 0x0010;
	*PEDATDIR = *PEDATDIR & 0xFFBF; 	//init of FPS is off
	

	RF_OFF=1;
	
	MODE_DONE=0;
	clearWarning=0;
} 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void First()
{
	SecurityIniting=0;
	if(securityenable>=1)
	{
		if(JumpInit==0)
		{
			SecurityIniting=1;
			FirstStemp=1;
		}
		else
		{
			SecurityIniting=0;
			FirstStemp=0;
		}
	}
	else
	{
		SecurityIniting=0;
		FirstStemp=0;
	}
	TimeC_Sec=0; 
	TimeC_Min=0;
	TimeC_2Min=0;
	TimeC_8Min=0;
	Sign_2Min=0;
	Sign_8Min=0;
	
	//securityenable=0;
	//INITCUR=380;
	InitingError=0;
	SIGN_FUN8SET=0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void dspfun()
{
	port00 = 01;
	wait(20);
		PLACE = 0;
		port00 = 01;
		wait(20);
	if(FUNCTION == 1)				// DIODE HOURS
		{
	 	message(msg3);
	 	PLACE = 20;
	 	num2ascii(Time, 2);
		}
		
	//FPS//
	else if(FUNCTION == 2)				
		{
	 	message(msg18);
	 	//PLACE = 25;
	 	//HOLD[0]=FPS_ON+'0';
	 	//wrtchrs(1);
	 	
	 	//PLACE = 34;
	 	//num2ascii(FPS_LEVEL*10, 0);	 	
	 		
	 	//cursor
	 	if(MODE_SEL==1)
	 		{
	 		PLACE = 25;
	 	HOLD[0]=FPS_ON+'0';
	 	wrtchrs(1);
	 		port00 = 26+128;
	 		wait(2);
			port00 = 0x000F;			
			}		
		else
	 		{
	 		PLACE = 33;
	 		num2ascii(((short)(FPS_LEVEL/5))*10, 0);	 		 		 		
	 		port00 = 39+128;
	 		wait(2);
			port00 = 0x000F;			
			}							
	 	}			
	else if (FUNCTION == 3)			// DIODE TEMPERATURE
		{
	 	message(msg4);
	 	PLACE = 25;
	   	num2ascii(D1_ACT, 0);	// D1_ACT*10
	   	PLACE = 35;
   		num2ascii(D1_SET, 0);		// D1_SET
		wait(2);
		port00 = 0x000F;
		}
	else if (FUNCTION == 9)			// ENVIROMENTAL TEMPERATURE
		{
	 	message(msg5);
	 	PLACE = 25;
	 	num2ascii(ENVACT, 0);
	 	PLACE = 35;
	 	num2ascii(ENVSET, 0);
		}
	else if (FUNCTION == 5)			// LASER TEMPERATURE
		{
	 	message(msg6);
	 	PLACE = 25;
	 	num2ascii(D2_ACT, 0);
	 	PLACE = 35;
	 	num2ascii(D2_SET, 0);
		//%%%%%%%%%%%%%%%%%%%%
	 	}
	else if (FUNCTION == 6)			// CRYSTAL1 TEMPERATURE
	 	{
	 	message(msg7);
	 	PLACE = 25;
	 	num2ascii(XTL1ACT, 0);
	 	PLACE = 35;
	 	num2ascii(XTL1SET, 0);
		}
	else if (FUNCTION == 7)			// CRYSTAL2 TEMPERATURE
		{
	 	message(msg8);
	 	PLACE = 25;
	 	num2ascii(XTL2ACT, 0);
	 	PLACE = 35;
	 	num2ascii(XTL2SET, 0);
		} 	
	else if (FUNCTION == 8)			// DIODE MAXIMUM CURRENT  , change +-
		{
	 	PLACE = 0;
	 	//%%%%%%%%%%%%%%%%%%%%
	 	//message(msg9);
	 	message(msg20);
		PLACE = 64;
	 	message(msg19);
		
		PLACE = 35;
		num2ascii(INITCUR, 0);

		PLACE = 99;
	 	num2ascii(INITCUR2, 0);//tang
		//%%%%%%%%%%%%%%%%%%%%
	 	PLACE = 79;
	 	num2ascii(DIMAX, 0); 	
		PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++

	 	wait(2);
		port00 = 0x000F;
		}
		else if (FUNCTION == 10)	
		{
	 	PLACE = 0;
	 	message(msg27);
		
		PLACE =30;
		num2ascii((short)LASERPOWER, 7);//tang
		//%%%%%%%%%%%%%%%%%%%%
		}
		else if (FUNCTION == 4)	
		{
		message(msg28);
		PLACE = 64;
	 	message(msg27);
		PLACE = 98;
		num2ascii((short)LASERPOWER, 7);//tang
	 	PLACE = 25;
	 	num2ascii(DIODECUR_ACT2, 0);
	 	PLACE = 35;
	 	num2ascii(DIODECUR2, 0);
		wait(2);
		port00 = 0x000F;

		}
		else if (FUNCTION == 11)			// CRYSTAL1 TEMPERATURE
	 	{
	 	message(msg29);
	 	PLACE = 25;
	 	num2ascii(LASACT, 0);
	 	PLACE = 35;
	 	num2ascii(LASSET, 0);
	 	}
} 

/* interrupt generated wait routine  20 counts / ms           */
void wait(short TICK)
{
	INTEST = TICK * 20;
	while (INTEST);
} /* End wait() */

/* message */
void message(char* msgnum1)
{
    int i;
	port00 = 12;
	wait(2);
   	port00 = PLACE + 128;
 	wait(20);
	i=0;
	while( msgnum1[i] )
	{
	wait(2);
	chr = msgnum1[i];					
	port01 = chr;
	i++;
	}
	
} 

/*WRITE DISPLAY ROUTINE */
void num2ascii(unsigned long number, short chr)
{
    wait(20);
	if(chr == 1) {
		if(number == 150000) {     //150k//频率上限120K，原100000
			HOLD[0] = ' ';
			HOLD[1] = '1';
			HOLD[2] = '5';
			HOLD[3] = '0';
			HOLD[4] = 'K';
		} else if(number >149999) {   //频率上限120K,119999，原为99999
			HOLD[0] = '>';
			HOLD[1] = '9';
			HOLD[2] = '9';
			HOLD[3] = '9';
			HOLD[4] = 'K';
		} else if(number >99999) {                //  ++
			HOLD[0] = ' ';                        //  ++
			HOLD[1] = (number / 100000) + '0';    //  ++
			if( HOLD[1] == '0' ) HOLD[0] = ' ';   //  ++
			number = (number % 100000);           //  ++
			HOLD[2] = (number / 10000) + '0';     //  ++
			number = (number % 10000);            //  ++                    
			HOLD[3] = (number / 1000) + '0';      //  ++
			HOLD[4] = 'K';                        //  ++
		} else if(number >999) {
			HOLD[0] = (number / 10000) + '0';
			if( HOLD[0] == '0' ) HOLD[0] = ' ';
			number = (number % 10000);
			HOLD[1] = (number / 1000) + '0';
			number = (number % 1000);
			HOLD[2] = '.';
			HOLD[3] = (number / 100) + '0';
			HOLD[4] = 'K';
		} else {
			HOLD[0] = ' ';
			HOLD[1] = ' ';
			HOLD[2] = (number / 100) + '0';
			number = (number % 100);
			HOLD[3] = (number / 10) + '0';
			number = (number % 10);
			HOLD[4] = number + '0';
		}
		wrtchrs(5);
	} else if(chr == 2 ) {
		HOLD[0] = (number / 10000) + '0';
		if( HOLD[0] == '0' ) HOLD[0] = ' ';
		number = (number % 10000);
		HOLD[1] = (number / 1000) + '0';
		if( HOLD[1] == '0' ) HOLD[1] = ' ';
		number = (number % 1000);
		HOLD[2] = (number / 100) + '0';
		number = (number % 100);
		HOLD[3] = (number / 10) + '0';
		number = (number % 10);
		HOLD[4] = '.';
		HOLD[5] = number + '0';
		wrtchrs(6);
	}else if(chr == 0 ){                       //   ++
		HOLD[0] = (number / 100) + '0';
		number = (number % 100);
		HOLD[1] = (number / 10) + '0';
		number = (number % 10);
		HOLD[2] = '.';
		HOLD[3] = number + '0';
		wrtchrs(4);   
	}
	else if(chr == 5 ){                       //   ++
		HOLD[0] = (number / 1000) + '0';
		number  = (number % 1000);
		HOLD[1] = (number / 100) + '0';
		number  = (number % 100);
		HOLD[2] = '.';
		HOLD[3] = (number / 10)+ '0';
		number  = (number % 10);
		HOLD[4] = number + '0';
		wrtchrs(5);   
	}
	else if(chr == 9 ){                        //PWM
	    number = (820 - number) / 8;           //500ns//y=(340-x)/3;Limit 40,310
	    if(number / 100)
	    HOLD[0] = '1';
	    else
	    HOLD[0] = ' ';
		number = (number % 100);
		HOLD[1] = (number / 10) + '0';
		number = (number % 10);
		HOLD[2] = number + '0';
		wrtchrs(3);
	}
	else if(chr == 7)
	{ HOLD[0]=number/100+'0';
	  HOLD[1]='.';
	  HOLD[2]=number%100/10+'0';
	  HOLD[3]=number%10+'0';
	wrtchrs(4);
	}
	else
	{                            //   ++     
	      	HOLD[0] = ' ';            //   ++
	      	HOLD[1] = ' ';            //   ++
	      	HOLD[2] = ' ';           //   ++
	      	HOLD[3] = number + '0';            //   ++
	        wrtchrs(4);               //   ++
	 }                            //   ++


} 

/* WRITE STRING TO DISPLAY */
void wrtstring(char *STRING)
{
    int i;    
	wait(2);
	port00 = 1;
	wait(16);
	i=0;
	while( STRING[i] ) {
		wait(2);
		chr = STRING[i];					
		port01 = chr;
	 	i++;
	 }
}

/* WRITE CHARACTERS TO DISPLAY */
void wrtchrs(short chrs)
{
    int i;    
	wait(2);
	port00 = PLACE + 128;	
	for( i = 0; i < chrs; i++ ) {
		wait(2);
		wt = 0;
		wt = 0;
		port01 = HOLD[i];		
	}
} 

/*************************** SUPPORTING SUB ROUTINES **************************/
/*1. GETTEMP */
unsigned short GETTEMP(float adcts)
	{
	float rdif, rdelta, temp;

	temp = (((adcts)/(1023.0 - adcts)) * 4990.0);
	if(temp > 9999) temp = 9999;    	
   	Iindex = 50;			//	 FIND PLACE IN TABLE
	while(TEMPTBL1[Iindex] < temp) if(Iindex) Iindex--;
		
	rdif = (TEMPTBL1[Iindex] - TEMPTBL1[Iindex+1]);
	rdelta = temp - TEMPTBL1[Iindex+1];

	temp = (Iindex -(rdelta / rdif) + 11);	/* CALCULATE TEMP */
	return(temp * 10);
	}

/*2. TEMPERATURE CONTROL ROUTINES */
void tempctl(void)
{
	short temp1, error;
	float ttemp;

	if( !(*ADCTRL2 & 0x1000) )    // MAKE SURE ADC READY
		{ 
		//ENVIR =		(*RESULT0>>7) & 0x3FF;    //环境
	//	T1 =		(*RESULT1>>7) & 0x3FF;	   //2倍频
	//	T2 =		(*RESULT2>>7) & 0x3FF;    //3倍频 A14中用为laserpower
	//	EXTDCUR2=	(*RESULT3>>7) & 0x3FF;    //diodecur2
	//	T4 =		(*RESULT4>>7) & 0x3FF;    //diode1
	//	T5 =		(*RESULT5>>7) & 0x3FF;		//diode2
	//	T6 =		(*RESULT6>>7) & 0x3FF;     //lasertemp
	//	EXTDCUR =	(*RESULT7>>7) & 0x3FF;     //diodecur
		ENVIR =		((((*RESULT0>>6)+(*RESULT8>>6))>>1) & 0x3FF);
		T1 =		((((*RESULT1>>6)+(*RESULT9>>6))>>1) & 0x3FF);
		T2 =		((((*RESULT2>>6)+(*RESULT10>>6))>>1) & 0x3FF);
		EXTDCUR2 =	((((*RESULT3>>6)+(*RESULT11>>6))>>1) & 0x3FF);
		T5 =		((((*RESULT4>>6)+(*RESULT12>>6))>>1) & 0x3FF);
		T4 =		((((*RESULT5>>6)+(*RESULT13>>6))>>1) & 0x3FF);
		T6 =		((((*RESULT6>>6)+(*RESULT14>>6))>>1) & 0x3FF);
		EXTDCUR =	((((*RESULT7>>6)+(*RESULT15>>6))>>1) & 0x3FF);
		//T9=			((((*RESULT8>>6))>>1) & 0x3FF);    //laserpower
   		}	
	/*** START ADC SEQUENCE ***/
    *ADCTRL2 = *ADCTRL2 | 0x4000;
    wt = 0;
    *ADCTRL2 = *ADCTRL2 | 0x2000;
	
	if(DIMAX > 250)	{*T3CMPR = (DIODECUR<<2); *CMPR6= (DIODECUR2<<2);}
	else {*T3CMPR = (DIODECUR<<2);*CMPR6= (DIODECUR2<<2);}

	*CMPR1 = (2000 - ((XTL1SET - 260) * 5.88));   //2000,400
	*CMPR2 = (2000 - ((XTL2SET - 260) * 5.88));
	XTL1ACT = ((T1 / 2.4) + 260);                 //4.8,400
	XTL2SET=XTL2ACT = 260;
	    
	ENVACT = GETTEMP(ENVIR);  //8/29

	/*if(DIODECUR2=0)*/
	/*LASERPOWERZERO=LASERPOWER;*/
	LASERPOWER = (float)T2*33*2 *10/0x3FF;  //tang
    /*
    if(*PBDATDIR & 0X0040)
    	{
    	*PBDATDIR = (*PBDATDIR & ~0X0040);
    	ENVACT = temp1;
    	}
    else
    	{
    	*PBDATDIR = (*PBDATDIR | 0X0040);
		D2_ACT = temp1;
		}
		*/
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    LASACT=GETTEMP(T6);					//8/29 t3-->t4
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	D1_ACT = GETTEMP(T4);					//8/29 t3-->t4

/*	if(D2_ACT < D2_SET) *CMPR4 = 2000;
	else
		{
		error = (D2_ACT - D2_SET);
		TEMP = (error * LHT_PG);
		TEMP = TEMP + (error * LHT_PG);							// PROP. TERM	
		LHT_I = LHT_OLDI + (LHT_IG * (error + OLD_ERROR_L)); 	// INTEGER TERM
		if(LHT_I > 1500) LHT_I = 1500;
		else if( LHT_I < -1500) LHT_I = -1500;				
		
		LHT_D = (LHT_DG * error);								// DIFF. TERM				
		OLD_ERROR_L = error;
		LHT_OLDI = LHT_I;
		TEMP = TEMP + LHT_I + LHT_D;
		TEMP = 2000 - TEMP;  // reverse output.
		if( TEMP < 100 ) TEMP += 50;
		if( TEMP < 0 ) TEMP = 0;
		*CMPR4 = TEMP;
		}
*/			
	if( D1_ACT < 150) *T1CMPR = 0;
	if( D1_ACT > 300 ) *T1CMPR = 1500;
	
	/* Error is reference - current */
	D1_ERROR = (( D1_ACT - D1_SET)/10);		/* CALCULATE ERROR */
	D1_PROP = D1_ERROR * Kp;				/* PROPORTIONAL TERM*/				
	D1_INT = OLD_D1_INT + (Ki * (D1_ERROR + OLD_ERROR));  /* INTEGER TERM */
	/* anti-windup test. NEED TO SET PROPER CUTOFF. */
	if( D1_INT > 900 )	D1_INT = 900;
	else if( D1_INT < -900) D1_INT = -900;	
	D1_DIF = Kd * (D1_ERROR - OLD_ERROR);			/* DIFFERENTIAL TERM*/
	/* Update history */
	OLD_ERROR = D1_ERROR;
	OLD_D1_INT = D1_INT;			
	/* Output the value. */
	D1_OUT = (D1_PROP + D1_INT + D1_DIF);		/* ADDED OLD OUTPUT(D1_OUT + */
	if( D1_OUT > 2000 ) D1_OUT = 2000;			
	if( D1_OUT < 0 ) D1_OUT = 0;		
	if( (D1_OUT - D1_OUT_OLD) > smooth )
		{
		D1_OUT_OLD += smooth;
		D1_OUT = D1_OUT_OLD;
		} 
	if( (D1_OUT - D1_OUT_OLD) < -smooth )
		{
		D1_OUT_OLD -= smooth;
		D1_OUT = D1_OUT_OLD;
		}
	D1_OUT_OLD = D1_OUT;	
	*T1CMPR = D1_OUT; //8/29
	
	D2_ACT=GETTEMP(T5);
	if( D2_ACT < 150) *T4CMPR = 0;
	if( D2_ACT > 300 ) *T4CMPR = 1500;
	
	/* Error is reference - current */
	FanLaser_ERROR = (( D2_ACT - D2_SET)/10);		/* CALCULATE ERROR */
	FanLaser_PROP = FanLaser_ERROR * Kp;				/* PROPORTIONAL TERM*/				
	FanLaser_INT = OLD_FanLaser_INT + (Ki * (FanLaser_ERROR +FanLaser_OLD_ERROR));  /* INTEGER TERM */
	/* anti-windup test. NEED TO SET PROPER CUTOFF. */
	if( FanLaser_INT > 900 )	FanLaser_INT =  900;
	else if( FanLaser_INT < -900) FanLaser_INT =  -900;	
	FanLaser_DIF = Kd * (FanLaser_ERROR -FanLaser_OLD_ERROR);			/* DIFFERENTIAL TERM*/
	/* Update history */
	FanLaser_OLD_ERROR = FanLaser_ERROR;
	OLD_FanLaser_INT = FanLaser_INT;			
	/* Output the value. */
	FanLaser_OUT = (FanLaser_PROP + FanLaser_INT + FanLaser_DIF);		/* ADDED OLD OUTPUT(D1_OUT + */
	if( FanLaser_OUT > 2000 ) FanLaser_OUT = 2000;			
	if( FanLaser_OUT < 0 ) FanLaser_OUT = 0;		
	if( (FanLaser_OUT - FanLaser_OUT_OLD) > smooth )
		{
		FanLaser_OUT_OLD += smooth;
		FanLaser_OUT = FanLaser_OUT_OLD;
		} 
	if( (FanLaser_OUT - FanLaser_OUT_OLD) < -smooth )
		{
		FanLaser_OUT_OLD -= smooth;
		FanLaser_OUT = FanLaser_OUT_OLD;
		}
	FanLaser_OUT_OLD = FanLaser_OUT;	
	*T4CMPR = FanLaser_OUT; //8/29

	ADTIMER = 2000;	//tanga2			/* reset timer 100 milliseconds*/
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
} 

/*3. WriteData */
void WriteDatax()
{
	int i;
	unsigned long PR,PR1;
	unsigned short temp,temp1;	 
	*EVAIMRA = 0x0000;         /* DISable desired EVA group A interrupts  tang*/
	*MCRB = 0xFF1C;
	*PFDATDIR = (*PFDATDIR | 0x0040);		/* ENABLE TIMEKEEPER */
	WriteDallas2(0x7F, 1);		// Write command
	WriteDallas2( XTL1SET,0);
	WriteDallas2( (unsigned short)DIMAX, 0 ); 
	PR = PULSERATE;
	temp = (unsigned short)((PR & 0xFFFF0000)>>16);
	WriteDallas2( temp, 0 );
	temp = (unsigned short)(PR & 0xFFFF);
	WriteDallas2( temp, 0 );
	PR1 = PWMTime;            //PWM
	temp1 = (unsigned short)((PR1 & 0xFFFF0000)>>16);
	WriteDallas2( temp1, 0 );
	temp1 = (unsigned short)(PR1 & 0xFFFF);
	WriteDallas2( temp1, 0 );    
	WriteDallas2( D2_SET, 0 );
	WriteDallas2( ENVSET, 0 );
	WriteDallas2( (unsigned short)D1_SET, 0 );

	WriteDallas2( Time, 0 );
//	WriteDallas2( XTL2SET,0);
	WriteDallas2( FPS_ON,0);    //   ++
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	WriteDallas2( (unsigned short)INITCUR, 0 );
	WriteDallas2( (unsigned short)INITCUR2, 0 );
	WriteDallas2( securityenable,0);
	WriteDallas2( (unsigned short)LASSET,0);
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	*PFDATDIR = (*PFDATDIR & ~0x0040);		/* DISABLE TIMEKEEPER */
	*MCRB = 0xFF0C;
	*EVAIMRA = 0x0080;         /* enable desired EVA group A interrupts  tang*/
}  

/*4. WriteDallas2 */
void WriteDallas2( unsigned short Data, short Command )
{
	unsigned short Tdata[2];
	int i, j;
	
	Tdata[0] = (char)((Data & 0x000000FF)<<8);
	Tdata[1] = (char)(Data & 0x0000FF00);
	*SPICTL = 0x0E;						/* TALK ENABLED */
	while(*SPISTS & 0x20);
	if( Command == 1 )
		j = 0;
	else
		j = 1;
		
	for( i = j; i >= 0; i-- ) {
		*SPITXBUF = Tdata[i]; 
		// Wait until read buffer is empty
		// Wait for read buffer not full
		while(!(*SPISTS & 0x40));
		// Read the data
		DUMMY = *SPIRXBUF;
		// Wait for transmit buffer empty
		while(*SPISTS & 0x20);
		// Write the data out
	}
	DUMMY = *SPIRXBUF;
	while(*SPISTS & 0x20);
}

/*5. ReadData */
void ReadDatax()
{
	unsigned long i,i1;
	unsigned long PR,PR1;
	*EVAIMRA = 0x0000;         /* DISable desired EVA group A interrupts  tang*/
	*MCRB = 0xFF1C;
	*PFDATDIR = (*PFDATDIR | 0x0040);		/* ENABLE TIMEKEEPER */
	WriteDallas2(0xFF, 1);		// Write command
	XTL1SET = ReadDallas2( );
	DIMAX = ReadDallas2( );        
	i = ReadDallas2( );
	PR = ((unsigned long)i<<16);
	i = ReadDallas2( );
	PR |= i;
	PULSERATE = PR;
	i1 = ReadDallas2( );  //PWM
	PR1 = ((unsigned long)i1<<16);
	i1 = ReadDallas2( );
	PR1 |= i1; 
	PWMTime = PR1; 
	D2_SET = ReadDallas2( );
	ENVSET = ReadDallas2( );
	D1_SET = ReadDallas2( );
	Time = ReadDallas2( );
	//XTL2SET = ReadDallas2( );
	FPS_ON = ReadDallas2( );      //   ++
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	INITCUR= ReadDallas2( );
	INITCUR2= ReadDallas2( );
	securityenable= ReadDallas2( );
	LASSET = ReadDallas2( );
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	*PFDATDIR = (*PFDATDIR & ~0x0040);		/* DISABLE TIMEKEEPER */
	*MCRB = 0xFF0C;
	*EVAIMRA = 0x0080;         /* enable desired EVA group A interrupts  tang*/
}

/*6. ReadDallas2 */
unsigned short ReadDallas2( )
{
	unsigned short Tdata[2];
	unsigned short Data;
	int i;
	
	*SPICTL = 0x0C;							/* TALK DISABLED */			
	for( i = 1; i >= 0; i-- ) {
		while(*SPISTS & 0x20);						
		*SPITXBUF = 0x0000;					/* DUMMY DATE TO START READ */	
		while(!(*SPISTS & 0x40));			/* WAIT UNTIL DATA READY */
		Tdata[i] = (*SPIRXBUF & 0xFF);		/* GET FIRST 8 BITS */
	}
	Data = 0;
	Data = ( (Tdata[1]<<8) | (Tdata[0]) );		
	*SPICTL = 0x0E;							/* TALK ENABLED */
	return(Data);
}


void ReadData()
{short ENVSET2,i,DIMAX2;
unsigned short securityenable2;
float INITCURa;
unsigned long PULSERATE2,PWMTime2;
  ReadDatax();
  PULSERATE2=PULSERATE;
  PWMTime2=PWMTime;
  ENVSET2=ENVSET;
  INITCURa=INITCUR;
  securityenable2=securityenable;
  DIMAX2=DIMAX;
  ReadDatax();
  i=0;
while(i<3)
{
  if( PULSERATE2!=PULSERATE||PWMTime2!=PWMTime||ENVSET2!=ENVSET||INITCURa!=INITCUR||securityenable2!=securityenable||DIMAX2!=DIMAX)
	ReadDatax();
	 else i=3;	
	i++;//tang 等加报错
	if(i==3)
	{	clearScreen();
		PLACE = 64;
		message(msg25);
		wait(3000);
		dspfun();
	}

}
}

void WriteData()
{short ENVSET2,i,DIMAX2;
unsigned short securityenable2;
float INITCURa,INITCURb,D1_SET2,D2_SET2;
unsigned long PULSERATE2,PWMTime2;
	PULSERATE2=PULSERATE;
  PWMTime2=PWMTime;
  ENVSET2=ENVSET;
  INITCURa=INITCUR;
  INITCURb=INITCUR2;
	D1_SET2	=D1_SET;
	D2_SET2	=D2_SET;
  securityenable2=securityenable;
  DIMAX2=DIMAX;
	WriteDatax();
	ReadDatax();
	 i=0;
	while(i<3)
	{

	  if( PULSERATE2!=PULSERATE||PWMTime2!=PWMTime||ENVSET2!=ENVSET||INITCURa!=INITCUR||INITCURb!=INITCUR2||D2_SET2	!=D2_SET||D1_SET2!=D1_SET||securityenable2!=securityenable||DIMAX2!=DIMAX)
			{
		 	 PULSERATE=PULSERATE2;
 			 PWMTime=PWMTime2;
		 	 ENVSET=ENVSET2;
 			 INITCUR=INITCURa;
			 INITCUR2=INITCURb;
		     D1_SET	=D1_SET2;
			 D2_SET	=D2_SET2;
 			 securityenable=securityenable2;
 			 DIMAX=DIMAX2;
			WriteDatax();
			ReadDatax();
			}
		 else 
			 i=3;	
		i++;
		if(i==3 && wrf==0)
		{	
		clearScreen();
		PLACE = 64;
	 	message(msg31);
		wait(3000);

		dspfun();

		
		}
	}	
}
/*7. LCDSetup */
void LCDSetup()
{
	wait(15);
    port00 = 0x0038;		
    wait(5);
    port00 = 0x0038;		
    wait(2);
    port00 = 0x0038;
    wait(2);
    port00 = 0x0014;
    wait(2);
    port00 = 0x0008;		
    wait(2);
    port00 = 0x0006;		
    wait(2);
    port00 = 0x0001;
	return;
}

/*8.LCDRefrech */
void LCDRefresh(long * pDspTmr)
{	
	if( ((*pDspTmr) >= 3600) )
		{
		Time++;
		WriteData();
		if( (FUNCTION == 1) ) dspfun();
		*pDspTmr = 0;
		}
	//Normal Display: FUNCTION==0 or REMOTE
	if(((!FUNCTION)&&(clearWarning==0))||(REMLOC==1))
	{
		PLACE = 71;
		if(!QSWEXT) num2ascii(PULSERATE,1);
		PLACE = 79;
		if(!QSWEXT) num2ascii(PWMTime,9);    //PWM
		else
		{
			PLACE = 71;
			EXTFREQ = (FREQ<<1);
			FREQ = 0;
			HOLD[0]='E';
			HOLD[1]='X';
			HOLD[2]='T';	
			HOLD[3]=' ';	
			wrtchrs(4);
		}
		PLACE = 25;
		num2ascii(DIODECUR,0);
	//rev6	PLACE=5 ;
//rev6		num2ascii(DIODECUR2,0);
		PLACE = 35;	
			if(DIODECUR < 12) EXTDCUR = (DIODECUR<<1);
				DIODECUR_ACT =EXTDCUR>>1;
				num2ascii(DIODECUR_ACT, 0);
				//rev6	PLACE= 15;
				if(DIODECUR2 < 12) EXTDCUR2 = (DIODECUR2<<1);
				DIODECUR_ACT2 =EXTDCUR2>>1;
			//rev6		num2ascii(DIODECUR_ACT2, 0);
	}
	
	LOOP = 10000;
	//FUNCTION==0 and TPFLAG==0
	if(!FUNCTION && !TPFLAG && (clearWarning==0))
	{
		if(QSWEXT)
		{
			PLACE = 71;
			EXTFREQ = (FREQ<<1);
			FREQ = 0;
			HOLD[0]='E';
			HOLD[1]='X';
			HOLD[2]='T';	
			HOLD[3]=' ';	
			wrtchrs(4);
			//num2ascii(EXTFREQ,1);
		}
		/*
		PLACE = 35;
		if(DIMAX > 250)
		{
			if(DIODECUR < 12) EXTDCUR = (DIODECUR<<2);
			DIODECUR_ACT =EXTDCUR>>2;
			num2ascii(DIODECUR_ACT, 0);
		}
		else
		{	
			if(DIODECUR < 6 ) EXTDCUR = (DIODECUR<<3);
			DIODECUR_ACT =EXTDCUR>>3;
			num2ascii(DIODECUR_ACT, 0);
		}
		*/
	}
	else
	{
		/* Output the actual temperature to the display. */
   		//DDD
   		if(FUNCTION==2)
   		{ 	
   			if((FPS_ON==0)||(FPS_ON==1))
   			FPS_LEVEL=100;
   			if(MODE_SEL==0)   		
   			{
   				PLACE = 25;   		
	 			HOLD[0]=FPS_ON+'0';
   	 			wrtchrs(1);
   	  			PLACE = 33;
	 			num2ascii(((short)(FPS_LEVEL/5))*10, 0);	 		 		 
	 		}
	 		else
	 		{	 	
   	  			PLACE = 33;
	 			num2ascii(((short)(FPS_LEVEL/5))*10, 0);	 		 		 
	 			PLACE = 25;   		
	 			HOLD[0]=FPS_ON+'0';
   	 			wrtchrs(1);
	 		}
	 	
   			if(MODE_SEL==1)
	 		{
	 			PLACE=26;
	 			port00 = PLACE+128;
	 			wait(20);
	 			port00=0x000F;  //turn off cursor and blink   		
	 		}
	 		else
	 		{	 	
	 			PLACE=37;
	 			port00 = PLACE+128;
	 			wait(20);
	 			if(MODE_DONE==0)
	 			port00=0x000F;  //turn off cursor and blink   		
	 		}	 	
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		if(FUNCTION==8)
		{
			if(SIGN_FUN8SET==0)
			{
				PLACE = 35;
		 		num2ascii(INITCUR, 0);
				PLACE = 99;
	 			num2ascii(INITCUR2, 0);//tang
	 			PLACE = 79;
	 			num2ascii(DIMAX, 0);
	 	     		PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++

	 			wait(20);
				port00 = 0x000C;
			}
			if(SIGN_FUN8SET==1)
			{
				PLACE = 35;
		 		num2ascii(INITCUR, 0);
				PLACE = 99;
	 			num2ascii(INITCUR2, 0);//tang
	 			PLACE = 79;
	 			num2ascii(DIMAX, 0);
	 	     	PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++

	 			wait(20);
				port00 = 0x000F;
			}
			if(SIGN_FUN8SET==2)
			{
				PLACE = 35;
		 		num2ascii(INITCUR, 0);
	 	 		PLACE = 99;
	 			num2ascii(INITCUR2, 0);//tang
	 	     	PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++

				PLACE = 79;
	 			num2ascii(ADJUST, 0);
	 			wait(20);
				port00 = 0x000F;
			}
			if(SIGN_FUN8SET==3)
			{
	 			PLACE = 79;
	 			num2ascii(DIMAX, 0);
	 		 	PLACE = 99;
	 			num2ascii(INITCUR2, 0);//tang
	 	     	PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++

				PLACE = 35;
		 		num2ascii(ADJUST, 0);
	 			wait(20);
				port00 = 0x000F;  //tang del set4
			}
		
	if(SIGN_FUN8SET==4)
			{
	 			PLACE = 79;
	 			num2ascii(DIMAX, 0);
	 	 	
	 	     	PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++

				PLACE = 35;
		 		num2ascii(INITCUR, 0);
				PLACE = 99;
	 			num2ascii(ADJUST, 0);//tang
	 			wait(20);
				port00 = 0x000F;  //tang
			}

		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%		
   		PLACE = 25;
   		if(FUNCTION == 3) num2ascii(D1_ACT, 0);
    	else if(FUNCTION == 9) num2ascii(ENVACT, 0);
   		else if(FUNCTION == 5) num2ascii(D2_ACT, 0);
   		else if(FUNCTION == 6) num2ascii(XTL1ACT, 0);
		else if(FUNCTION == 11)  num2ascii(LASACT, 0);
   		else if(FUNCTION == 7) num2ascii(XTL2ACT, 0);
		else if (FUNCTION == 4) 
		{
				if(DIODECUR2 < 12) EXTDCUR2 = (DIODECUR2<<1);
				DIODECUR_ACT2 =EXTDCUR2>>1;
	
			num2ascii(DIODECUR_ACT2, 0);
			PLACE = 98;	
			num2ascii((short)LASERPOWER, 7);
			}

		else if (FUNCTION == 10)	
		{PLACE =30;
		num2ascii((short)LASERPOWER, 7);}//tang
		wait(20);
	   	if((FUNCTION!=2) && (FUNCTION!=8)&& (FUNCTION!=9))        
		{	
   				PLACE=39;
	 			port00 = PLACE+128;
	 			wait(20);
	 			port00=0x000F;  //turn off cursor and blink 
		}
   		wait(15);
	}
	return;
}	
