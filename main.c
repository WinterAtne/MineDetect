#include <stdio.h>
#include <stdlib.h>

#define NOINFO '#'
#define CLEAR '_'
#define FLAG '!'

const char x = 16;
const char y = 16;
const char bombs = 15;

char PlayerDied = 0;
char PlayerWon = 0;
char PlayerQuit = 0;


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



int main(int argc, int** argv) {
  //Initialization
  short* field_size;
  char* hidden_field = GenerateField(x, y, bombs, field_size);
  
  
  // Main Loop
  while (!PlayerDied || !PlayerWon || !PlayerQuit) {
    //Initialize Loop;

    char* command = (char*)calloc(8, sizeof(char));

    //Draw
    for (int i = 0; i < *field_size; i++) {
      putchar(hidden_field[i]);
    }
    
    //User input
    fgets(command, sizeof(command), stdin);

  }
  
  //Exit

  return 0;
}


