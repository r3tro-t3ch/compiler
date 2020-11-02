;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"


.DSEG
	a: .BYTE 1
	b: .BYTE 1
.CSEG

setup:
	cbi DDRB, 4
	cbi DDRB, 2


main:
	nop
	in r16, 16
	andi r16, 16
	sts a, r16
	nop
	in r16, 4
	andi r16, 4
	sts b, r16


end:
	rjmp end
