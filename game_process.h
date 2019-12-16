#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void handler(int signum);
void kill_computer(int signum);
void thread_function(void *f);
void play_game(char* maze, int width, int height, int stage);
void computer_algorithm(char *maze, int width, int height, int stage);
void moving(int *row, int *col, int direction);
