# SystemProgramming

## Description
- KNU Computer Science and Engineering term project for System Programming

## Introduction
There is a maze search game with a computer.
1. We used the Ubuntu Linux environment.
2. We used DFS to make and find a maze.

## Development Environment
- Ubuntu 16.04
- Linux C

## Caution
- Title.txt file must exist in the same directory as the executable file.
- Terminal size needs to be maximized before execution.
- All files needed for compilation must be in the same directory.

## Run
- Enter gcc -o mirror game_process.c maze.c mirror_main.c setting.c -lcurses -lpthread when compiling.
- Use the arrow key to move the character.
- If you win the stage, print out the time it took to arrive and move to the next stage (current stage +1).
- As the stage increases, the algorithm speeds up and the maze size increases.
- If you lose on stage, show the path the computer found and end the game.


