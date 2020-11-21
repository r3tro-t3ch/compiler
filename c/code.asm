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
	red1: .BYTE 1
	yellow: .BYTE 1
	red2: .BYTE 1
	time: .BYTE 1
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
	sbi DDRB, 4
	sbi DDRB, 2
	sbi DDRB, 1
	sbi DDRB, 4
	sbi DDRB, 2
	sbi DDRB, 1
	sbi DDRB, 4
	sbi DDRB, 2
	sbi DDRB, 1


main:
	ldi r16, 12
	sts red1, r16
	ldi r16, 10
	sts yellow, r16
	ldi r16, 9
	sts red2, r16
	ldi r16, 1000
	sts time, r16
	sbi PortB, 4
	sbi PortB, 2
	sbi PortB, 1
	ldi delay_count, 60
	rcall delay
	cbi PortB, 4
	cbi PortB, 2
	cbi PortB, 1
	ldi delay_count, 60
	rcall delay
	sbi PortB, 4
	sbi PortB, 2
	sbi PortB, 1
	ldi delay_count, 60
	rcall delay
	cbi PortB, 4
	cbi PortB, 2
	cbi PortB, 1
	ldi delay_count, 60
	rcall delay
	sbi PortB, 4
	sbi PortB, 2
	sbi PortB, 1
	ldi delay_count, 60
	rcall delay
	cbi PortB, 4
	cbi PortB, 2
	cbi PortB, 1
	ldi delay_count, 60
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
