#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NOINFO '#'
#define CLEAR '_'
#define FLAG '!'

const char quit = 'q';
const char flag = 'f';
const char clear = 'c';

bool PlayerDied = false;
bool PlayerWon = false;
bool PlayerQuit = false;


char* GenerateField(char xSize, char ySize, char numBombs, short* retsize) {
  xSize += 2;
  ySize += 1;
  *retsize = xSize * ySize;
  char* field = (char*)malloc(*retsize * sizeof(char));
  
  for (short i = 0; i < *retsize; i++) {
    
    field[i] = NOINFO;
  }
  
  //Format Collumn indexes
  field[0] = '-';
  for (char i = 1; i < xSize - 1; i++) {
    field[i] = i + 'A' - 1;
  }
  
  //Format Columns, row index && line-breaks;
  for (short i = xSize-1; i < *retsize; i+=xSize) {
    field[i] = '\n';
    field[i+1] = ((i/xSize) % 10) + '0';
  }
  
  return field;
}

bool ClearTile(short position) {
  printf("Clearing tile: %d \n", position);
  return true;
}

void FlagTile(short position) {
  printf("Flagging tile: %d \n", position);
}

short XYToAbsolute(char x, char y, short fieldX, short field_size) {
  short ret = ((fieldX + 2) * (y - '0')) + 
               (x - 'A') + ((y - '0') * 2) +
               fieldX + 4;
  if (field_size <= ret) return -1;

  return ret;
}

int main(int argc, int** argv) {
  //Initialization
  short* field_size;
  char* hidden_field = GenerateField(16, 16, 15, field_size);
  
  
  // Main Loop
  while (!PlayerDied && !PlayerWon && !PlayerQuit) {
    //Initialize Loop;


    //Draw
    for (int i = 0; i < *field_size; i++) {
      putchar(hidden_field[i]);
    }
    
    //User input
    char command[8];

    fgets(command, sizeof(command), stdin);
    if (quit == command[0]) { //We do this here so that we don't attempt to get the position
      PlayerQuit = true;
      break;
    }
    
    short position = XYToAbsolute(command[2], command[3], 16, *field_size);
    if (-1 == position) {
      printf("Invalid input, please eneter real input.\n");
      continue;
    }

    if (clear == command[0]) {
      PlayerDied = ClearTile(position);
    }
    else if (flag == command[0]) {
      FlagTile(position);
    }
    else {
      printf("Invalid Input, please select real input.\n");
    }

  }
  
  //Exit

  return 0;
}

