MineDetect is a simple clone of minesweeper written entirely in raw C. It runs in the terminal, and should work on Linux, Mac, and Windows(altho the later two are untested). It comes bundled with an AI that can solve the game the majority of the time.

# Building
It should be compiled using the command
```
clang main.c
```

The program can then be run using ./a.out on linux.

By default the program will be set to AI mode, which means that it will run using the AI and will near instantly win or loose the game (minesweeper is not always winnable).
