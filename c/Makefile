
HEADER_CODE:= HEADER/*.c  HEADER/*.h
MAIN:= main.c
TARGET:= compiler
CFLAGS:= -Wall -g -s #-Werror 
DFLAGS:= --leak-check=full -s

build:
	gcc ${HEADER_CODE} ${MAIN} ${CFLAGS}-o ${TARGET}
	
clean:
	rm ${TARGET}

debug:
	valgrind ${DFLAGS} ./${TARGET}
