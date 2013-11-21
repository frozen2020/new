#include "constants.h"
#include "extern.h"
#include "RS232.h"
#include "Proto.h"

void sciPolling()
{	char new_byte;
	//check RXRDY
	*IFR= 0x0010;	
	asm(" clrc INTM");
	if(((*SCIRXST) & 0x40) != 0x40)
	{
		new_byte=0;
		return;
	}
	//check RX ERROR
	//else if(((*SCIRXST) & 0x80) == 0x80)
	//echo("RS232 RX ERROR");
	else
	{ 
	new_byte = (*SCIRXBUF);
	//check for ENTER key: ASCII 0x0D
	if(new_byte==NEW_LINE)
	 	{
	 	 if((buffer_index==4)&&(RS232_RX[0]==QUESTION))
		 {parameter[0]=RS232_RX[1];
	 	  parameter[1]=RS232_RX[2];
	  	  parameter[2]=RS232_RX[3];
	  	  runQuery();
	  	 }
	 	 else if((buffer_index==10)&&(RS232_RX[3]==EQUAL))
	 	 {parameter[0]=RS232_RX[0];
	  	  parameter[1]=RS232_RX[1];
	  	  parameter[2]=RS232_RX[2];
		  setting_value[0]=RS232_RX[4]; 
		  setting_value[1]=RS232_RX[5];
		  setting_value[2]=RS232_RX[6];
		  setting_value[3]=RS232_RX[7];
		  setting_value[4]=RS232_RX[8];
		  setting_value[5]=RS232_RX[9];
		  runCommand();
		  LCDRefresh(&DspTmr);			
	  	}
	  	else
	  	{strncpy(msg_globe,ERROR,6);
	  	echo();		 
	  	}
	}	
	else
	{ 	if(buffer_index==10)	
		echo();		 
	  	else
	  	{RS232_RX[buffer_index]=new_byte;
	  	buffer_index++;
	  	}
	} //end of checking other key
	}
	return;
}

//echo back error message or queries/command
void echo()
{	
   	index=0;
   	 //wait for TX buffer ready
   	//while(((*SCICTL2) & 0x80) != 0x80) ;
    *SCITXBUF = msg_globe[index];
    
    //clearn buffer_index, RS232_RX, parameter,setting_value
	
   
}

void echo2()
{	*IFR= 0x0010;	
	asm(" clrc INTM");
	index++;
	if(index>=VALUE_LENGTH)  
	{ buffer_index=0;
    strcpy(RS232_RX,EMPTY);
    strcpy(parameter,EMPTY);
    strcpy(setting_value,EMPTY);
    return;
    }
    *SCITXBUF = msg_globe[index];	//依次发送定义的字符串中的各个字符
	*IFR=0x0010; 			//清除IFR中相应的中断标志 
	asm(" clrc INTM");
}

void runQuery()
{   
	unsigned long iTemp;	
	//ON and OFF query
    if(strncmp(parameter,OKK,3)==0)
    	{
    	strncpy(msg_globe,OKOKOK,6);
    	echo();
    	}    	
	else if(strncmp(parameter,QSW,3)==0)
		{
		if(QSWON==0)		
		strncpy(msg_globe,TURN_OFF,6);
		else
		strncpy(msg_globe,TURN_ON,6);
		
		echo();
		}
	else if(strncmp(parameter,SHT,3)==0)
		{
		if(SHTON==0)
		strncpy(msg_globe,TURN_OFF,6);
		else
		strncpy(msg_globe,TURN_ON,6);
		
		echo();
		}		
	else if(strncmp(parameter,EXT,3)==0)
		{
		if(QSWEXT==0)
		strncpy(msg_globe,TURN_OFF,6);
		else
		strncpy(msg_globe,TURN_ON,6);
		echo();
		}	
	else if(strncmp(parameter,RST,3)==0)
		{
		if(RESET==0)
		strncpy(msg_globe,TURN_OFF,6);
		else
		strncpy(msg_globe,TURN_ON,6);
		echo();
		}		
	else if(strncmp(parameter,DIO,3)==0)
		{
		if(RF_OFF==1)
		strncpy(msg_globe,TURN_OFF,6);
		else
		strncpy(msg_globe,TURN_ON,6);
				
		echo();
		}
	//Quantitative query		
	else if((strncmp(parameter,PRF, 3)==0))		
		{		
		longToString(PULSERATE, msg_globe);						
		echo();		
		}
	else if((strncmp(parameter,PWM, 3)==0))//++xiao		
		{		
		longToString(PWMTime, msg_globe);						
		echo();		
		}//++xiao		
	else if((strncmp(parameter,TEV, 3)==0))		
		{		
		longToString((unsigned long)ENVACT, msg_globe);				
		echo();		
		}				
	else if((strncmp(parameter,TLA, 3)==0))		
		{		
		longToString((unsigned long)LASACT, msg_globe);				
		echo();		
		}						
	else if((strncmp(parameter,TK1, 3)==0))		
		{		
		longToString((unsigned long)XTL1ACT, msg_globe);				
		echo();		
		}						
	else if((strncmp(parameter,TK2, 3)==0))		
		{		
		longToString((unsigned long)XTL2ACT, msg_globe);				
		echo();		
		}						
	else if((strncmp(parameter,TDI, 3)==0))		
		{		
		longToString((unsigned long)D1_ACT, msg_globe);				
		echo();		
		}						
	else if((strncmp(parameter,IDI, 3)==0))		
		{		
		longToString((unsigned long)DIODECUR_ACT, msg_globe);				
		echo();		
		}						
	/*else if((strncmp(parameter,PKP, 3)==0))		
		{		
		longToString((unsigned long)Kp, msg_globe);				
		echo();		
		}						
	else if((strncmp(parameter,PKI, 3)==0))		
		{		
		longToString((unsigned long)Ki, msg_globe);				
		echo();		
		}						
	else if((strncmp(parameter,PKD, 3)==0))		
		{		
		longToString((unsigned long)Kd, msg_globe);				
		echo();		
		}*/							
	else if(strncmp(parameter,FPS,3)==0)
		{
		longToString((unsigned long)FPS_ON, msg_globe);								
		echo();
		}						
			
	else if((strncmp(parameter,FPL, 3)==0))		
		{		
		longToString((unsigned long)FPS_LEVEL, msg_globe);				
		echo();		
		}		
	else if((strncmp(parameter,DCL, 3)==0))		
		{		
		longToString((unsigned long)DIMAX, msg_globe);				
		echo();						
		}
	else
	{strncpy(msg_globe,ERROR,6);
	echo();		 
	}
	return;
}

