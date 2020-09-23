;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"


start:
	sbi DDRB, 2
	sbi PortB, 2
	sbi DDRB, 3
	sbi PortB, 3
	sbi DDRB, 4
	sbi PortB, 4
	sbi DDRB, 5
	sbi PortB, 5
	rjmp start
