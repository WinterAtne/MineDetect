#pragma once
//Defines input for a player
#include <stdio.h>

#include "board.c"

int framenum = 0;
short pc_input(Board* board, char* action) {
	char command[5] = "";
	fgets(command, 5, stdin);
	printf("%c%c\n", command[2], command[3]);
	while (getchar() != '\n') { } 
	*action = command[0];
	return XYToAbsolute(board, command[2] - 'A', command[3] - 'A');
}

