;*
;*  Copyright (c) 2001-2002, Texas Instruments Incorporated.
;*  All rights reserved. Property of Texas Instruments Incorporated.
;*  Restricted rights to use, duplicate or disclose this code are
;*  granted through contract.
;*

	.sect	".text"
	.global	_load

;***************************************************************
;* FNAME: _load                         FR SIZE:   1           *
;*                                                             *
;* This function simulates a load on the DSP with a loop that  *
;* iterates N times, where N is the processingLoad parameter   *
;* that is passed to this function.                            *
;***************************************************************
_load:

LF1     .set    1

        SAR     AR0,*+
        SAR     AR1,*
        LAR     AR0,*+,AR2

        LARK    AR2,-3+LF1
        MAR     *0+
        LAC     *
        BZ      L2
L1:
        LAC     *
        SUBK    1
        SACL    *
        LAC     *
        BNZ     L1
L2:
EPI0_1:
        MAR     * ,AR1
        SBRK    2
        LAR     AR0,*
        RET
