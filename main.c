#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define NOINFO '#'
#define CLEAR '_'
#define FLAG '!'

const char quit = 'q';
const char flag = 'f';
const char clear = 'c';

bool PlayerDied = false;
bool PlayerWon = false;
bool PlayerQuit = false;

char verticle_offset[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
char side_offset[8] = {     -1,  0,  1,-1, 1,-1, 0, 1 };

short XYToAbsolute(char x, char y, short fieldX, short field_size) {
	short ret = ((fieldX + 2) * (y - 'A')) + (x - 'A') + fieldX + 5;

	if (field_size < ret) return -1;
	return ret;
}

char* GenerateField(char xSize, char ySize, char numBombs, short* retsize) {
	xSize += 2;
	ySize += 1;
	*retsize = xSize * ySize;
	char* field = (char*)malloc(*retsize * sizeof(char));
	printf("Welcome to MineSweep!\n"); // Not having this here causes random segfaults;
	
	srand (time(NULL));

	for (short i = 0; i < *retsize; i++) {
		field[i] = CLEAR;
	}
	
	//Place Bombs
	for (char i = 0; i < numBombs; i++) {
		char x = (rand() % (xSize - 2)) + 'A';
		char y = (rand() % (ySize - 1)) + 'A';
		short pos = XYToAbsolute(x, y, xSize - 2, *retsize);
		if (field[pos] == FLAG) { //Lets us try again if we hit the same spot twice;
			i--;
			continue;
		} 
		field[pos] = FLAG;
		
		for (char k = 0; k < 8; k++) {
			short offset = verticle_offset[k] * (xSize) + side_offset[k] + pos;

			if (field[offset] == CLEAR) {
				field[offset] = '0';
			}

			if (field[offset] >= '0' && field[offset] <= '9') {
				field[offset]++;
				continue;
			}
		}
	}
	
	//Format Collumn indexes
	field[0] = '-';
	for (char i = 1; i < xSize - 1; i++) {
		field[i] = i + 'A' - 1;
	}
	
	//Format Columns, row index && line-breaks;
	for (short i = xSize-1; i < *retsize; i+=xSize) {
		field[i] = '\n';
		field[i+1] = (i/xSize) + 'A';
	}
	
	
	
	return field;
}

void RecursiveClearTile(short position, char xSize, char* hidden_field, char* shown_field, short field_size) {
	for (int i = 0; i < 8; i++) {
		short offset_position = verticle_offset[i] * (xSize + 2) + side_offset[i] + position; 
		if (offset_position >= field_size || offset_position <= 0 || shown_field[offset_position] != NOINFO) {
			continue;
		}
		
		if (hidden_field[offset_position] == CLEAR) {
			shown_field[offset_position] = hidden_field[offset_position];
			RecursiveClearTile(offset_position, xSize, hidden_field, shown_field, field_size);
		}
		
		if (hidden_field[offset_position] > '0' && hidden_field[offset_position] < '9') {
			shown_field[offset_position] = hidden_field[offset_position];
		}

	}
}

bool ClearTile(short position, char xSize, char* hidden_field, char* shown_field, short field_size) {
	if (shown_field[position] == FLAG) {
		return false;
	}

	if (hidden_field[position] == FLAG) {
		return true;
	}
	
	shown_field[position] = hidden_field[position];
	if (shown_field[position] == CLEAR) {
		RecursiveClearTile(position, xSize, hidden_field, shown_field, field_size);
	}

	return false;
}

bool FlagTile(short position, char* shown_field, char* hidden_field, char* discovered_bombs, char numBombs) {
	if (shown_field[position] != NOINFO) {
		return false;
	}
	
	shown_field[position] = FLAG;
	if (hidden_field[position] == FLAG) {
		*discovered_bombs += 1;
		if (*discovered_bombs == numBombs) {
			return true;
		}
	}

	return false;
}


int main(int argc, char** argv) {
	//Initialization
	char x = 16;
	char y = 16;
	char bombs = 16;
	short* field_size = (short*)malloc(sizeof(short));
	char* discovered_bombs = (char*)calloc(1, sizeof(char));

	char* hidden_field = GenerateField(x, y, bombs, field_size);
	char* shown_field = (char*)malloc(*field_size * sizeof(char));
	shown_field = memcpy(shown_field, hidden_field, *field_size);
	for (char i = 'A' - 2; i < 'A' + x - 2; i++) {
		for (char k = 'A'; k < 'A' + y; k++) {
			shown_field[XYToAbsolute(i, k, x, *field_size)] = NOINFO;
		}
	}
	
	// Main Loop
	while (!PlayerDied && !PlayerWon && !PlayerQuit) {
		//Initialize Loop;


		//Draw
		for (int i = 0; i < *field_size; i++) {
			putchar(shown_field[i]);
		}
		
		//User input
		char command[8];

		fgets(command, sizeof(command), stdin);
		if (quit == command[0]) { //We do this here so that we don't attempt to get the position
			PlayerQuit = true;
			break;
		}
		
		short position = XYToAbsolute(command[2], command[3], x, *field_size);
		if (0 > position) {
			printf("Invalid input, please eneter real input.\n");
			continue;
		}

		if (clear == command[0]) {
			PlayerDied = ClearTile(position - 2, x, hidden_field, shown_field, *field_size);
		}
		else if (flag == command[0]) {
			PlayerWon = FlagTile(position - 2, shown_field, hidden_field, discovered_bombs, bombs);
		}
		else {
			printf("Invalid Input, please select real input.\n");
		}
	}
	
	//Exit
	if (PlayerQuit) {
		printf("QUITTING!\n");
	} else if (PlayerDied) {
		printf("YOU DIED!\n");
	} else if (PlayerWon) {
		printf("YOU WON!\n");
	}

	free(hidden_field);
	free(shown_field);
	free(field_size);
	return 0;
}