void runCommand()
{	unsigned long temp;
	//ON and OFF command
	if((strncmp(parameter,QSW, 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				QSWON=0;
				strncpy(msg_globe,TURN_OFF,6);
				echo();
				}
				
			else
				{
				QSWON=1;		
				strncpy(msg_globe,TURN_ON,6);
				echo();
				}			
			qswonAction();
		}
	else if((strncmp(parameter,SHT, 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				SHTON=0;
				strncpy(msg_globe,TURN_OFF,6);
				echo();
				}
			else
				{
				SHTON=1;		
				strncpy(msg_globe,TURN_ON,6);
				echo();
				}
			shtonAction();		
		}	
	else if((strncmp(parameter,EXT, 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				QSWEXT=0;
				strncpy(msg_globe,TURN_OFF,6);
				echo();
				}
			else
				{
				QSWEXT=1;		
				strncpy(msg_globe,TURN_ON,6);
				echo();
				}				
			qswextAction();		
		}
	else if((strncmp(parameter,RST, 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				RESET=0;
				strncpy(msg_globe,TURN_OFF,6);
				echo();
				}
			else
				{
				RESET=1;		
				strncpy(msg_globe,TURN_ON,6);
				echo();
				TPFLAG = 0;
				}							
		}
	else if((strncmp(parameter,DIO, 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				RF_OFF=1;
				strncpy(msg_globe,TURN_OFF,6);
				echo();
				}
				
			else
				{
				RF_OFF=0;
				strncpy(msg_globe,TURN_ON,6);
				echo();
				}			
			diodeAction();
		}	
	else if((strncmp(parameter,FPS, 3)==0))
		{
			   if(strncmp(setting_value,TURN_OFF,6)==0)  //normal: no FPS
				{
				FPS_ON=0;
				*PEDATDIR = *PEDATDIR & 0xFFBF; 		
				FPS_LEVEL=100;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
				//*T4CMPR = FPS_LEVEL;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				}
				else if(strncmp(setting_value,TURN_ON,6)==0) //method 1: FPS=on, FPL=100%
				{
				FPS_ON=1;
				*PEDATDIR = *PEDATDIR | 0x0040; 	
				FPS_LEVEL=100;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@				
				//*T4CMPR = FPS_LEVEL;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				else      //method 2: FPS=off, FPL=input
				{
				FPS_ON=2;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//*T4CMPR = FPS_LEVEL;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				*PEDATDIR = *PEDATDIR & 0xFFBF; 												
				}				
				if(FPS_ON==2)
   	 			*XINT2CR = 0x8005;
   	 			else
   	 			*XINT2CR = 0x8000;   	 	
				strncpy(msg_globe,(char *)FPS_ON,6);
				echo();				
		}									
	//SETTING VALUE COMMAND		
	else if((strncmp(parameter,PRF, 3)==0))		
		{
		PULSERATE=stringToLong((char *)setting_value);		
		if( PULSERATE < 20000 )  PULSERATE = 20000;//频率下限 20K
		if( PULSERATE > 149999 )  PULSERATE = 150000;//频率上限150K	
		pulseRateAction();		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}
	else if((strncmp(parameter,PWM, 3)==0))//++xiao PWM		
		{
		PWMTime=stringToLong((char *)setting_value);
		if( (PWMTime < 20) || (PWMTime > 380) )
		PWMTime=20;		
		pulseRateAction();
		WriteData();
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}//++xiao		
	else if((strncmp(parameter,TEV, 3)==0))		
		{
		ENVSET=(short)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}		
	else if((strncmp(parameter,TLA, 3)==0))		
		{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//LASSET=(short)stringToLong((char *)setting_value);
		LASSET=(float)stringToLong((char *)setting_value);
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}		
	else if((strncmp(parameter,TK1, 3)==0))		
		{
		XTL1SET=(short)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}		
	else if((strncmp(parameter,TK2, 3)==0))		
		{
		XTL2SET=stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}		
	else if((strncmp(parameter,TDI, 3)==0))		
		{
		D1_SET=(float)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}		
	else if((strncmp(parameter,IDI, 3)==0))		
		{
		DIODECUR=stringToLong((char *)setting_value);
		if( DIODECUR > DIMAX ) DIODECUR = DIMAX;	//ver3c
		Diode_SetPt= DIODECUR;			
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		/*
		while(DIODECUR < Diode_SetPt)			// ramp the diode current
			{
			DIODECUR++;      				
			if(DIMAX > 250)	*T3CMPR = (DIODECUR<<2);
			else *T3CMPR = (DIODECUR<<3);
		 	wait(100);
			PLACE = 25;
		 	num2ascii(DIODECUR, 0);
		 	}						
		 	*/
		}		
	/*else if((strncmp(parameter,PKP, 3)==0))		
		{
		Kp=(float)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}		
	else if((strncmp(parameter,PKI, 3)==0))		
		{
		Ki=(float)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}					
	else if((strncmp(parameter,PKD, 3)==0))		
		{
		Kd=(float)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}*/		
	else if((strncmp(parameter,FPL, 3)==0))		
		{
		if(FPS_ON==2)
		{
			FPS_LEVEL=stringToLong((char *)setting_value);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			//*T4CMPR = FPS_LEVEL;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		else 
		{
			FPS_LEVEL=100;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
			//*T4CMPR = FPS_LEVEL;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}			
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}	
	else if((strncmp(parameter,DCL, 3)==0))		
		{
		DIMAX=(short)stringToLong((char *)setting_value);		
		strncpy(msg_globe,(char *)setting_value,6);
		echo();
		}											
	else
	{strncpy(msg_globe,ERROR,6);
	 echo();		 
	 }
	return;
}

//Setup initial conditions for SCI control registers
void sciInit()
{
  	//SCICCR: 1 stop bit, even parity,enable parity bit, 8 data bits, 
  	//idle-line mode
  	*SCICCR = 0x67;//67(with parity bit) 07(without parity bit)
  	//SCICTL1: no erro int.,do sw reset,no TX wakeup,no SCI sleep,enable 
  	//TX,enable RX
  	*SCICTL1 = 0x03; //03
  	//SCIHBAUD,SCILBAUD: baud rate setup: default is 9600 (0x2580)
  	*SCIHBAUD =0x02;
  	*SCILBAUD =0x08;
  	//SCICTL2: TX flag, diable TX/RX interrupt
  	*SCICTL2 = 0xC3;
  	//SCIRXST: RX status. read only.
  	//SCIRXEMU: RX emulation. read only
  	//SCIRXBUF: RX buffer. read only.
  	//SCITXBUF: TX buffer.
  	//SCIPRI: Priority control. not used since interrupt is not used.
  	//echo("Welcome YUCO Optics");
	*SCIPRI=0x60;   
  	 buffer_index=0;  
  	 *SCICTL1 = 0x23; //03	 
    //strcpy(RS232_RX,"");
    //strcpy(parameter,"");
    //strcpy(setting_value,"");
  	return;
}


void longToString(unsigned long iTemp, char *p)
	{		
	*p = (unsigned char )(iTemp>>20) + ZERO;
	*(p+1) = (unsigned char )((iTemp & 0x0F0000)>>16) + ZERO;
	*(p+2) = (unsigned char )((iTemp& 0x00F000)>>12) + ZERO;
	*(p+3) = (unsigned char )((iTemp&0x000F00)>>8) + ZERO;
	*(p+4) = (unsigned char )((iTemp&0x0000F0)>>4) + ZERO;
	*(p+5) = (unsigned char )((iTemp&0x00000F)) + ZERO;
	return;
	}
	
unsigned long stringToLong(char *p)
	{	unsigned long temp, value;
		temp = (p[0]-ZERO);
		temp = temp<<20;
		value= temp;
		temp = (p[1]-ZERO);
		temp = temp<<16;
		value= temp+value;
		temp = (p[2]-ZERO);
		temp = temp<<12;
		value= temp+value;
		temp = (p[3]-ZERO);
		temp = temp<<8;
		value= temp+value;
		temp = (p[4]-ZERO);
		temp = temp<<4;
		value= temp+value;
		temp = (p[5]-ZERO);
		value= temp+value;
		return value;
	}
