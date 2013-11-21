*********************************************************************
* Filename: cvectors.asm                                             *
*                                                                    *
* Author: David M. Alter, Texas Instruments Inc.                     *
*                                                                    *
* Last Modified: 03/14/01                                            *
*                                                                    *
* Description: Interrupt vector table for '240x DSP core             *
* for use with C language programs.                                  *
*                                                                    *
**********************************************************************

**********************************************************************
* THIS PROGRAM IS PROVIDED "AS IS". TI MAKES NO WARRANTIES OR        *
* REPRESENTATIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,             *
* INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS       *
* FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR             *
* COMPLETENESS OF RESPONSES, RESULTS AND LACK OF NEGLIGENCE.         *
* TI DISCLAIMS ANY WARRANTY OF TITLE, QUIET ENJOYMENT, QUIET         *
* POSSESSION, AND NON-INFRINGEMENT OF ANY THIRD PARTY                *
* INTELLECTUAL PROPERTY RIGHTS WITH REGARD TO THE PROGRAM OR         *
* YOUR USE OF THE PROGRAM.                                           *
*                                                                    *
* IN NO EVENT SHALL TI BE LIABLE FOR ANY SPECIAL, INCIDENTAL,        *
* CONSEQUENTIAL OR INDIRECT DAMAGES, HOWEVER CAUSED, ON ANY          *
* THEORY OF LIABILITY AND WHETHER OR NOT TI HAS BEEN ADVISED         *
* OF THE POSSIBILITY OF SUCH DAMAGES, ARISING IN ANY WAY OUT         *
* OF THIS AGREEMENT, THE PROGRAM, OR YOUR USE OF THE PROGRAM.        *
* EXCLUDED DAMAGES INCLUDE, BUT ARE NOT LIMITED TO, COST OF          *
* REMOVAL OR REINSTALLATION, COMPUTER TIME, LABOR COSTS, LOSS        *
* OF GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF          *
* USE OR INTERRUPTION OF BUSINESS. IN NO EVENT WILL TI'S             *
* AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF         *
* YOUR USE OF THE PROGRAM EXCEED FIVE HUNDRED DOLLARS                *
* (U.S.$500).                                                        *
*                                                                    *
* Unless otherwise stated, the Program written and copyrighted       *
* by Texas Instruments is distributed as "freeware".  You may,       *
* only under TI's copyright in the Program, use and modify the       *
* Program without any charge or restriction.  You may                *
* distribute to third parties, provided that you transfer a          *
* copy of this license to the third party and the third party        *
* agrees to these terms by its first use of the Program. You         *
* must reproduce the copyright notice and any other legend of        *
* ownership on each copy or partial copy, of the Program.            *
*                                                                    *
* You acknowledge and agree that the Program contains                *
* copyrighted material, trade secrets and other TI proprietary       *
* information and is protected by copyright laws,                    *
* international copyright treaties, and trade secret laws, as        *
* well as other intellectual property laws.  To protect TI's         *
* rights in the Program, you agree not to decompile, reverse         *
* engineer, disassemble or otherwise translate any object code       *
* versions of the Program to a human-readable form.  You agree       *
* that in no event will you alter, remove or destroy any             *
* copyright notice included in the Program.  TI reserves all         *
* rights not specifically granted under this license. Except         *
* as specifically provided herein, nothing in this agreement         *
* shall be construed as conferring by implication, estoppel,         *
* or otherwise, upon you, any license or other right under any       *
* TI patents, copyrights or trade secrets.                           *
*                                                                    *
* You may not use the Program in non-TI devices.                     *
**********************************************************************


        .ref _c_int0, _xint1, _timer1_isr, _uarttr;
        ;, _t2cmp_isr

        .sect    "vectors"
rset:   B       _c_int0         ;00h reset
int1:   B       _xint1          ;02h INT1
int2:   B       _timer1_isr     ;04h INT2
int3:   B       int3    		;06h INT3
int4:   B       int4            ;08h INT4
int5:   B 		_uarttr         ;0Ah INT5
int6:   B       int6            ;0Ch INT6
int7:   B       int7            ;0Eh reserved
int8:   B       int8            ;10h INT8  (software)
int9:   B       int9            ;12h INT9  (software)
int10:  B       int10           ;14h INT10 (software)
int11:  B       int11           ;16h INT11 (software)
int12:  B       int12           ;18h INT12 (software)
int13:  B       int13           ;1Ah INT13 (software)
int14:  B       int14           ;1Ch INT14 (software)
int15:  B       int15           ;1Eh INT15 (software)
int16:  B       int16           ;20h INT16 (software)
int17:  B       int17           ;22h TRAP
int18:  B       int18           ;24h NMI
int19:  B       int19           ;26h reserved
int20:  B       int20           ;28h INT20 (software)
int21:  B       int21           ;2Ah INT21 (software)
int22:  B       int22           ;2Ch INT22 (software)
int23:  B       int23           ;2Eh INT23 (software)
int24:  B       int24           ;30h INT24 (software)
int25:  B       int25           ;32h INT25 (software)
int26:  B       int26           ;34h INT26 (software)
int27:  B       int27           ;36h INT27 (software)
int28:  B       int28           ;38h INT28 (software)
int29:  B       int29           ;3Ah INT29 (software)
int30:  B       int30           ;3Ch INT30 (software)
int31:  B       int31           ;3Eh INT31 (software)
