#include "maze.h"
#include "game_process.h"
#include "setting.h"

pid_t computer;  
pthread_t t1;
int count;

void handler(int signum);
void kill_computer(int signum);
void thread_function(void *f);
void play_game(char* maze, int width, int height, int stage);
void computer_algorithm(char *maze, int width, int height, int stage);

int main()
{
	FILE *inf = fopen("title.txt", "r");
	int title_return;
	int stage;
	int width, height;
	char *maze;
	pid_t user = getpid();
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
		
	title_return = start_title(inf, &stage);
	if(title_return == 0) return 0;

	while(1) {
		//미로 만들기
		
		width = (stage+3) * 2 + 3;
		height = (stage+3) * 2 + 3;

		maze = (char*)malloc(width * height * sizeof(char));
		if (maze == NULL) {
			printf("error: not enough memory\n");
			exit(EXIT_FAILURE);
		}

		GenerateMaze(maze, width, height);

		if( (computer = fork()) == -1 ) {
			perror("fork");
		}
		else if( computer != 0 ) {              //user
			signal(SIGTERM, kill_computer);
			//사용자 알고리즘 부분 시작
			pthread_create(&t1, NULL, (void*)thread_function, (void*)NULL);
			play_game(maze, width, height, stage);
			//사용자 알고리즘 부분
		        kill(computer, SIGKILL);
			pthread_cancel(t1);
			pthread_join(t1, NULL);
			win_screen(stage);
			printf("You win\n");	
			stage++;
		}
		else {                                  //computer
			//컴퓨터 알고리즘 부분 시작
			computer_algorithm(maze, width, height, stage);
			ShowMaze2(maze, width, height, stage);
			//컴퓨터 알고리즘 부분 끝
			kill(user, SIGTERM);
			return 0; //필수
		}
	}
	
	free(maze);
	exit(EXIT_SUCCESS);

}
