#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void set_game_mode();
int tty_mode(int how);
void win_screen(int stage);
int start_title(FILE *inf, int* stage);
void new_addstr(int row, int col, char* newstr);
void init_title(FILE *inf);
