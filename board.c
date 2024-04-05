//Define the board, and functions for working with it
#include <stdlib.h>
#include <time.h>

//Define the board elements besides numbers
#define CLEAR  '_'
#define FLAG   '!'
#define NOINFO '#'

//Define a board
typedef struct Board {
	char sizeX;
	char sizeY;
	short size;
	short numBombs;
	char* field;
} Board;

//Define an XY position
typedef struct XYPosition {
	char x;
	char y;
} XYPosition;

XYPosition AbsoluteToXY(Board* board, short position) {
	XYPosition relative;
	relative.y = board->sizeY % position;
	relative.x = position - (relative.y * position);
	return relative;
}

//callback takes in the board and a position
void CallOnNeighbors(void (*callback)(Board*, short), Board* board, short position) {
	for (short i = 0; i < 8; i++) {

	}
}

void SetHint(Board* board, short position) {
	if (board->field[position] != FLAG) {
		return;
	}

	if (board->field[position] == '0') {
		board->field[position] = '0';
	}

	board->field[position]++;
}

Board* GenerateBoard(char sizeX, char sizeY, char numBombs) {
	
	//Initialize Board
	Board *board = (Board*) malloc(sizeof(Board));

	board->sizeX = sizeX;
	board->sizeY = sizeY;
	board->size = sizeX * sizeY;
	board->numBombs = numBombs;
	board->field = (char*) malloc(board->size);

	for (short i = 0; i < board->size; i++) {
		board->field[i] = CLEAR;
	}


	//Place Bombs
	srand(time(NULL));
	for (char i = 0; i < numBombs; i++) {
		short position = rand() % board->size;
		if (board->field[position] == FLAG) {
			i--;
			continue;
		}
		board->field[position] = FLAG;
		
		CallOnNeighbors(SetHint, board, position);
	}

	//Return board and assume caller calls free()
	return board;
}
