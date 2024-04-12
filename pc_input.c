#pragma once
//Defines input for a player
#include <stdio.h>

#include "board.c"

int framenum = 0;
short pc_input(Board* board, char* action) {
	char command[5] = "";
	fgets(command, sizeof(command), stdin);
	while (getchar() != '\n') { } 
	*action = command[0];

	command[2] -= 'A';
	command[3] -= 'A';
	if (command[2] < 0 || command[3] < 0 || command[2] >= board->sizeX || command[3] >= board->sizeY) {
		printf("invalid input, please enter valid input\n");
		return pc_input(board, action);
	}
	return XYToAbsolute(board, command[2], command[3]);
}

