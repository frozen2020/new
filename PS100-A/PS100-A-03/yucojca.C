#include "constants.h"
#include "yuco.h"
#include "Proto.h"

/******************************* MAIN ***********************/	
void main(void)
{	
	short wrFlag = 1;
	short errFlag = 1;
	short key = 0;
	/* System restore conditions. */
	short SaveQSExt = 0;
	short SaveQSOn = 0;
	unsigned long abc;
	short FuncFlg = 0;
	char strTime[80];
	char *a, *b, *c, *d;
	unsigned long word;
	short settleDelay;
	Diode_SetPt =Diode_SetPt2= 0;

	LOOP = 10;
	TPFLAG = 0;
	BEEPER = 0;
	DspTmr = 0;		

    /* Initialize registers and variables */
    Initialize();
	/*** SETUP LCD DISPLAY ***/
	LCDSetup();    
 	/* Make sure the shutter is off on start up. */
	shutterOff(); 
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
	while(1)
	{
	/* Check to see if the key switch is on. */	
	if(!KEYSW_ON) wait(20);
	if( !KEYSW_ON && !OLD_KEYSW_ON && !WriteFlag)				
	keyswOffAction (&SaveQSExt,&SaveQSOn,&key);
	if( KEYSW_ON) wait(20);
	if( KEYSW_ON && !OLD_KEYSW_ON )
	{
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		keyswFirstOnAction(&settleDelay,&SaveQSExt,&SaveQSOn);
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if(InitingError==0)
	{
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	while( KEYSW_ON )
	{	
	*PCDATDIR = 0xF00F;				/* ANY KEY PRESSED ?*/					
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%				
	//*PCDATDIR = 0xF000;
	if(SecurityIniting==1)
	{
		

		*PCDATDIR = 0xF0F0;   //tang suojianpan
	}
	else
	{	
		*PCDATDIR = 0xF000;
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	while(((*PCDATDIR & 0x0003)==3)&&((*PFDATDIR & 0x0003)==3)&& KEYSW_ON)
	{//no key pressed 
	if( !ADTIMER )
	{
	tempctl(); //0.1sec
	DspTmr++;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if(SecurityIniting==1)
	{
		TimeC_Sec++;
		if(TimeC_Sec==10)
		{
			TimeC_Sec=0;
			TimeC_Min++;
		}
		if(TimeC_Min==60)
		{
			TimeC_Min=0;
			TimeC_2Min++; 
			TimeC_8Min++;
		}
		if(TimeC_2Min==1)
		{
			TimeC_2Min=0; 
			Sign_2Min=1;
		}
		if(TimeC_8Min==5)
		{
			TimeC_8Min=0; 
			Sign_8Min=1;
		}
	}
	
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%
	}	
	
	if(REMLOC) 
    {    
    FUNCTION=15;
    *IMR=*IMR|0x10;
    }
    else 
    {if(FUNCTION==15)
    	{FUNCTION=0;
		}
	*IMR=*IMR&0xEF;
    }
    
	if(LOOP) continue;	
	/* Do this every 0.5sec */									
	if(!LOOP)
	LOOP = 10000;
	LCDRefresh(&DspTmr);			
//==============================================================================
			/* Test temperature and make sure it is within acceptable range.
			 * The temperature should be greater than or equal to 15 degrees C
			 * less than or equal to 35 degrees C. */
//==============================================================================
	if( KEYSW_ON && OLD_KEYSW_ON)  //default ACTION every 0.5sec (LOOP)
	defaultAction(&errFlag,&wrFlag);


	//%%%%%%%%%%%%%%%%%%%%%
	if(InitingError==0)
	{
	if(SecurityIniting==1)
	{
		switch(FirstStemp) 
		{
			case 1:	QSWON = 1;
					QSWEXT = 1;
				    qswonAction();
					RF_OFF=0;
   		    		// diodeAction_1(0,0.8*INITCUR);
   		    	//test	QSWEXT = 1;
					qswextAction();
					diodeAction_1(0,0.6*INITCUR,0,0.6*INITCUR2);
   		    		TimeC_2Min=0;
   		    		Sign_2Min=0;
   		    		FirstStemp=2;
   		    		break;	
			case 2: if(Sign_2Min==1)
					{
						FirstStemp=3;	
					}
					break;
			case 3:	diodeAction_1(0.6*INITCUR,INITCUR,0.6*INITCUR2,INITCUR2);
					TimeC_8Min=0;
   		    		Sign_8Min=0;
   		    		//FirstStemp=4;
					FirstStemp=5;	 //tang
   		    		break;
			case 4:	if(Sign_8Min==1)
					{
						FirstStemp=5;	
					}
					break;
			case 5:	SecurityIniting=0;
					BEEPER = 1;
					wait(50);
					BEEPER = 0;
					*PCDATDIR = 0xF00F;		
					*PCDATDIR = 0xF000;
					FirstStemp=0;
					break;
			default:break;
		}
		}
	}
	
	//%%%%%%%%%%%%%%%%%%%%%
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if(InitingError==0)
	{
	if(SecurityIniting==0)
	{
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//key is pressed, start scanning
	BEEPER = 1;
	wait(50);
	BEEPER = 0;
	/* Check Remote/Local key */
	/* SET ROW 40 STROBE */
	*PCDATDIR = ~0x0F40;	
	wait(1);		
    /*   TOGGLE REMOTE/LOCAL MODE   */
	//if( (!(*PCDATDIR & 0x0002)) && (!FUNCTION) )
	if((!FUNCTION)||(REMLOC==1))
	{
	if (!(*PCDATDIR & 0x0002)) 
	wait(20);
	if( !(*PCDATDIR & 0x0002) )	
	{REMLOC = !REMLOC;
	if(REMLOC)
		{
		HOLD[0] = 'R';
	   	HOLD[1] = 'E';
	   	HOLD[2] = 'M';	   	
	  	}
  	else
  		{
		HOLD[0] = 'L';
	   	HOLD[1] = 'O';
	   	HOLD[2] = 'C';	   	
	  	}
	PLACE=101;
	wrtchrs(3);	  	
 	}  	
 	while( !(*PCDATDIR & 0x0002) );	
 	/* REMOTE */
    if(REMLOC) 
    {
    FUNCTION=15;
    sciPolling();
    }
    else 
    {if(FUNCTION==15)
    FUNCTION=0;}
    }
/*RESET KEY CHECK AND ACTION */			
/*SET ROW  40 STROBE */
	*PCDATDIR = ~0x0F40;	
	while(TPFLAG)
	{
	if( !(*PCDATDIR & 0x0001) )  /*    RESET BUTTON  */
		{
		wait(10);
		if( !(*PCDATDIR & 0x0001) )
			{
			RESET = 1;
			clearWarning=0;
			TPFLAG = 0;
			}
		while( !(*PCDATDIR & 0x0001) )
			if(!KEYSW_ON)  port00 = 0x0008;
		}
	}
  
  /*ENTER KEY CHECK AND ACTION    TANG */	
/*SET ROW  40 STROBE */
	*PCDATDIR = ~0x0F40;	
	if( !(*PFDATDIR & 0x0002) && (!FUNCTION) && (!(FUNCTION == 3)) )  /*    ENTER BUTTON  */
	{
		wait(10);
		if( !(*PFDATDIR & 0x0002) )
			DIODESELECT=!DIODESELECT;
		while( !(*PFDATDIR & 0x0002) );
		
	}

/*Q-SWITCH INTERNAL/ENTERNAL KEY CHECK AND ACTION*/ 
/* SET ROW 10 STROBE */
	*PCDATDIR = ~0x0F10;	
	wait(1);

//DIODE_ON:
	if( (!(*PCDATDIR & 0x0001)) && (!FUNCTION) && (!(FUNCTION == 3)) )
	{
	wait(10);	
	if( !(*PCDATDIR & 0x0001 ))
		{
		RF_OFF = !RF_OFF;
		diodeAction();
		while( !(*PCDATDIR & 0x0001 ));
		}
	}
	
//QSW EXT/INT:	
	if( (!(*PCDATDIR & 0x0002)) && (!FUNCTION) && (!(FUNCTION == 3)) )
	{
	wait(10);
	PLACE = 88;
	if( !(*PCDATDIR & 0x0002) )
		{
		QSWEXT = !QSWEXT;
		qswextAction();
		while( !(*PCDATDIR & 0x0002) );
		}
	}


/* Q-SWITCH ON/OFF KEY CHECK AND ACTION  */
	if(QSWEN==0)
    {
	    if( (!(*PFDATDIR & 0x0001) && (!FUNCTION)) && (!(FUNCTION == 3))&&(EXTDCUR<10)&&(EXTDCUR2<10)  ) ///tang????
		{
		wait(10);
   		   if( !(*PFDATDIR & 0x0001) )
   			 {
   			  QSWON = !QSWON;
   			  qswonAction();
   			  while( !(*PFDATDIR & 0x0001) );
			 }
		}
    }
    else
    {
	    if( (!(*PFDATDIR & 0x0001) && (!FUNCTION)) && (!(FUNCTION == 3)) )
		{
		wait(10);
   		   if( !(*PFDATDIR & 0x0001) )
   			 {
   			  QSWON = !QSWON;
   			  qswonAction();
   			  while( !(*PFDATDIR & 0x0001) );
			 }
		}
    }

/* SHUTTER ON/OFF KEY CHECK AND ACTION  */

	if( (!(*PFDATDIR & 0x0002)) && (!FUNCTION) && (!(FUNCTION == 3)) )
		{
		wait(10);
   		if( !(*PFDATDIR & 0x0002) )
   			{
   			PLACE = 99;
   			SHTON = !SHTON;
   			shtonAction();
   			while( !(*PFDATDIR & 0x0002) );
			}
		}

/* SET ROW 20 STROBE */
	*PCDATDIR = ~0x0F20;	
	wait(1);

/*  PULSE RATE CHECK AND ACTION  */
/* INCREMENT */
  	UPDRAT = 10;
   	while( (!(*PCDATDIR & 0x0001)) && (!FUNCTION) && (!QSWEXT) )
   		{
		if( PULSERATE / 100000 ) PULSERATE = PULSERATE + 1000; //  ++
		else                                                   //  ++
		if( PULSERATE / 1000 )   PULSERATE = PULSERATE + 100;
		else PULSERATE++;
		//if( PULSERATE > 99999 )	PULSERATE = 100000;     //频率上限100K
		//if( PULSERATE > 119999 )	PULSERATE = 120000;     //频率上限120K
		if( PULSERATE > 149999 )  PULSERATE = 150000;//频率上限150K
		PLACE = 71;
		num2ascii(PULSERATE,1);
	    pulseRateAction();
		if( UPDRAT ) wait(250);
		else wait(25);
		if( UPDRAT ) UPDRAT--;
		}	
/* DECREMENT */
   		UPDRAT = 10;
		while( (!(*PCDATDIR & 0x0002)) && (!FUNCTION) && (!QSWEXT) )
		{
		if( PULSERATE == 1000 ) PULSERATE = 999;
		else if( PULSERATE / 100000 ) PULSERATE = PULSERATE - 1000; //  ++
		else                                                        //  ++
		if( PULSERATE / 1000 ) PULSERATE = PULSERATE - 100;
		else PULSERATE--;
		if( PULSERATE < 10 ) PULSERATE = 10;
		PLACE = 71;
		num2ascii(PULSERATE, 1);
		pulseRateAction();
		if( UPDRAT ) wait(500);
		else wait(50);
		if( UPDRAT ) UPDRAT--;
		}


/* INCREASE DIODE CURRENT CHECK AND ACTION */					
/* INCREMENT */
   		UPDRAT = 10;
   		if(QSWEN==0)
   		{
   		   while( (!(*PFDATDIR & 0x0001)) && (!FUNCTION) && (QSWON==1) )
		   {
		     DIODECUR++;		/*   LIMIT ON CURRENT OUTPUT */
		     if( DIODECUR > DIMAX ) DIODECUR = DIMAX;
		     if(DIMAX > 250)	*T3CMPR = (DIODECUR<<2);
		     else *T3CMPR = (DIODECUR<<2);
	         PLACE = 25;
		     num2ascii(DIODECUR,0);
		     if( UPDRAT ) wait(500);
		     else wait(50);
		     if( UPDRAT ) UPDRAT--;
		     Diode_SetPt= DIODECUR;

		   }
		}
        else
   		{
   		   while( (!(*PFDATDIR & 0x0001)) && (!FUNCTION) )
		   {
			 
		     DIODECUR++;		/*   LIMIT ON CURRENT OUTPUT */
		     if( DIODECUR > DIMAX ) DIODECUR = DIMAX;
		     if(DIMAX > 250)	*T3CMPR = (DIODECUR<<2);
		     else *T3CMPR = (DIODECUR<<2);
	         PLACE = 25;
		     num2ascii(DIODECUR,0);
		     if( UPDRAT ) wait(500);
		     else wait(50);
		     if( UPDRAT ) UPDRAT--;
		     Diode_SetPt= DIODECUR;}
		    
		}
/*DECREMENT */
   	 		UPDRAT = 10;
   		if(QSWEN==0)
   		{
   		   while( (!(*PFDATDIR & 0x0002)) && (!FUNCTION) && (QSWON==1) )
		   {
		     if(DIODECUR>0) DIODECUR--;		/*   LIMIT ON CURRENT OUTPUT */
		     if( DIODECUR > DIMAX ) DIODECUR = DIMAX;
		     if(DIMAX > 250)	*T3CMPR = (DIODECUR<<2);
		     else *T3CMPR = (DIODECUR<<2);
	         PLACE = 25;
		     num2ascii(DIODECUR,0);
		     if( UPDRAT ) wait(500);
		     else wait(50);
		     if( UPDRAT ) UPDRAT--;
		     Diode_SetPt= DIODECUR;
		  }
		}
        else
   		{
   		   while( (!(*PFDATDIR & 0x0002)) && (!FUNCTION) )
		   {
			 
		    if(DIODECUR>0)  DIODECUR--;		/*   LIMIT ON CURRENT OUTPUT */
		     if( DIODECUR > DIMAX ) DIODECUR = DIMAX;
		     if(DIMAX > 250)	*T3CMPR = (DIODECUR<<2);
		     else *T3CMPR = (DIODECUR<<2);
	         PLACE = 25;
		     num2ascii(DIODECUR,0);
		     if( UPDRAT ) wait(500);
		     else wait(50);
		     if( UPDRAT ) UPDRAT--;
		     Diode_SetPt= DIODECUR;

		   }
		}

/* SET ROW 80 STROBE */
	*PCDATDIR = ~0x0F80;	
	wait(1);
/*  PWM CHECK AND ACTION  */     //+++++++++PWM
/* INCREMENT */
  	UPDRAT = 10;
   	while( (!(*PFDATDIR & 0x0001)) && (!FUNCTION) && (!QSWEXT) )
   		{
		if(PWMTime<=20) PWMTime = 20;
		else
		PWMTime = PWMTime - 8;
		PLACE = 79;
		num2ascii(PWMTime,9);  //
	    pulseRateAction();
		if( UPDRAT ) wait(250);
		else wait(25);
		if( UPDRAT ) UPDRAT--;
		}	
/* DECREMENT */
   		UPDRAT = 10;
		while( (!(*PFDATDIR & 0x0002)) && (!FUNCTION) && (!QSWEXT) )
		{
		if(PWMTime>= 740) PWMTime = 740;
		else
		PWMTime = PWMTime + 8;
		PLACE = 79;
		num2ascii(PWMTime, 9);
		pulseRateAction();
		if( UPDRAT ) wait(500);
		else wait(50);
		if( UPDRAT ) UPDRAT--;
		}

/* SET ROW 40 STROBE */
		*PCDATDIR = ~0x0F40;	
		wait(1);
/*  EXIT SETUP KEY CHECK AND ACTION   */
		if( !(*PFDATDIR & 0x0001) )
		{
		wait(10);
		if( !(*PFDATDIR & 0x0001) )
			{
			FuncFlg = 0;
			port00 = 12;
			FUNCTION = 0;
			REMLOC=0;
			wait(2);
			PLACE = 0;
			message(msg1);
			PLACE = 64;
			message(msg2);
			if( PULSERATE < 10 ) PULSERATE = 10;
			PLACE = 71;
			num2ascii(PULSERATE,1);
			if( QSWEXT )
			{
			HOLD[0] = 'E';
			HOLD[1] = 'X';
			}
			else
			{
			HOLD[0] = 'I';
			HOLD[1] = 'N';
			}
			PLACE = 88;
			wrtchrs(2);
			if( SHTON )
			{
			HOLD[0] = 'N';
			HOLD[1] = ' ';
			}
			else
			{
			HOLD[0] = 'F';
			HOLD[1] = 'F';
			}
			PLACE = 97;	
  			wrtchrs(2);
			wait(10);
   			PLACE = 25;
   			num2ascii(DIODECUR, 0);
 
 			while( !(*PFDATDIR & 0x0001) );
			}
		}
	if(!REMLOC)	
	functionAction(&FuncFlg);		
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%
	}
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%
	}	/* END while( KEYSW_ON ) */
	}
	OLD_KEYSW_ON = 0;
	FuncFlg = 0;		
	} /* End while(1) */
}