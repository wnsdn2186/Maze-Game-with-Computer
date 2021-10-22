# SystemProgramming

###############################
*            README           *
###############################

########################################
*2019-2 시스템 프로그래밍 팀프로젝트 11팀 *
*주제 : 미로찾기 게임                   **
########################################

#################게임설명################
컴퓨터와 미로찾기 대결하는 게임이다.

###########게임 실행전 필수사항###########
1. 컴파일 시 gcc -o mirror game_process.c maze.c mirror_main.c setting.c -lcurses -lpthread 입력
2. 실행 파일(mirror)와 같은 디렉토리에 title.txt 파일이 있어야함(시작 화면 구성 위한 파일)
3. mirror 실행 전에 터미널 크기를 최대화 해야함(터미널 크기 줄인 상태에서 실행 후 다시키우면 화면 깨짐)

###############게임 실행후###############

################초기 화면################
* 방향키 왼쪽, 오른쪽키로 스테이지 설정가능 (1 ~ 15)
* s키 누르면 해당 스테이지로 시작
* e키 누르면 종료

################게임 시작################
* 방향키를 사용해 캐릭터 이동
* 스테이지에서 이겼을시 해당 스테이지, 도착까지 걸린시간 출력 후 다음스테이지(현재스테이지+1)로 이동
* 스테이지가 증가하면 컴퓨터 알고리즘 속도도 빨라지고 미로크기도 증가함
* 스테이지에서 졌을 시 컴퓨터가 찾은 경로를 보여주고 게임 종료
* 게임 실행도중 Ctrl-C, Ctrl-\ 입력 시 게임종료

#################주의사항#################
* 컴파일에 필요한 모든 파일은 같은 디렉토리 안에 있어야함
* game_process.c game_process.h maze.c maze.h mirror_main.c setting.c setting.h title.txt 

