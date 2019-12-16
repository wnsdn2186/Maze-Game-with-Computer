#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void ShowMaze(const char *maze, int width, int height, int stage);
void ShowMaze2(const char *maze, int width, int height, int stage);
void CarveMaze(char *maze, int width, int height, int x, int y);
void GenerateMaze(char *maze, int width, int height);

