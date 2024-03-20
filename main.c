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
  char bomb_hint_offsets[8] = { -19, -18, -17, -1, 1, 17, 18, 19 };
  
  srand (time(NULL));

  for (short i = 0; i < *retsize; i++) {
    field[i] = '0';
  }
  
  for (char i = 0; i < numBombs; i++) {
    char x = (rand() % (xSize - 2)) + 'A';
    char y = (rand() % (ySize - 1)) + 'A';
    short pos = XYToAbsolute(x, y, xSize - 2, *retsize);
    field[pos] = FLAG;
    
    for (char k = 0; k < 8; k++) {
      if (field[bomb_hint_offsets[k]+pos] != FLAG) {
        field[bomb_hint_offsets[k]+pos] += 1;
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

bool ClearTile(short position, char* hidden_field, char* shown_field) {
  if (hidden_field[position] == FLAG) {
    return true;
  }

  shown_field[position] = hidden_field[position];
  return false;
}

void FlagTile(short position) {
  printf("Flagging tile: %d \n", position);
}


int main(int argc, int** argv) {
  //Initialization
  char x = 16;
  char y = 16;
  char bombs = 32;
  short* field_size = (short*)malloc(sizeof(short));

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
    printf("%d\n", position);
    if (0 > position) {
      printf("Invalid input, please eneter real input.\n");
      continue;
    }

    if (clear == command[0]) {
      PlayerDied = ClearTile(position - 2, hidden_field, shown_field);
    }
    else if (flag == command[0]) {
      FlagTile(position - 2);
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

