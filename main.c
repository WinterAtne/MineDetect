#include <stdbool.h>

#include "board.c"
#include "rendering.c"

short test_in(Board* board, char* action) {
	*action = 'c';
	return 128;
}

int main(int argc, char** argv) {
	//Board Properties
	char sizeX = 16;
	char sizeY = 16;
	short numBombs = 42;
	
	//Input Properties
	short (*input)(Board*, char*) = test_in; //This is the definition of our input method
	short position = 0;
	char action = 'c';

	//Game Over Conditions
	bool died   = false;
	bool won    = false;
	bool closed = false;

	//Create & Draw the initial blank board
	Board* shown = GenerateBlankBoard(sizeX, sizeY, numBombs, 0);
	DrawBoard(shown);

	//Get the first move
	position = input(shown, &action);

	//Create the hidden board
	Board* hidden = GenerateBoard(sizeX, sizeY, numBombs, position);
	ClearTile(hidden, shown, position);

	//Main Loop
	while (!died && !won && !closed) {
		DrawBoard(shown);
		position = input(shown, &action);
		ClearTile(hidden, shown, position);

		won = true;
	}


	free(shown);
	free(hidden);
}

