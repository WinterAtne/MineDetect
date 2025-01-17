#include <stdbool.h>

#include "board.c"
#include "rendering.c"

// Define our input method
short (*input)(Board*, char*);
#ifdef AI
	#include "ai_input.c"
	short (*input)(Board*, char*) = ai_input;
#else
	#include "pc_input.c"
	short (*input)(Board*, char*) = pc_input; //This is the definition of our input method
#endif

int main(int argc, char** argv) {
	//Board Properties
	char sizeX = 16;
	char sizeY = 16;
	short numBombs = 42;
	
	//Input Properties
	short position = 0;
	char action = 'c';

	//Game Over Conditions
	bool died   = false;
	bool won    = false;
	bool closed = false;
	short discoveredBombs = 0;

	//Create & Draw the initial blank board
	Board* shown = GenerateBlankBoard(sizeX, sizeY, numBombs, 0);
	DrawBoard(shown);

	//Get the first move
	position = input(shown, &action);

	//Create the hidden board
	Board* hidden = GenerateBoard(sizeX, sizeY, numBombs, position);
	switch (action) {
		case 'c':
			ClearTile(hidden, shown, position);
			break;
		case 'f':
			FlagTile(shown, position);
			break;
		case 'q':
			closed = true;
	}

	//Main Loop
	while (!died && !won && !closed) {
		DrawBoard(shown);
		
		position = input(shown, &action);
		
		switch (action) {
			case 'c':
				if (CheckTile(hidden, position)) died = true;
				ClearTile(hidden, shown, position);
				break;
			case 'f':
				if (CheckTile(hidden, position)) {
					discoveredBombs++;
					if (discoveredBombs == numBombs) {
						won = true;
					}
				}
				FlagTile(shown, position);
				break;
			case 'q':
				closed = true;
		}
	}

	if (died) {
		printf("You Died :(\n");
	} else if (won) {
		printf("You Won! :3\n");
	} else if (closed) {
		printf("Closing Game\n");
	}


	free(shown);
	free(hidden);
}

