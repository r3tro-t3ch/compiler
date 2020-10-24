;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"



setup:
	sbi DDRB, 3


main:
	sbi PortB, 3


end:
	rjmp end
