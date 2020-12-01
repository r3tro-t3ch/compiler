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
	t1: .BYTE 1
	t2: .BYTE 1
	t: .BYTE 1
.CSEG


.def overflow_counter = r16
.def delay_count = r17

.def temp = r18
.org 0x0000
rjmp reset

.org 0x0020
rjmp overflow_handler


reset:
	ldi temp, 0b00000101
	out TCCR0B, temp				;prescaling to 1024
	ldi temp, 0b00000001
	sts TIMSK0, temp				;enabling timer interrupt
	sei								;enabling global interrupt

setup:
	sbi DDRB, 1
	sbi DDRB, 1
	sbi DDRB, 1


main:
	ldi r16, 8
	sts led1, r16
	ldi r16, 9
	sts led2, r16
	ldi r16, 1000
	sts t1, r16
	ldi r16, 2000
	sts t2, r16
	sbi PortB, 1
	ldi delay_count, 60
	rcall delay
	cbi PortB, 1
	ldi delay_count, 60
	rcall delay
	sbi PortB, 1
	ldi delay_count, 60
	rcall delay
	rcall delay
	cbi PortB, 1
	ldi delay_count, 60
	rcall delay
	rcall delay
	ldi r19, 3000
	sts t, r19
	sbi PortB, 1
	ldi delay_count, 60
	rcall delay
	rcall delay
	rcall delay
	cbi PortB, 1
	ldi delay_count, 60
	rcall delay
	rcall delay
	rcall delay


end:
	rjmp end


delay:
	clr overflow_counter
	sec_count:
		cp overflow_counter, delay_count
	brne sec_count
	ret


overflow_handler:
	inc overflow_counter
	cpi overflow_counter, 61
	brne PC+2
	clr overflow_counter
	reti
