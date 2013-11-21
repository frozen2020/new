#include "constants.h"
#include "extern.h"
#include "Proto.h"

/*************************** ACTIONS ON PARAMETER CHANGES **************************/
void clearstring()
{  
    clearWarning=1;
	//clearScreen();
	if(*PADATDIR & 0x0020)	//KEYSWITCH
	{
	wait(2);
	//PLACE = 65;
	PLACE = 85;
	if(SecurityIniting==1)
	{
		message(msg24);
	}
	else
	{
		message(msg16);
	}
	}
	else RESET = 1;
}

/*1. shutterOff */
void shutterOff()
{
	//SHT_ON LED OFF:
	*PBDATDIR = *PBDATDIR | 0x0008; 	
	(*PEDATDIR = *PEDATDIR | 0x0014);  /* Shutter off */
	*CMPR5 = 800; /* Fan HALF SPEED */
	(*PFDATDIR = *PFDATDIR | 0x0003);	
}	

/*2. qswonAction */
void qswonAction()
{ 
	if( QSWON )
  	{
  	//QS_ON LED ON:
  	*PBDATDIR = *PBDATDIR & 0xFFFD;   	
  	(*PFDATDIR = *PFDATDIR & ~0x0010);/* Turn on QSWITCH DRIVER */
	}
	else
	{	
   	*PBDATDIR = *PBDATDIR | 0x0002;
   	(*PFDATDIR = *PFDATDIR | 0x0010); /* Turn off QSWITCH DRIVER */
   	}
}   	 	

/*2.1 */
void alarmAction()
{ 
	QSWON=0;
  	*PBDATDIR = *PBDATDIR | 0x0002;
   	(*PFDATDIR = *PFDATDIR | 0x0010); /* Turn off QSWITCH DRIVER */   	
   	RF_OFF=1;
   	diodeAction();
}   	 						

/*2.2 */
void resetAction()
{ 
	//QSWON=0;
  	//*PBDATDIR = *PBDATDIR & 0xFFFD;   	
  	//(*PFDATDIR = *PFDATDIR & ~0x0010);/* Turn on QSWITCH DRIVER */
  	QSWON=0;
  	*PBDATDIR = *PBDATDIR | 0x0002;
   	(*PFDATDIR = *PFDATDIR | 0x0010); /* Turn off QSWITCH DRIVER */  
   	RF_OFF=1;
   	//*GPTCONA = 0x6046;//++xiao
   	diodeAction(); 	
}   	 						

/*3. pulseRateAction */
void pulseRateAction()
{
	if( PULSERATE > 999 )
  	{
  	*T2CON = 0x9042;  //timer 2 control
   	*T2PR = (40000000 / PULSERATE);
   	*T2CMPR = PWMTime / 20;  //40,1us: gen pulse PWM tanga2
	//*T2CMPR = PWMTime;
	}
	else
	{
   	*T2CON = 0x9642;
   	*T2PR = (625000 / PULSERATE);
   	*T2CMPR = 1;
   	}
}   					

/*4. keyswOffAction*/
void keyswOffAction (short *pSaveQSExt, short * pSaveQSOn, short * pkey)
{
	BEEPER = 0;
	*pSaveQSExt = QSWEXT;
	*pSaveQSOn = QSWON;
	DIODECUR=DIODECUR2 = 0;
	*T3CMPR = 0;
	*CMPR6 = 0;
	//RF_OFF=1; //?
	
	*CMPR4 = 0;							/* LASER FAN OFF */
	*CMPR5 = 1000; 						/* DRIVER Fan HALF SPEED */
	*T1CMPR = 0;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	*T4CMPR = 0;  				
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	port00 = 0x0008;
	wait(20);
	*pkey = 0;
	SHTON = 0;
	*PBDATDIR = *PBDATDIR | 0x0008; 
	(*PEDATDIR = *PEDATDIR | 0x0014); 	/* Shutter off */
	QSWEXT = 0;							/* QSwitch to internal. */	
	//QS_EXT OFF:
	*PADATDIR = *PADATDIR | 0x0080;	/* QSwitch internal LED */
	
	QSWON = 0;							/* QSwitchto off mode. */	
	*PBDATDIR = *PBDATDIR | 0x0002; 
	(*PFDATDIR = *PFDATDIR | 0x0010); 	/* Turn off the RF power. */
	WriteFlag = 1;
	return;
}

