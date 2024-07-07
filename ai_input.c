#pragma once
// The AI input method
#include <unistd.h>
#include "board.c"



short ai_input(Board* board, char* action) {
	// Simple Algorithm checking numbered tiles for neighboring bombs;
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
	*action = 'c';
	short random_when_unknown = 0;
	while (true) {
		if (board->field[random_when_unknown] == NOINFO) {
			return random_when_unknown;
		} else if (board->size < random_when_unknown) {
			random_when_unknown = 0;
		} else {
			random_when_unknown++;
		}
	}
	return random_when_unknown;
}

