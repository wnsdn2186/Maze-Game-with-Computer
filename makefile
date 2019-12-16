.PHONY: clean
	RM = rm -f
mirror: mirror_main.o game_process.o maze.o setting.o
	gcc -o mirror mirror_main.o game_process.o maze.o setting.o -lcurses -lpthread
maze.o: maze.c maze.h
	gcc -Wall -g -c maze.c -lcurses -lpthread
setting.o: setting.c setting.h
	gcc -Wall -g -c setting.c -lcurses -lpthread
game_process.o: game_process.c maze.h setting.h game_process.h
	gcc -Wall -g -c game_process.c -lcurses -lpthread
mirror_main.o: mirror_main.c maze.h setting.h game_process.h
	gcc -Wall -g -c mirror_main.c -lcurses -lpthread
clean:
	$(RM) *.o
