/*********************************************************************
* Filename: led_c1.cmd                                               *
*                                                                    *
* Author: David M. Alter, Texas Instruments Inc.                     *
*                                                                    *
* Last Modified: 12/20/00                                            *
*                                                                    *
* Description: C code linker command file for F2407 EVM Board        *
*********************************************************************/
-STACK 40
MEMORY
{
  PAGE 0:    /* Program Memory */
    VECS:           org=0h,      len=40h        /* internal FLASH */
    FLASH:          org=44h,     len=7FBCh     /* internal FLASH */

  PAGE 1:    /* Data Memory */
    B2:             org=60h,     len=20h        /* internal DARAM */       
    B0:             org=200h,    len=100h       /* internal DARAM */
    B1:             org=300h,    len=100h       /* internal DARAM */
    SARAM:          org=0800h,   len=800h       /* internal SARAM */
   /* EXTDATA:        org=8000h,   len=8000h */    /* external SRAM  */
}

SECTIONS
{
        .text  >       FLASH      PAGE 0
       .cinit  >       FLASH      PAGE 0
      .switch  >       FLASH      PAGE 0
       .const  >       B1         PAGE 1
       //.const  >       FLASH      PAGE 0
       my_sect >       B0         PAGE 1
   /*      .bss  >       SARAM      PAGE 1 */
	   /*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
	   .bss  >       SARAM      PAGE 1
	   /*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
       .stack  >       SARAM      PAGE 1
      .sysmem  >       B1         PAGE 1

      vectors  >       VECS       PAGE 0
        .data  >       B1         PAGE 1
        table  >       FLASH      PAGE 0
}
