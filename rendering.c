#pragma once
//This handles rendering a board to the console
#include <stdio.h>

#include "board.c"

#define clrscr() printf("\e[1;1H\e[2J")

const char RESET[] = "\x1b[0m";
const char BGNOINFO[] = "\x1b[47m";
const char BGFLAG[] = "\x1b[41m";
const char FG1[] = "\x1b[36m"; 
const char FG2[] = "\x1b[32m"; 
const char FG3[] = "\x1b[31m"; 
const char FG4[] = "\x1b[34m"; 

void DrawBoard(Board* board) {
	clrscr();
	
	//Create the collumn indices
	putchar(' ');
	for (short x = 0; x < board->sizeX; x++) {
		putchar('A' + x);
	}
	putchar('\n');
	
	for (short y = 0; y < board->sizeY; y++) {
		putchar('A' + y); //Adds the row indices
		
		for (short x = 0; x < board->sizeX; x++) {
			char tile = board->field[XYToAbsolute(board, x, y)];
			switch (tile) {
				case NOINFO:
					printf("%s%c%s", BGNOINFO, tile, RESET);
					break;
				case FLAG:
					printf("%s%c%s", BGFLAG, tile, RESET);
					break;
				case '1':
					printf("%s%c%s", FG1, tile, RESET);
					break;
				case '2':
					printf("%s%c%s", FG2, tile, RESET);
					break;
				case '3':
					printf("%s%c%s", FG3, tile, RESET);
					break;
				case '4':
					printf("%s%c%s", FG4, tile, RESET);
					break;
				case '5':
					printf("%s%c%s", FG4, tile, RESET);
					break;
				case '6':
					printf("%s%c%s", FG4, tile, RESET);
					break;
				case '7':
					printf("%s%c%s", FG4, tile, RESET);
					break;
				case '8':
					printf("%s%c%s", FG4, tile, RESET);
					break;
				default:
					putchar(tile);
					break;
			}
		}
		
		putchar('\n');
	}
}

//int main() {
//	Board *hidden = GenerateBoard(16, 16, 42, 0);
//	Board *clearboard = GenerateBlankBoard(16, 16, 42, 0);
//
//	DrawBoard(clearboard);
//	DrawBoard(hidden);
//	return 0;
//}
