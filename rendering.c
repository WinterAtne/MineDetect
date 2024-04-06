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
	for (short y = 0; y < board->sizeY; y++) {
		for (short x = 0; x < board->sizeX; x++) {
			putchar(board->field[XYToAbsolute(board, x, y)]);
		}
		
		putchar('\n');
	}
	
}

//int main() {
//	Board *board = GenerateBoard(16, 16, 42, 0);
//	DrawBoard(board);
//	return 0;
//}
