//This handles rendering a board to the console
#include <stdio.h>

#include "board.c"

//This portion of the code, and by extention clrscr is untested on windows
#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void DrawBoard(Board* board) {
	//clrscr();
	
	//Create the collumn indices
	putchar(' ');
	for (short x = 0; x < board->sizeX; x++) {
		putchar('A' + x);
	}
	putchar('\n');
	
	for (short y = 0; y < board->sizeY; y++) {
		putchar('A' + y); //Adds the row indices
		
		for (short x = 0; x < board->sizeX; x++) {
			putchar(board->field[XYToAbsolute(board, x, y)]);
		}
		
		putchar('\n');
	}
}

//int main() {
//	Board *hidden = GenerateBoard(16, 16, 42, 0);
//	Board *clearboard = GenerateBlankBoard(hidden, 0);
//
//	DrawBoard(clearboard);
//	DrawBoard(hidden);
//	return 0;
//}