/*5. qswextAction */
void qswextAction ()
{
	if( QSWEXT )
   	{
   	*T2CON = 0x8042;			/* STOP COUNTER */		
   	*GPTCONA = 0x6042;			/* TURN OFF LASER */
   	*T2CNT = 0;
   	//*EVAIFRB = 0x0002;			
   	//*EVAIMRB = 0x0002;			/* CLEAR ANY PENDING INTERRUPT */
   	*XINT1CR = 0x8000;			
	TFLAG = 0;
   	*PADATDIR = *PADATDIR | 0xC100; 
   	//QS_EXT ON:
	*PADATDIR = *PADATDIR & 0xFF7F;  	
	
   	(*PBDATDIR = *PBDATDIR & ~0x0080);
   	HOLD[0] = 'E';
   	HOLD[1] = 'X';
  	//wrtchrs(2);
  	//HOLD[0] = HOLD[1] = HOLD[2] = HOLD[3] = HOLD[4] = ' ';
  	PLACE = 88;
  	wrtchrs(2);
	}
	else
	{
   	*XINT1CR = 0x8000;			/* DISABLE EXTERNAL INTERRUPT */	
   	*GPTCONA = 0x6046;
   	*T2CON = 0x9042;
   	*EVAIMRA = 0x0080;
   	
   	//QS_EXT OFF:
	*PADATDIR = *PADATDIR | 0x0080;	/* QSwitch internal LED */
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
	(*PBDATDIR = *PBDATDIR | 0x0080);
   	HOLD[0] = 'I';
   	HOLD[1] = 'N';
  	//wrtchrs(2);
  	PLACE = 88;
  	wrtchrs(2);
  	PLACE = 71;
  	num2ascii(PULSERATE, 1);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//*T4CMPR = 100;			/* Maximum output for driver. */
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	return;
}					

/*6. shtonAction */
void shtonAction()
{
    PLACE=97;
	if( SHTON )
   	{
   	*PBDATDIR = *PBDATDIR & 0xFFF7;
   	(*PEDATDIR = *PEDATDIR & ~0x0004); /* Shutter on */
   	HOLD[0] = 'N';
   	HOLD[1] = ' ';
   	wrtchrs(2);
	}
	else
	{
   	*PBDATDIR = *PBDATDIR | 0x0008;
	(*PEDATDIR = *PEDATDIR | 0x0004); /* Shutter off */
   	HOLD[0] = 'F';
   	HOLD[1] = 'F';
   	wrtchrs(2);
	}
	return;
}						


/*6. defaultAction */
void defaultAction(short * perrFlag, short * pwrFlag)
{ 
	if (ENVACT > ENV_MAXTEMP)	/* Turn on beeper. */
	{	
	alarmAction();
	DIODECUR=DIODECUR2 = 0;	
	BEEPER = 1;
	port00 = 01;
	wait(20);
	PLACE = 0;
	clearScreen();
	message(msg10);
	PLACE = 70;
	message(msg14);
	while((ENVACT > ENV_MAXTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;	
	}	
	else if(ENVACT < ENV_MINTEMP)	/* Turn on beeper. */
 	{ 	
 	alarmAction();
	DIODECUR=DIODECUR2 = 0;
	BEEPER = 1;
	clearScreen();
	message(msg10);
	PLACE = 70;
	message(msg15);
	while((ENVACT < ENV_MINTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;	
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//else if (D2_ACT > (D2_SET + 20)) /* Turn on beeper. */
	else if (D2_ACT > D2_MAXTEMP) /* Turn on beeper. */
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	{
	alarmAction();
	DIODECUR=DIODECUR2 = 0;
	BEEPER = 1;
	clearScreen();
	wait(20);
	message(msg30);
	PLACE = 70;
	message(msg14);
	while((D2_ACT > D2_MAXTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;	
	}
	else if(D2_ACT < D2_MINTEMP) /* Turn on beeper. */
	{
	alarmAction();
	DIODECUR=DIODECUR2 = 0;
	BEEPER = 1;
	clearScreen();
	message(msg30);
	PLACE = 70;
	message(msg15);
	while((D2_ACT < D2_MINTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;
	}

	else if (LASACT > (LASSET + 20)) /* Turn on beeper. */

	{
	alarmAction();
	DIODECUR = 0;
	BEEPER = 1;
	clearScreen();
	wait(20);
	message(msg11);
	PLACE = 70;
	message(msg14);
	while((LASACT > LASSET) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;	
	}
	else if(LASACT < LAS_MINTEMP) /* Turn on beeper. */
	{
	alarmAction();
	DIODECUR = 0;
	BEEPER = 1;
	clearScreen();
	message(msg11);
	PLACE = 70;
	message(msg15);
	while((LASACT < LAS_MINTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;
	}
	else if (!(*PADATDIR & 0x0010))    /* INTERLOCK OPEN ERROR */
	{
	alarmAction();
	DIODECUR=DIODECUR2 = 0;
	BEEPER = 1;
	clearScreen();	
	message(msg12);
	while((!(*PADATDIR & 0x0010)) && KEYSW_ON);
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;
	}
	else if(D1_ACT > D1_MAXTEMP)
	{	
	alarmAction();
	BEEPER = 1;
	DIODECUR=DIODECUR2 = 0;				/* TURN OFF LASER */
	clearScreen();
	wait(20);
	message(msg13);
	PLACE = 70;
	message(msg14);
	while((D1_ACT > D1_MAXTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;
	}
	else if(D1_ACT < D1_MINTEMP)
	{
	alarmAction();
	BEEPER = 1;
	DIODECUR=DIODECUR2 = 0;				/* TURN OFF LASER */
	clearScreen();
	wait(20);
	message(msg13);
	PLACE = 70;
	message(msg15);
	while((D1_ACT < D1_MINTEMP) && KEYSW_ON)
	{
	if( !ADTIMER )	tempctl();
	}
	clearstring();
	TPFLAG = 1;
	FUNCTION = 0;
	}
	
	if( TPFLAG && (*perrFlag) )
	{
	BEEPER = 0;
	if(SecurityIniting==1)
	{
		InitingError=1;
	}
	alarmAction();
	*perrFlag = 0;
	DIODECUR=DIODECUR2 = 0;						/* Set diode current to zero. */
	Diode_SetPt =Diode_SetPt2= 0;
	SHTON = 0;							/* Turn off the shutter */
	*PBDATDIR = *PBDATDIR | 0x0008;
	(*PEDATDIR = *PEDATDIR | 0x0004); 	/* Shutter off */
   	QSWEXT = 0;							/* Set the QSwitch to internal. */
	//QS_EXT OFF:
	*PADATDIR = *PADATDIR | 0x0080;
	
	(*PBDATDIR = *PBDATDIR | 0x0080);
  	QSWON = 0;							/* Set the QSwitch On to off mode. */
  	*PBDATDIR = *PBDATDIR | 0x0002; 
	//*GPTCONA = 0x6042;//++xiao
	(*PFDATDIR = *PFDATDIR | 0x0010); 	/* Turn off the RF power. */
	}
	if( RESET )
	{
	resetAction();
	RESET = 0;
	TPFLAG = 0;
	*pwrFlag = 1;
	*perrFlag = 1;
	FUNCTION = 0;
	PLACE = 0;
	message(msg1);
	PLACE = 64;
	message(msg2);
	PLACE = 71;
	num2ascii(PULSERATE, 1);
	PLACE = 25;
	num2ascii(DIODECUR, 0);
//rev6	PLACE =5;
//rev6	num2ascii(DIODECUR2, 0);
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
	PLACE = 88;
	HOLD[0] = 'I';
   	HOLD[1] = 'N';
  	wrtchrs(2);
	PLACE = 102;
	HOLD[0] = 'O';
   	HOLD[1] = 'C';
   	wrtchrs(2);
	}   
	return;			 
}   			

/*7. keyswFirstOnAction */
void keyswFirstOnAction(short * psettleDelay, short * pSaveQSExt,short * pSaveQSOn)
{
	
	ReadData();
	
	*PEDATDIR = *PEDATDIR | 0x0010;

	WriteFlag = 0;
	//*psettleDelay = 200;	// Wait 2 minutes for laser temp to settle.
	*psettleDelay = 3000;	// Wait 2 minutes for laser temp to settle.
	PLACE = 0;
	port00 = 01;
	wait(20);
	message(msg17);	
	/*WAIT FOR SETTLING DELAY*/
	while((*psettleDelay) && ( KEYSW_ON ))
	{
		wait(10);
		if( !ADTIMER )	tempctl();
		(*psettleDelay)--;
	}
	
	JumpInit=0;
	PLACE = 0;
	port00 = 01;
	wait(20);
	message(msg26);	
	port00 = 0x000C;
	wait(1);
	PLACE = 34;
	num2ascii(3, 3);
	*PCDATDIR = ~0x0F40;	
	LOOP=60000;
	while((LOOP)&& ( KEYSW_ON ))
	{if(!(*PFDATDIR & 0x0001))
		{
		JumpInit=1;
		LOOP=0;
		}
	 if((LOOP<40000)&&(LOOP>=39900))
	 	{port00 = 0x000C;
		wait(1);
	 	PLACE = 34;
		num2ascii(2, 3);
		}		 
		 if(LOOP<20000&&(LOOP>=19900))
	 	{port00 = 0x000C;
		wait(1);
	 	PLACE = 34;
		num2ascii(1, 3);
		}
	}
	

	First();

	if(!KEYSW_ON)
	{
		port00 = 01;
		wait(20);
	}
	else
	{
		FUNCTION = 0;
		port00 = 0x000C;
		wait(1);
	
		PLACE = 0;				// Key switch was just turned on
		message(msg1);			// SIGN ON MESSAGE
		PLACE = 64;
		message(msg2);
		PLACE = 71;
		num2ascii(PULSERATE, 1);
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
		
		
		
/*		
		*psettleDelay = 1000;
			while(*psettleDelay)
	{
		wait(10);

		(*psettleDelay)--;
	}
	
	*/
	
	
	*PBDATDIR = *PBDATDIR | 0x0008;
	//(*PEDATDIR = *PEDATDIR & ~0X0010);	// ENABLE POWER SUPPLY
	(*PEDATDIR = *PEDATDIR | 0x0004); /* Shutter off */
	*CMPR4 = 2000;							/* LASER FAN ON */
	*CMPR5 = 0; 						/* DRIVER Fan on */ 
	TPFLAG = 0;
	QSWEXT = (*pSaveQSExt);
	if( QSWEXT )
		{
		//QS_EXT ON:
		*PADATDIR = *PADATDIR & 0xFF7F;  			
		(*PBDATDIR = *PBDATDIR & ~0x0080);
		PLACE = 88;
		HOLD[0] = 'E';
		HOLD[1] = 'X';
		wrtchrs(2);		
		/* In external mode do not display frequency. */
		HOLD[0] = HOLD[1] = HOLD[2] = HOLD[3] = HOLD[4] = ' ';
		PLACE = 71;
		wrtchrs(5);
		}
		//QSWON = (*pSaveQSOn);
		
		QSWON=0;		
		*PBDATDIR = *PBDATDIR | 0x0002; 
		(*PFDATDIR = *PFDATDIR | 0x0010); 	/* Turn off the RF power. */
	
		if( QSWON )
			{
 			(*PFDATDIR = *PFDATDIR & ~0x0010);	/* Turn on QSWITCH DRIVER */
		 	*PBDATDIR = *PBDATDIR & 0xFFFD;
		 	}
		 	
		/* don't ramp when key switch on. Current is controller by Diode_On button */
	    DIODECUR = Diode_SetPt;
		DIODECUR2=Diode_SetPt2;
	    PLACE = 25;
		num2ascii(DIODECUR, 0);
//rev6		PLACE =5;
//rev6		num2ascii(DIODECUR2, 0);
				 	
		/*
		while(DIODECUR < Diode_SetPt)			// ramp the diode current
			{
			DIODECUR++;      				
			if(DIMAX > 250)	*T3CMPR = (DIODECUR<<2);
			else *T3CMPR = (DIODECUR<<2);
		 	wait(100);
			PLACE = 25;
		 	num2ascii(DIODECUR, 0);
		 	} */
		}
		OLD_KEYSW_ON = 1;
		return;
}					

/*8. functionAction */
void functionAction(short * pFuncFlg)
{   //if(FUNCTION!=10)
	//{
/*   ENTER FUNCTION DATA   */
	if( (!(*PFDATDIR & 0x0002)) && (FUNCTION > 1) )
	{
	wait(10);
	if( !(*PFDATDIR & 0x0002) )
	{
	if(FUNCTION == 3) D1_SET = ADJUST;
	
	else if((FUNCTION == 2) && (MODE_SEL==1)) 
	{FPS_ON=ADJUST;
	MODE_DONE=0;
	if((FPS_ON==0)||(FPS_ON==1))
	ADJUST=100;
	else
	ADJUST=FPS_LEVEL;
	}
   	else if((FUNCTION == 2) && (MODE_SEL==0)) 
   	{FPS_LEVEL=ADJUST;
   	port00=0x000C;
   	wait(20);
   	MODE_DONE=1;
   	}	
	else if(FUNCTION == 9) ENVSET = ADJUST;
	else if(FUNCTION == 5) D2_SET = ADJUST;
	else if(FUNCTION == 6) XTL1SET = ADJUST;
	else if(FUNCTION == 11) LASSET = ADJUST;
	else if(FUNCTION == 10)
	{	//if(!RF_OFF)  baocuo
		if	(POS_NEW==0)
 		{
			 *PEDATDIR |= 0x000A;
			 *PBDATDIR |= 0x0040;
			 MOTORSTART=0;
 		}

 		else 
		{ 	STEPCOUNT=(POS_NEW-POS_OLD)*10000;
			*PEDATDIR &= 0xFFF7;
			  MOTORSTART=1;
				*PCDATDIR = 0xF0F0;   //tang suojianpan
				while(POS_NEW!=0);
		}
	}
	else if(FUNCTION == 7) XTL2SET = ADJUST;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//else DIMAX = ADJUST;
	else if((FUNCTION == 8) && (SIGN_FUN8SET==1)) 
	{
		SIGN_FUN8SET=2;
		//securityenable=ADJUST;
		ADJUST = DIMAX;
	}
	else if((FUNCTION == 8) && (SIGN_FUN8SET==2)) 
	{
		SIGN_FUN8SET=3;
		DIMAX=ADJUST;
		ADJUST = INITCUR;
	}
	else if((FUNCTION == 8) && (SIGN_FUN8SET==3)) 
	{
		SIGN_FUN8SET=4;  //tang
		INITCUR=ADJUST;
		ADJUST = INITCUR2;
	}
	else if((FUNCTION == 8) && (SIGN_FUN8SET==4)) 
	{
		SIGN_FUN8SET=0;  //tang
		INITCUR2=ADJUST;

	}
	else if(FUNCTION == 4) 
	   { if( ADJUST > DIMAX ) DIODECUR2 = DIMAX;
			else  DIODECUR2 = ADJUST;
		     if(DIMAX > 250)	*CMPR6 = (DIODECUR2<<2);
		     else *CMPR6 = (DIODECUR2<<2);
	         PLACE = 35;
		     num2ascii(DIODECUR2,0);
			 PLACE = 98;	num2ascii((short)LASERPOWER, 7);
		     Diode_SetPt2= DIODECUR2;
		     }
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	Sctr = 20;
	while( !(*PFDATDIR & 0x0002) )
	{
	wait(500);
	if(Sctr) Sctr--;
	else
		{
		*pFuncFlg = 1;
		BEEPER = 1;
		wait(100);
		BEEPER = 0;
		while( !(*PFDATDIR & 0x0002) );
		}
	}
	
	if(FPS_ON==2)
   	*XINT2CR = 0x8005;
   	else
   	{
   	*XINT2CR = 0x8000; 
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   	//*T4CMPR = 100; 
   	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
   	}	 	   	
   		
	if((FUNCTION == 2) && (MODE_SEL==1))
		{   MODE_SEL=0;
			port00 = 39+128;
	 		wait(2);
			port00 = 0x000F;			
		}
	else	
		{
		wait(20);
		WriteData();
		port00 = 14;
		}	
	}
	}

/* SET ROW 80 STROBE */
	*PCDATDIR = ~0x0F80;	
	wait(1);
/*   FUNCTION SELECT INCREMENT   */
	if( !(*PCDATDIR & 0x0001) )
	{
	wait(10);
	if(	!(*PCDATDIR & 0x0001))
	{ 									
	FUNCTION++;
	if(FUNCTION==2) MODE_SEL=1;	
	
	if(!(*pFuncFlg))
		{if(FUNCTION > 11) FUNCTION = 1;
		if(FUNCTION == 6) FUNCTION = 10;
		if(FUNCTION == 2) FUNCTION = 3;
		}
		else 
		{
		if( FUNCTION < 6) FUNCTION = 9;	
		if( FUNCTION > 9 ) FUNCTION = 6;
 		}
  		WriteData();
  		if( FUNCTION == 3 ) ADJUST = D1_SET;
  		else if((FUNCTION == 2) && (MODE_SEL==1)) ADJUST = FPS_ON;
   	    else if((FUNCTION == 2) && (MODE_SEL==0)) ADJUST = FPS_LEVEL;
  		else if( FUNCTION == 9 ) ADJUST = ENVSET;
  		else if( FUNCTION == 5 ) ADJUST = D2_SET;
  		else if( FUNCTION == 6 ) ADJUST = XTL1SET;
		else if( FUNCTION == 7 ) ADJUST = XTL2SET;
		else if( FUNCTION == 4 ) ADJUST = DIODECUR2;
		else if( FUNCTION == 11 ) ADJUST = LASSET;
		else if( FUNCTION == 10 ) POS_NEW=1;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		else if( FUNCTION == 8 ) //ADJUST = DIMAX;
		{
			SIGN_FUN8SET=1;
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 		dspfun();
 		while( !(*PCDATDIR & 0x0001) );
 		}	
 	}		
		
/*   FUNCTION SELECT DECREMENT   */
	if( !(*PCDATDIR & 0x0002) )
	{
 	wait(10);
 	if( !(*PCDATDIR & 0x0002) )
 		{
		FUNCTION--;
		if(FUNCTION==2) MODE_SEL=1;	
		if(!(*pFuncFlg))
{		if(FUNCTION==2)  FUNCTION =1 ;
		if(FUNCTION ==9)  FUNCTION = 5;
		if(FUNCTION < 1) FUNCTION = 11;
		Sctr = 20;
		while( !(*PCDATDIR & 0x0002) )
			{
			wait(500);
			if(Sctr) Sctr--;
			else
			{
			Time = 0;
			BEEPER = 1;
			wait(100);
			BEEPER = 0;
			}
		}
	}
	else 
		{
		if( FUNCTION < 6) FUNCTION = 9;	
		if( FUNCTION > 9 ) FUNCTION = 6;
 		}
	WriteData();
	if( FUNCTION == 3 ) ADJUST = D1_SET;
	
	else if((FUNCTION == 2) && (MODE_SEL==1)) ADJUST = FPS_ON;
   	else if((FUNCTION == 2) && (MODE_SEL==0)) ADJUST = FPS_LEVEL;
   		
  	else if( FUNCTION == 9 ) ADJUST = ENVSET;
  	else if( FUNCTION == 5 ) ADJUST = D2_SET;
  	else if( FUNCTION == 6 ) ADJUST = XTL1SET;
	else if( FUNCTION == 7 ) ADJUST = XTL2SET;
	else if( FUNCTION == 4 ) ADJUST = DIODECUR2;
	else if( FUNCTION == 11 ) ADJUST = LASSET;
		else if( FUNCTION == 10 ) POS_NEW=1;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	else if( FUNCTION == 8 ) //ADJUST = DIMAX;
	{
		SIGN_FUN8SET=1;
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 	dspfun();
 	while( !(*PCDATDIR & 0x0002) );
	}
	}
		
/*   FUNCTION VALUES INCREASE   */
  	UPDRAT = 10;
  	while( (!(*PFDATDIR & 0x0001)) && (FUNCTION > 1)&&(*PFDATDIR & 0x0002)) // ++)
  		{
   		port00 = 15;
   		wait(20);
   		if((FUNCTION == 2) && (MODE_SEL==0))
   		{
   			if(FPS_ON==2)
   				ADJUST=ADJUST+5;   		
   			else
   				ADJUST=100;
   		}
   		//****************
		else if((FUNCTION == 2) && (MODE_SEL==1))
		{
			;
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==0))
   		{
   			;
   		}
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==1))
   		{
   			;
   		}
			else if(FUNCTION == 10)
   		{
   			POS_NEW+=1;
   		}
   		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		else
   		{ 
   			ADJUST++;
   		}
   		//;
		//****************
   		if((FUNCTION == 3) && (ADJUST > 350)) ADJUST = 300;
   	//fsp//
   	//************************************************************************
   		//else if((FUNCTION == 2) && (MODE_SEL==1) && (ADJUST > 2)) ADJUST = 2;
   	//************************************************************************
   		else if((FUNCTION == 2) && (MODE_SEL==0) && (ADJUST > 100)) ADJUST = 100;
   		//###############################################################
   		//else if((FUNCTION == 4) && (ADJUST > 350)) ADJUST = 350;
   		else if((FUNCTION == 9) && (ADJUST > 400)) ADJUST = 400;
   		//###############################################################
   		else if((FUNCTION == 5) && (ADJUST > 450)) ADJUST = 450;
		else if(FUNCTION == 11)
		{if(ADJUST < LAS_MINTEMP) ADJUST = LAS_MINTEMP;        
   		else if(ADJUST > LAS_MAXTEMP) ADJUST = LAS_MAXTEMP;
		}
		else if(FUNCTION == 10)
		{if(POS_NEW < 1)  POS_NEW = 12;        
   		else if(POS_NEW > 12) POS_NEW = 1;
		}

   		else if((FUNCTION == 6) || (FUNCTION == 7))
   		{
   		if(ADJUST < 260) ADJUST = 260;        //400
   		else if(ADJUST > 600) ADJUST = 600;
   		}
   		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		//else if((FUNCTION == 8) && (ADJUST > 480)) ADJUST = 480;
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==2) && (ADJUST > 480))
   		{
   			ADJUST = 480;
   		}
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==3) && (ADJUST > DIMAX)) 
   		{
   			ADJUST = DIMAX;
   		}
			else if((FUNCTION == 8) && (SIGN_FUN8SET==4) && (ADJUST > DIMAX)) 
   		{
   			ADJUST = DIMAX;
   		}
			else if(FUNCTION == 4)
			{
			if( ADJUST > DIMAX ) ADJUST = DIMAX;
			if( ADJUST < 1 ) ADJUST = 0;
			  DIODECUR2 = ADJUST;
		     if(DIMAX > 250)	*CMPR6 = (DIODECUR2<<2);
		     else *CMPR6 = (DIODECUR2<<2);
			  PLACE = 98;	num2ascii((short)LASERPOWER, 7);
	         PLACE = 35;
		     num2ascii(DIODECUR2,0);
		     Diode_SetPt2= DIODECUR2;
		     }
   		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		if((FUNCTION==2)&&(MODE_SEL==1))
   		{
   			//***********************
   			/*PLACE = 25;   		
	 		HOLD[0]=ADJUST+'0';
   	 		wrtchrs(1);
   	 		FPS_ON=ADJUST;
   	 		if(FPS_ON==2)
   	 			*XINT2CR = 0x8005;
   	 		else
   	 		{
   	 			*XINT2CR = 0x8000; 
   	 			*T4CMPR = 100;  
   	 		}*/
   	 		;
   	 		//***********************	 	   	 	
   	 	}   		
   		else if((FUNCTION==2)&&(MODE_SEL==0))
   		{
   			PLACE = 33;
	 		num2ascii(((short)(ADJUST/5))*10, 0);
	 		FPS_LEVEL=ADJUST;
	 	}
	 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		//else if(FUNCTION==8)          //   +++
   		//{                             //   +++
   		  //PLACE = 80;                 //   +++
   		  //num2ascii(ADJUST, 0);       //   +++
   		  //PLACE = 95;                 //   ++
   		  //num2ascii(QSWEN, 3);        //   ++
   		//}                             //   ++
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==1)) 
		{
			PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++
			wait(20);
			port00 = 0x000F;
		}
		else if((FUNCTION == 8) && (SIGN_FUN8SET==2)) 
		{
			PLACE = 79;
	 		num2ascii(ADJUST, 0);
			wait(20);
			port00 = 0x000F;
		}
		else if((FUNCTION == 8) && (SIGN_FUN8SET==3)) 
		{
			PLACE = 35;
		 	num2ascii(ADJUST, 0);
		 	wait(20);
			port00 = 0x000F;
		}
			else if((FUNCTION == 8) && (SIGN_FUN8SET==4)) 
		{
			PLACE = 99;
		 	num2ascii(ADJUST, 0);
		 	wait(20);
			port00 = 0x000F;
		}
	//tang
		else if(FUNCTION == 10) 
			{ 	PLACE = 17;	
			num2ascii(POS_OLD, 8); 
	//			PLACE = 37;
	//	num2ascii(POS_NEW,8);
		}
   		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	 	else
   		{
   		PLACE = 35;   		
   		num2ascii(ADJUST,0);
   		}
   		if( UPDRAT ) wait(500);
		else wait(50);
		if( UPDRAT ) UPDRAT--;
		}		
/*   DECREASE FUNCTION VALUE   */ 
  		UPDRAT = 10;
  		while( (!(*PFDATDIR & 0x0002)) && (FUNCTION > 1)&&(*PFDATDIR & 0x0001))//++
  		{
    	port00 = 15;
    	wait(20);
    	
    	if((FUNCTION == 2) && (MODE_SEL==0))
    	{
    		if(FPS_ON==2)
    		{
    			if(ADJUST >5) ADJUST=ADJUST-5;
    	  		else ADJUST=0;
    	  	}   		
   			else
   				ADJUST=100;
   		}
   		//****************************************
   		else if((FUNCTION == 2) && (MODE_SEL==1))
		{
			;
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		else if((FUNCTION == 8) && (SIGN_FUN8SET==0))
   		{
   			;
   		}
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==1))
   		{
   			;
   		}
		else if(FUNCTION == 10)
   		{
   		POS_NEW-=1;
   		}
   		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		else
   		{ 
   			if ( ADJUST ) ADJUST--;
   		}    	    	
		//else 
		//{
			//****************************
			//if ( ADJUST ) ADJUST--;
			//;
			//****************************
		//}
		//**********************************
		/*if((FUNCTION == 2) && (MODE_SEL==1)) 
		{
			if (ADJUST <0) FPS_ON=0;
		}
		else if((FUNCTION == 3) || (FUNCTION == 4) || (FUNCTION == 5))*/
		if((FUNCTION == 3) || (FUNCTION == 9) || (FUNCTION == 5))
   	    //**********************************		
   			{
   			if(ADJUST < 150) ADJUST = 150;
   			}
		if(FUNCTION == 4)
		{
			if( ADJUST > DIMAX ) ADJUST = DIMAX;
			if( ADJUST < 1 ) ADJUST = 0;
			  DIODECUR2 = ADJUST;
		     if(DIMAX > 250)	*CMPR6 = (DIODECUR2<<2);
		     else *CMPR6 = (DIODECUR2<<2);
			  PLACE = 98;	num2ascii((short)LASERPOWER, 7);
	         PLACE = 35;
		     num2ascii(DIODECUR2,0);
		     Diode_SetPt2= DIODECUR2;
		  
		}
   		if((FUNCTION == 6) || (FUNCTION == 7))
   			{
   			if(ADJUST < 260) ADJUST = 260;    //400
   			}
			 if(FUNCTION == 11)
		{if(ADJUST < LAS_MINTEMP) ADJUST = LAS_MINTEMP;        
   		else if(ADJUST > LAS_MAXTEMP) ADJUST = LAS_MAXTEMP;
		}
		 	if(FUNCTION == 10)
		{if(POS_NEW < 1)  POS_NEW = 12;        
   		else if(POS_NEW > 12) POS_NEW = 1;
		}
   		if(FUNCTION==2)
   		{	
   			if(MODE_SEL==1)
   			{
   				//******************
   				/*PLACE = 25;
	 			HOLD[0]=ADJUST+'0';
	 			wrtchrs(1);
	 			FPS_ON=ADJUST;*/
	 			;
	 			//******************
	 		}
	 		else
	 		{	 	
	 			PLACE = 33;
	 	    	num2ascii(((short)(ADJUST/5))*10, 0);	 		 		 		
	 	    	FPS_LEVEL=ADJUST;
	 		}
	 	}
	 	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   		//else if(FUNCTION==8)          //   +++
   		//{                             //   +++
   		  //PLACE = 80;                 //   +++
   		  //num2ascii(ADJUST, 0);       //   +++
   		  //PLACE = 95;                 //   ++
   		  //num2ascii(QSWEN, 3);        //   ++
   		//}                             //   ++
   		else if((FUNCTION == 8) && (SIGN_FUN8SET==1)) 
		{
				PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);   
				wait(20);
			port00 = 0x000F;
		}
		else if((FUNCTION == 8) && (SIGN_FUN8SET==2)) 
		{
			PLACE = 79;
	 		num2ascii(ADJUST, 0);
			wait(20);
			port00 = 0x000F;
		}
		else if((FUNCTION == 8) && (SIGN_FUN8SET==3)) 
		{
			PLACE = 35;
		 	num2ascii(ADJUST, 0);
		 	wait(20);
			port00 = 0x000F;
		}
		else if((FUNCTION == 8) && (SIGN_FUN8SET==4)) 
		{
			PLACE = 99;
		 	num2ascii(ADJUST, 0);
		 	wait(20);
			port00 = 0x000F;
		}
	//tang
			else if(FUNCTION == 10) 
			{	PLACE = 17;
			num2ascii(POS_OLD, 8); 
		 	
		//	PLACE = 37;
	//	num2ascii(POS_NEW,8);
		}
   		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
   	 	else
	 	{   		
   		PLACE = 35;
   		num2ascii(ADJUST, 0);
   		}
		if( UPDRAT ) wait(500);
		else wait(50);
		if( UPDRAT ) UPDRAT--;
		}
		
/*   CHANGE QSWEN VALUE   */ 	         //新增加的组合键	
UPDRAT=10;		                                                            //  ++
if(FUNCTION == 8)
{
 while( (!(*PFDATDIR & 0x0002)) && (!(*PFDATDIR & 0x0001))) //  ++		
 {
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //tang
  	if(SIGN_FUN8SET==1)
  	{
    	if(securityenable==0)
    	securityenable=10;
		else if(	securityenable==10)
		securityenable=11;
		else if(	securityenable==11)
		securityenable=1;
		else
		securityenable=0;


			PLACE = 5;
			num2ascii(securityenable/10, 3);       //   +++
			PLACE = 15;
			num2ascii(securityenable%10, 3);       //   +++


		if( UPDRAT ) wait(500);
  		else wait(50);
  		if( UPDRAT ) UPDRAT--;
  	}
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 }
}             
//*******************************************************
/*   CHANGE QSWEN VALUE   */ 	         //新增加的组合键2	
UPDRAT=10;		                                                            //  ++
if((FUNCTION == 2) && (MODE_SEL==1))
{
 while( (!(*PFDATDIR & 0x0002)) && (!(*PFDATDIR & 0x0001))) //  ++		
 {
  port00 = 15;
  wait(20);
  ADJUST++;
  if (ADJUST>2) ADJUST=0; 
  //******************************
  PLACE = 25;   		
  HOLD[0]=ADJUST+'0';
  wrtchrs(1);
  FPS_ON=ADJUST;
  if(FPS_ON==2)
   	 *XINT2CR = 0x8005;
  else
  {
   	 *XINT2CR = 0x8000;
   	 //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
   	 //*T4CMPR = 100;
   	 //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  
  }
  //******************************               
  if( UPDRAT ) wait(500);
  else wait(50);
  if( UPDRAT ) UPDRAT--;
 }
}
//*******************************************************		
		
		if(FPS_ON==1)
		*PEDATDIR = *PEDATDIR | 0x0040; 
		else
		*PEDATDIR = *PEDATDIR & 0xFFBF; 		
//	}
}	

/*9.  diodeOff */
void diodeAction()  //TANG
{
	if(RF_OFF)
	*PEDATDIR = *PEDATDIR | 0x0010; 	/* Turn off the RF power and LED will be ON ?. */
	else
	{	
	//before ramp, set current to zero
	DIODECUR=DIODECUR2=0;
	*T3CMPR = 0;
	*CMPR6=0;
	*PEDATDIR = *PEDATDIR & 0xFFEF; 	/* Turn ON the RF power and the LED will be OFF ? */
	
	while(DIODECUR < Diode_SetPt || DIODECUR2 < Diode_SetPt2)			// ramp the diode current
			{
			if (DIODECUR < Diode_SetPt)
			DIODECUR++;  
				if (DIODECUR2 < Diode_SetPt2)
			 DIODECUR2++;    				
			if(DIMAX > 250)	{*T3CMPR = (DIODECUR<<2);*CMPR6 = (DIODECUR2<<2);}
			else {*T3CMPR = (DIODECUR<<2);*CMPR6 = (DIODECUR2<<2);}
		 	wait(100);
			PLACE = 25;
		 	num2ascii(DIODECUR, 0);
//rev6			PLACE =5;
//rev6			num2ascii(DIODECUR2, 0);
		 	}
	}
}	
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void diodeAction_1(unsigned long low,unsigned long high,unsigned long low2,unsigned long high2)
{
	if(RF_OFF)
	*PEDATDIR = *PEDATDIR | 0x0010; 	// Turn off the RF power and LED will be ON ?. 
	else
	{	if(securityenable==10)
		{high2=0;low2=0;}
     	else	if(securityenable==01)
		{high=0;low=0;}
		//before ramp, set current to zero
		DIODECUR=low;
		DIODECUR2=low2;
	//	*T3CMPR = 0; tang
	//*CMPR6=0;
		*PEDATDIR = *PEDATDIR & 0xFFEF; 	//Turn ON the RF power and the LED will be OFF ? 
	
		while((DIODECUR < high)  ||( DIODECUR2 < high2)&& (KEYSW_ON))			// ramp the diode current
		{
			if(DIODECUR<high)  DIODECUR++;  
			if(DIODECUR2<high2)  DIODECUR2++ ; 
		  				
			if(DIMAX > 250)	{*T3CMPR = (DIODECUR<<2);*CMPR6 = (DIODECUR2<<2);}
			else {*T3CMPR = (DIODECUR<<2);*CMPR6 = (DIODECUR2<<2);}
		 	wait(100);
			PLACE = 25;
		 	num2ascii(DIODECUR, 0);
//rev6			PLACE =5;
//rev6			num2ascii(DIODECUR2, 0);
		}
		Diode_SetPt=DIODECUR;
		Diode_SetPt2=DIODECUR2;

	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*10 */
void clearScreen()
{
	PLACE = 0;
	port00 = 01;
	wait(20);
	port00 = 01;
	wait(20);
	port00 = 01;
	wait(20);
}	