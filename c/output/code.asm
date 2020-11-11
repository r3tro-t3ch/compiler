;**************************************************
;*                                                *
;*     THIS IS CODE GENERATED AUTOMATICALLY       *
;*                 BY COMPILER                    *
;*                                                *
;**************************************************


.include "./m328Pdef.inc"


.DSEG
	n: .BYTE 1
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
	cbi DDRB, 3
	sbi DDRB, 2


main:
	nop
	in r16, 8
	andi r16, 8
	sts n, r16
	sbi PortB, 2
	ldi delay_count, 60
	rcall delay
	cbi PortB, 2


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
