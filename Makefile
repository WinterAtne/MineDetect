NAME = MineSweep
VERSION = 1.0.0

SRC = main.c
OPTS = -o ${NAME}.out

AI_OPTS = -D AI=true
PC_OPTS = 

ai:
	clang ${SRC} ${AI_OPTS} ${OPTS}

pc:
	clang ${SRC} ${PC_OPTS} ${OPTS}


