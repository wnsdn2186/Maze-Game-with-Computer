#include "game_process.h"
#include "setting.h"
#include "maze.h"

#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68

extern pid_t computer;  
extern pthread_t t1;
extern int count;

/***********************************************************************************************
 * 방향키 입력                                                                                 *
 * 리눅스에서 getchar()로 방향키 받을 시 리턴값을 3번 받아야함(getchar() 3번 연속 호출 해야함) *
 * 첫번째 값 = 27, 두번째 값 = 91, 세번째 값은 키마다 다르므로 밑에 각각 정의                  *
 * ex) 왼쪽 방향키 누를 시, getchar() == 27, getchar() == 91, getchar() == 68                  *
 * ********************************************************************************************/

void handler(int signum) {  //SIGINT, SIGQUIT처리
	endwin();
	tty_mode(1);
	exit(1);
}

/****************************************************************************
 * kill_computer(int signum)                                                *
 * 설명 : computer가 먼저 끝났을 시 부모프로세스에게 SIGTERM 보낸 후 종료   *
 * 	  부모프로세스에서 사용할 SIGTERM handler 함수                      *
 * 기능 : 자식 프로세스 kill, counter thread 종료, 터미널 설정 값 복구      *
 ****************************************************************************/

void kill_computer(int signum) {
	pthread_cancel(t1);
	pthread_join(t1,NULL);
	sleep(3);
	kill(computer, SIGKILL);
	endwin();
	tty_mode(1);
	//game over
	printf("You lose\n"); //예시
	exit(1);
}

/****************************************************************************
 * thread_function(void f*)                                                 *
 * 설명 : counter 함수                                                      *
 * 기능 : 경과시간을 초단위로 게임화면에 보여줌                             *
 ****************************************************************************/

void thread_function(void *f) {
	char time[20];
	count = 0;

	while(1) {
		sleep(1);
		sprintf(time, "time : %d", ++count);
		move(1, 23);
		addstr(time);
		refresh();
	}
}

void play_game(char* maze, int width, int height, int stage) {
	int row = 3, col = 3;
	int input;

	set_game_mode();
	initscr();
	ShowMaze(maze, width, height, stage);
	move(1, 23);
	addstr("time : 0");
	move(row, col);
	addstr("##");
	refresh();

	while(1) {
		input = getchar();
		if(row > width+1 && col > height+1) break; //도착
		//if(input == 'q') break;	
		if(input == 27) { //방향키 일때
			getchar(); //return 91
			input = getchar();
			switch(input) {
			case LEFT :
				moving(&row, &col, LEFT);	
				break;
			case RIGHT :
				moving(&row, &col, RIGHT);
				break;
			case UP :
				moving(&row, &col, UP);
				break;
 			case DOWN :
				moving(&row, &col, DOWN);
				break;	
			default : break;
			}
		}
	}
	clear();	
	endwin();
	tty_mode(1);
}

void computer_algorithm(char *maze, int width, int height, int stage) { //컴퓨터 알고리즘 시작 부분	
	int dir, count;
	int x, y;
	int dx, dy;
	int forward;
	int i, sleeptime = 150000; //stage 1
	
	for(i=1; i<stage; i++) {
		sleeptime = sleeptime * 0.9; //stage 증가될때마다 10%씩 빨라짐
	}

	maze[0 * width + 1] = 1;
	maze[(height - 1) * width + (width - 2)] = 1;

	forward = 1;
	dir = 0;
	count = 0;
	x = 1;
	y = 1;
	while (x != width - 2 || y != height - 2) {
		dx = 0; dy = 0;
		switch (dir) {
		case 0:  dx = 1;  break;
		case 1:  dy = 1;  break;
		case 2:  dx = -1; break;
		default: dy = -1; break;
		}
		if ((forward  && maze[(y + dy) * width + (x + dx)] == 0)
			|| (!forward && maze[(y + dy) * width + (x + dx)] == 2)) {
			maze[y * width + x] = forward ? 2 : 3;
			x += dx;

			y += dy;
			forward = 1;
			count = 0;
			dir = 0;
		}
		else {
			dir = (dir + 1) % 4;
			count += 1;
			if (count > 3) {
				forward = 0;
				count = 0;
			}
		}
		usleep(sleeptime);
	}

	maze[(height - 2) * width + (width - 2)] = 2;
	maze[(height - 1) * width + (width - 2)] = 2;
}

void moving(int *row, int *col, int direction) {
	int dir;
	char ptr[3];
	
	switch(direction) {
	case LEFT :
		dir = -2; 
		break;	
	case RIGHT : 
		dir = 2; 
		break;
	case UP : 
		dir = -1; 
		break;
	case DOWN :
		 dir = 1; 
		break;
	}

	if(direction == LEFT || direction == RIGHT)
		move(*row, *col+dir);
 	else
		move(*row+dir, *col);

	innstr(ptr, 2);

	if(strcmp(ptr, "[]") != 0) {
		new_addstr(*row, *col, "");
		if(direction == LEFT || direction == RIGHT)
			*col = *col + dir;
		else
			*row = *row + dir;
		new_addstr(*row, *col, "##");
		refresh();
	}
}
