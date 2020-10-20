;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"



setup:
	sbi DDRB, 5


main:
	sbi PortB, 5


end:
	rjmp end
