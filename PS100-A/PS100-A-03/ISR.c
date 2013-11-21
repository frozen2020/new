#include "constants.h"
#include "extern.h"
#include "Proto.h"

/********************** INTERRUPT SERVICE ROUTINES *********************/
/*1. TIMER 1 INTERRUPT ROUTINE   */
interrupt void timer1_isr(void)
{
	*EVAIFRA = 0x0080;      /* clear TIMER1 PERIOD INTERRUPT flagS */
	if( INTEST ) INTEST--;
	if( ADTIMER ) ADTIMER--;
	if(LOOP) LOOP--;
	if(MOTORSTART) 
	{	if(STEPCOUNT <0)
		{		
			*PBDATDIR &= 0xFFBF;
			MOTORCOUNT++;
		if (MOTORCOUNT < 4)
			{*PEDATDIR &=0xFFFD;}
			
			if (MOTORCOUNT > 4)
			{*PEDATDIR |=0x0002;}
			
			if (MOTORCOUNT >20)
			{MOTORCOUNT=0;
			STEPCOUNT ++;}
		}
		else if(STEPCOUNT>0)
		{
			*PBDATDIR |= 0x0040;
			MOTORCOUNT++;
			if (MOTORCOUNT < 4)
			{*PEDATDIR &=0xFFFD;}
			
			if (MOTORCOUNT > 4)
			{*PEDATDIR |=0x0002;}
			
			if (MOTORCOUNT >20)
			{MOTORCOUNT=0;
			STEPCOUNT--;}
		}
		else 
		{	 *PEDATDIR |= 0x000A;
			 *PBDATDIR |= 0x0020;
			 MOTORSTART=0;
			 POS_OLD=POS_NEW;
			POS_NEW=0;
		}

	}
	if(BEEPER)
		{
		if(BTIME > 2) BTIME = 0;
		else BTIME++;
		if(!BTIME) *PFDATDIR = (*PFDATDIR ^ BEEPER_BIT);
	 	}
} 	

/*2. TRIGGER INTERRUPT ROUTINE   */   
interrupt void xint1(void)  //extern trigger: FREQ++, clear interrup
{  
    if((*XINT2CR) & 0x0004)
		{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//*T4CMPR = FPS_LEVEL;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		*XINT2CR = 0x8001;
		}
	else
		{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//*T4CMPR = 100;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		*XINT2CR = 0x8005;
		}	
}   
	
    //if((*PIRQR0)&0x0004)   //xint1
	//{
//		if( QSWEXT )
//		{
//		*XINT1CR = *XINT1CR | 0x8001;
 //		FREQ++;
   //		}   		
   	//	*PIACKR0=(*PIACKR0)|0x0004;
   	//}
//}
/*   	
   	else if( (*PIRQR0)&0x0008)   //xint2
   	{
   	if(*XINT2CR & 0x0004)
		{
		*T4CMPR = FPS_LEVEL<<2;
		*XINT2CR = 0x8001;
		}
	else
		{
		*T4CMPR = 400;
		*XINT2CR = 0x8005;
		}
	*PIACKR0=(*PIACKR0)|0x0008;		
	}   	
}		 /* End xint1() */


/*3. GATE INTERRUPT ROUTINE   */  
//interrupt void xint2(void)   //1. clear int. 2.set T4 compare register at array index.
//{    
//	if(*XINT2CR & 0x0004)
//		{
//		*T4CMPR = FPS_LEVEL<<2;
//		*XINT2CR = 0x8001;
//		}
//	else
//		{
//		*T4CMPR = 400;
//		*XINT2CR = 0x8005;
//		}
//} 	
/*4 RS232 INTERRUPT*/
interrupt	void    uarttr(void)    		//中断服务程序
{	switch (*PIVR)			//根据中断向量寄存器PVIR的值区别是接收还是发送中断
	{
	        case 6:    sciPolling();break;	//如果PIVR=6，则发生了接收中断，执行接收服务程序
			    	case 7:	   echo2(); break;//清除IFR中相应的中断标志 
						}
}