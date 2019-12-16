#include "maze.h"

void ShowMaze(const char *maze, int width, int height, int stage) {
	int x, y;
	int row = 3, col;
	char prompt[50];
	sprintf(prompt, "stage : %d", stage);
	move(1, 1);
	addstr(prompt);


	for (y = 0; y < height; y++) {
		col = 1;
		move(row, col);
		for (x = 0; x < width; x++) {
			switch (maze[y * width + x]) {
			case 1:  addstr("[]");  break;
			case 2:  addstr("##");  break;
			default: addstr("  ");  break;
			}
			col+=2;
			move(row, col);
			
		}
		row++;
	}
	refresh();
}


void ShowMaze2(const char *maze, int width, int height, int stage) {
	ShowMaze(maze, width, height, stage);
	refresh();
	move(2, 1);
	addstr("You Lose!!!");
	refresh();
}


void CarveMaze(char *maze, int width, int height, int x, int y) {

	int x1, y1;
	int x2, y2;
	int dx, dy;
	int dir, count;

	dir = rand() % 4;
	count = 0;
	while (count < 4) {
		dx = 0; dy = 0;
		switch (dir) {
		case 0:  dx = 1;  break;
		case 1:  dy = 1;  break;
		case 2:  dx = -1; break;
		default: dy = -1; break;
		}
		x1 = x + dx;
		y1 = y + dy;
		x2 = x1 + dx;
		y2 = y1 + dy;
		if (x2 > 0 && x2 < width && y2 > 0 && y2 < height
			&& maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
			maze[y1 * width + x1] = 0;
			maze[y2 * width + x2] = 0;
			x = x2; y = y2;
			dir = rand() % 4;
			count = 0;
		}
		else {
			dir = (dir + 1) % 4;
			count += 1;
		}
	}

}

void GenerateMaze(char *maze, int width, int height) {

	int x, y;

	for (x = 0; x < width * height; x++) {
		maze[x] = 1;
	}

	maze[1 * width + 1] = 0;

	srand(time(0));

	for (y = 1; y < height; y += 2) {
		for (x = 1; x < width; x += 2) {
			CarveMaze(maze, width, height, x, y);
		}
	}

	maze[0 * width + 1] = 0;
	maze[(height - 1) * width + (width - 2)] = 0;

}
