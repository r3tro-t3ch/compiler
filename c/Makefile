
HEADER_CODE:= HEADER/*.c  HEADER/*.h
MAIN:= main.c
TARGET:= compiler
CFLAGS:= -Wall -g #-s #-Werror 
DFLAGS:= --leak-check=full -s -v
BAUDRATE:=115200
PORT:=/dev/ttyACM0
ASSEMBLY_CODE:=code.asm
HEX_CODE:=code.hex

build:
	gcc ${HEADER_CODE} ${MAIN} ${CFLAGS}-o ${TARGET}
	
clean:
	rm ${TARGET}

debug:
	valgrind ${DFLAGS} ./${TARGET}


upload:
	avra $(ASSEMBLY_CODE)
	avrdude -p m328p -c stk500v1 -b $(BAUDRATE) -P $(PORT) -U flash:w:$(HEX_CODE) -F


