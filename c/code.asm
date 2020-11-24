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
	led1: .BYTE 1
	led2: .BYTE 1
	button: .BYTE 1
.CSEG



setup:


main:
	ldi r16, 1
	sts led1, r16
	ldi r16, 1
	sts led2, r16
	ldi r16, 8
	sts button, r16


end:
	rjmp end
