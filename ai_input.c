#pragma once
// The AI input method
#include "board.c"


short random_when_unknown = 0;

short ai_input(Board* board, char* action) {
	/* Methodology:
	 * Loop through looking for number tiles, once one is found.
	 * Count the number of flagged tiles around it. 
	 * If the number of unflagged tiles = flagged tiles, flag all noinfo tiles,
	*/
	
	for (short tile = 0; tile < board->size; tile++) {
		if (board->field[tile] < '0' || board->field[tile] > '9') continue;
		
		char bombs = 0;
		char noinfo = 0;
		char allbombs = board->field[tile] - '0';
		
		short* neighbors = GetNeighborIndicies(board, tile);
		for (char i = 0; i < 8; i++) {
			if (board->field[neighbors[i]] == NOINFO) noinfo++;
			else if (board->field[neighbors[i]] == FLAG) bombs++;
		}
		
		if (allbombs == bombs) {
			*action = 'c';
			
		} else if (allbombs - bombs == noinfo) {
			*action = 'f';
			
		} else {
			continue;
		}

		for (char i = 0; i < 8; i++) {
			if (neighbors[i] == -1) continue;
			if (board->field[neighbors[i]] == FLAG) continue;
			if (board->field[neighbors[i]] == NOINFO) return neighbors[i];
		}
	}



	printf("trying my best\n");
	random_when_unknown += 10;
	if (random_when_unknown > board->size) random_when_unknown = 0;
	*action = 'c';
	return random_when_unknown;
}

