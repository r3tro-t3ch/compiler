;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"



setup:
	cbi DDRB, 5
	cbi DDRB, 4
	cbi DDRB, 2


main:
	nop
	in r16, 32
	andi r16, 32
	nop
	in r17, 16
	andi r17, 16
	nop
	in r18, 4
	andi r18, 4


end:
	rjmp end
