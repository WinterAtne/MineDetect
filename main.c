#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
  short ret = ((fieldX + 2) * (y - 'A')) + (x - 'A') + fieldX + 2;

  if (field_size <= ret) return -1;
  return ret;
}

char* GenerateField(char xSize, char ySize, char numBombs, short* retsize) {
  xSize += 2;
  ySize += 1;
  *retsize = xSize * ySize;
  char* field = (char*)malloc(*retsize * sizeof(char));
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

bool ClearTile(short position) {
  printf("Clearing tile: %d \n", position);
  return false;
}

void FlagTile(short position) {
  printf("Flagging tile: %d \n", position);
}


int main(int argc, int** argv) {
  //Initialization
  short* field_size;
  char* hidden_field = GenerateField(16, 16, 32, field_size);
  
  
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
    if (0 > position) {
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

