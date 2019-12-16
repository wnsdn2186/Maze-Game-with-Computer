#include "setting.h"

#define max_level 10
#define RIGHT 67
#define LEFT 68

extern int count;

void set_game_mode() {   //canonical mode and no echo
	struct termios ttystate;
	tcgetattr(0, &ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &ttystate);
}

int tty_mode(int how) {  //recover original terminal setting
	static struct termios original_mode;
	if(how == 0) {
		return tcgetattr(0, &original_mode);
	}else {
		return tcsetattr(0, TCSANOW, &original_mode);
	}
}

void win_screen(int stage) {
	int i, input;
	char str1[20] = "You Win!!!";
	//char str2[20];
	char str3[20];
	char str4[1];
	char str5[20];
	char time[20];
	
	sprintf(str3, "stage : %d", stage);
	sprintf(time, "time : %d(sec)", count);

	set_game_mode();
	initscr();

	while((input = getchar())) {
		for(i=0; i<strlen(str1); i++) {
			move(3, 3+i);
			str4[0] = str1[i];
			addstr(str4);
			refresh();
			usleep(100000);
		}
		new_addstr(5,3,str3);
		refresh();
		sleep(1);
		new_addstr(6,3,time);
		refresh();
		sleep(1);
		new_addstr(7, 3, "going to next stage");
		refresh();
		for(i=0; i<3; i++) {
			sprintf(str5, "wait %d second....", 3-i);
			new_addstr(8, 3, str5);	
			refresh();
			sleep(1);
		}
		break;
	}
	endwin();
	clear();
	tty_mode(1);
}

/***********************************************************************************
 * start_title(FILE *inf, int* level)                                              * 
 * 설명 : 게임 시작 화면 출력, 게임 진행을 위한 키보드 입력 받는 함수              *
 * 기능 : 시작 : S, 종료 : e, 방향키(<- ->) 를 통해 stage선택 가능(stage : 1 ~ 10) *
 *        키보드 입력에 대한 정보(start or end)를 int 형태로 return                *
 **********************************************************************************/

int start_title(FILE *inf, int* stage) { //title 시작 함수
	int input;
	char le[2], return_value = -1;
	*stage = 1;
	
	tty_mode(0);
	set_game_mode();
	initscr();

	init_title(inf);
	refresh();

	while(1) {
		input = getchar();	
		switch(input) {
		case 'e': 
			return_value = 0;  //end -> 0 return 
			break;
		case 's':
		        return_value = 1;  //start -> 1 return
			break;
		case 27: //방향키 일때
			getchar(); //return 91
			input = getchar();
			if(input == LEFT) {
				if((*stage) > 1) (*stage)--;
				sprintf(le, "%d", (*stage));  
				new_addstr(21, 47, le);
				refresh();
			}		
			else if(input == RIGHT) {
				if((*stage) < max_level) (*stage)++;
				sprintf(le, "%d", (*stage));
				new_addstr(21, 47, le);
				refresh();
			}
		       	break; 
		default : break;
		}
		if(return_value == 0 || return_value == 1) break;	
	}
	clear();	
	endwin();
	tty_mode(1);
	return return_value;
}


void new_addstr(int row, int col, char* newstr) { // 해당 row, col에 새로운 문자열 넣기
	move(row, col);
	addstr("  ");
	move(row, col);
	addstr(newstr);
}

void init_title(FILE *inf) {  //title화면 초기화 함수
	char strTemp[255];
	int row = 0;

	while( !feof(inf)) 
	{
	        fgets(strTemp, sizeof(strTemp), inf);
		move(row, 0);
		addstr(strTemp);
		row++;
	}
	fclose(inf);
}
