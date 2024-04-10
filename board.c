#pragma once
//Define the board, and functions for working with it
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//Define the board elements besides numbers
#define CLEAR  ' '
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
	xy.y = position / board->sizeY;
	xy.x = position - (xy.y * board->sizeY);
	return xy;
}

short XYToAbsolute(Board* board, char x, char y) {
	return y * board->sizeX + x;
}

//callback takes in the board and a position
void CallOnNeighbors(void (*callback)(Board*, Board*, short), Board* board, Board* clear, short position) {
	char offsetX[8] = { -1,  0,  1, -1,  1, -1,  0,  1 };
	char offsetY[8] = { -1, -1, -1,  0,  0,  1,  1,  1};
	XYPosition xy = AbsoluteToXY(board, position);

	for (short i = 0; i < 8; i++) {
		char x = xy.x + offsetX[i];
		char y = xy.y + offsetY[i];
		if (0 > x || x > board->sizeX - 1) continue;
		if (0 > y || y > board->sizeY - 1) continue;

		short neighbor = XYToAbsolute(board, x, y);
		callback(board, clear, neighbor);
	}
}

void SetHint(Board* board, Board* clear, short position) {
	if (board->field[position] == FLAG) {
		return;
	}

	if (board->field[position] == CLEAR) {
		board->field[position] = '0';
	}

	board->field[position]++;
}

void ClearTile(Board* hidden, Board* clear, short position) {
	if (hidden->field[position] == CLEAR && clear->field[position] == NOINFO) {
		clear->field[position] = hidden->field[position];
		CallOnNeighbors(ClearTile, hidden, clear, position);
	}
	clear->field[position] = hidden->field[position];
}

void FlagTile(Board* clear, short position) {
	if (clear->field[position] == NOINFO) {
		clear->field[position] = FLAG;
	}
}

Board* GenerateBoard(char sizeX, char sizeY, char numBombs, short init_pos) {
	srand(time(NULL));
	
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
	for (char i = 0; i < board->numBombs; i++) {
		short x = rand() % board->sizeX;
		short y = rand() % board->sizeY;
		short position = XYToAbsolute(board, x, y);
		if (board->field[position] == FLAG || position == init_pos) {
			i--;
			continue;
		}
		board->field[position] = FLAG;
		
		CallOnNeighbors(SetHint, board, NULL, position);
	}

	return board;
}

Board* GenerateBlankBoard(char sizeX, char sizeY, char numBombs, short init_pos) {
	Board *blank = (Board*) malloc(sizeof(Board));
	
	blank->sizeX = sizeX;
	blank->sizeY = sizeY;
	blank->size = sizeX * sizeY;
	blank->numBombs = numBombs;
	blank->field = (char*) malloc(blank->size);

	memset(blank->field, NOINFO, blank->size * sizeof(char));

	return blank;
}

//int main() {
//	Board *board = GenerateBoard(16, 16, 16, 0);
//	for (short y = 0; y < board->sizeY; y++) {
//		for (short x = 0; x < board->sizeX; x++) {
//			putchar(board->field[XYToAbsolute(board, x, y)]);
//		}
//		
//		putchar('\n');
//	}
//	return 0;
//}

