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
	a: .BYTE 1
.CSEG



setup:


main:
	ldi r16, 1
	sts a, r16


end:
	rjmp end
