;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"


;************************************
;*             variables            *
;************************************

.DSEG
	b: .BYTE 1
	c: .BYTE 1
	a: .BYTE 1
	variable: .BYTE 1
.CSEG



setup:
	cbi DDRB, 3


main:
	nop
	in r16, 8
	andi r16, 8
	sts b, r16
	ldi r16, 10
	sts c, r16
	ldi r16, ($b+$c*4)
	sts a, r16
	ldi r17, ($a+$b*10)
	sts c, r17
	ldi r17, ($a*$b+$c)
	sts variable, r17
	ldi r18, ($variable+$f)
	sts c, r18


end:
	rjmp end
