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
	XYPosition xy;
	xy.y = board->sizeY % position;
	xy.x = position - (xy.y * position);
	return xy;
}

short XYToAbsolute(Board* board, XYPosition xy) {
	return xy.x + xy.y;
}

//callback takes in the board and a position
void CallOnNeighbors(void (*callback)(Board*, short), Board* board, short position) {
	char offsetX[8] = { -1, 0, -1, -1, 1, -1, 0, -1 };
	char offsetY[8] = { -1, -1, -1, 0, 0, 1, 1, 1};
	XYPosition xy = AbsoluteToXY(board, position);

	for (short i = 0; i < 8; i++) {
		XYPosition relative;
		relative.x = xy.x - offsetX[i];
		if (0 > relative.x || relative.x > board->sizeX) continue;
		relative.y = xy.y - offsetY[i];
		if (0 > relative.y || relative.y > board->sizeY) continue;

		short neighbor = XYToAbsolute(board, relative);
		callback(board, neighbor);
	}
}

void SetHint(Board* board, short position) {
	if (board->field[position] != FLAG) {
		return;
	}

	if (board->field[position] == CLEAR) {
		board->field[position] = '0';
	}

	board->field[position]++;
}

Board* GenerateBoard(char sizeX, char sizeY, char numBombs, short init_pos) {
	
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
		if (board->field[position] == FLAG || position == init_pos) {
			i--;
			continue;
		}
		board->field[position] = FLAG;
		
		CallOnNeighbors(SetHint, board, position);
	}

	//Return board and assume caller calls free()
	return board;
}
