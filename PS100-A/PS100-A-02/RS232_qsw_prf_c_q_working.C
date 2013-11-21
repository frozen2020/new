#include "constants.h"
#include "extern.h"
#include "RS232.h"
#include "Proto.h"


//echo back error message or queries/command
void echo(char * msg)
{
	int index;
   	for (index=0; index<strlen(msg);index++)
   	{ //wait for TX buffer ready
   	while(((*SCICTL2) & 0x80) != 0x80) ;
    *SCITXBUF = msg[index];
    *SCICTL1 = 0x23;
    //clearn buffer_index, RS232_RX, parameter,setting_value
	}
    buffer_index=0;
    strcpy(RS232_RX,"");
    strcpy(parameter,"");
    strcpy(setting_value,"");
    return;
}

//Setup initial conditions for SCI control registers
void sciInit()
{
  	//SCICCR: 1 stop bit, even parity,enable parity bit, 8 data bits, 
  	//idle-line mode
  	*SCICCR = 0x67;
  	//SCICTL1: no erro int.,do sw reset,no TX wakeup,no SCI sleep,enable 
  	//TX,enable RX
  	*SCICTL1 = 0x23; //03
  	//SCIHBAUD,SCILBAUD: baud rate setup: default is 9600 (0x2580)
  	*SCIHBAUD =0x02;
  	*SCILBAUD =0x08;
  	//SCICTL2: TX flag, diable TX/RX interrupt
  	*SCICTL2 = 0xC0;
  	//SCIRXST: RX status. read only.
  	//SCIRXEMU: RX emulation. read only
  	//SCIRXBUF: RX buffer. read only.
  	//SCITXBUF: TX buffer.
  	//SCIPRI: Priority control. not used since interrupt is not used.
  	//echo("Welcome YUCO Optics");
  	return;
}


void runQuery()
{
	char p[6]="";
	unsigned long iTemp;
	//ON and OFF query
    if(strncmp(parameter,"OKK",3)==0)
    	echo("OKOKOK");
	else if(strncmp(parameter,"QSW",3)==0)
		{
		if(QSWON==0)		
		echo(TURN_OFF);
		else
		echo(TURN_ON);
		}
	else if(strncmp(parameter,"SHT",3)==0)
		{
		if(SHTON==0)
		echo(TURN_OFF);
		else
		echo(TURN_ON);
		}		
	else if(strncmp(parameter,"EXT",3)==0)
		{
		if(QSWEXT==0)
		echo(TURN_OFF);
		else
		echo(TURN_ON);
		}	
	else if(strncmp(parameter,"RST",3)==0)
		{
		if(RESET==0)
		echo(TURN_OFF);
		else
		echo(TURN_ON);
		}		
	//Quantitative query		
	else if((strncmp(parameter,"PRF", 3)==0))		
		{
		
		iTemp = PULSERATE;
		*p = (unsigned char )(iTemp>>20) + '0';

		iTemp = PULSERATE;
		*(p+1) = (unsigned char )((iTemp & 0x0F0000)>>16) + '0';

		iTemp = PULSERATE;
		*(p+2) = (unsigned char )((iTemp& 0x00F000)>>12) + '0';

		iTemp = PULSERATE;
		*(p+3) = (unsigned char )((iTemp&0x000F00)>>8) + '0';

		iTemp = PULSERATE;
		*(p+4) = (unsigned char )((iTemp&0x0000F0)>>4) + '0';

		iTemp = PULSERATE;
		*(p+5) = (unsigned char )((iTemp&0x00000F)) + '0';
		
		echo(p);
		//pulseRateAction();
		//echo((char *) setting_value);
		}		
	else
	echo("FFFFFF");		
	return;
}

void runCommand()
{	unsigned long temp;
	//ON and OFF command
	if((strncmp(parameter,"QSW", 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				QSWON=0;
				echo(TURN_OFF);
				}
				
			else
				{
				QSWON=1;		
				echo(TURN_ON);
				}			
			qswonAction();
		}
	else if((strncmp(parameter,"SHT", 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				SHTON=0;
				echo(TURN_OFF);
				}
			else
				{
				SHTON=1;		
				echo(TURN_ON);
				}
			shtonAction();		
		}	
	else if((strncmp(parameter,"EXT", 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				QSWEXT=0;
				echo(TURN_OFF);
				}
			else
				{
				QSWEXT=1;		
				echo(TURN_OFF);
				}				
			qswextAction();		
		}
	else if((strncmp(parameter,"RST", 3)==0))
		{
			if(strncmp(setting_value,TURN_OFF,6)==0)
				{
				RESET=0;
				echo(TURN_OFF);
				}
			else
				{
				RESET=1;		
				echo(TURN_ON);
				TPFLAG = 0;
				}							
		}		
	//SETTING VALUE COMMAND		
	else if((strncmp(parameter,"PRF", 3)==0))		
		{
		temp = (setting_value[0]-'0');
		temp = temp<<20;
		PULSERATE=temp;
		temp = (setting_value[1]-'0');
		temp = temp<<16;
		PULSERATE=temp+PULSERATE;
		temp = (setting_value[2]-'0');
		temp = temp<<12;
		PULSERATE=temp+PULSERATE;
		temp = (setting_value[3]-'0');
		temp = temp<<8;
		PULSERATE=temp+PULSERATE;
		temp = (setting_value[4]-'0');
		temp = temp<<4;
		PULSERATE=temp+PULSERATE;
		temp = (setting_value[5]-'0');
		PULSERATE=temp+PULSERATE;		
		
		pulseRateAction();
		echo("FFFFFF");
		}		
	
	
	//other command compare statements
	else
	echo("FFFFFF");	
	return;
}

void sciPolling()
{	char new_byte;
	//check RXRDY
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
	if(new_byte=='\n')
	 	{
	 	 if((buffer_index==4)&&(RS232_RX[0]=='?'))
		 {parameter[0]=RS232_RX[1];
	 	  parameter[1]=RS232_RX[2];
	  	  parameter[2]=RS232_RX[3];
	  	  runQuery();
	  	 }
	 	 else if((buffer_index==10)&&(RS232_RX[3]=='='))
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
	  	echo(ERROR_MSG);		 
	}	
	else
	{ 	if(buffer_index==10)
		echo(ERROR_MSG);		 
	  	else
	  	{RS232_RX[buffer_index]=new_byte;
	  	buffer_index++;
	  	}
	} //end of checking other key
	}
	return;
}

