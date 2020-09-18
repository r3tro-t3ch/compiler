.include "./m328Pdef.inc"
sbi DDRB, 3
sbi PortB, 3
start:
	rjmp start
