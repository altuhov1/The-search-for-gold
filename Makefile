mp : main.o global.o drawing.o game_mechanics.o space_creation.o console_work.o
	gcc main.o  global.o drawing.o game_mechanics.o space_creation.o console_work.o -lncurses -o mp

const.o : main.c
	gcc -c main.c -o main.o
glonal.o : global.c
	gcc -c global.c -o global.o
drawing.o : drawing.c
	gcc -c drawing.c -o drawing.o
game_mechanics.o : game_mechanics.c
	gcc -c game_mechanics.c -o game_mechanics.o
space_creation.o : space_creation.c
	gcc -c space_creation.c -o space_creation.o
console_work.o : console_work.c
	gcc -c console_work.c -o console_work.o
clean : 
	rm mp *.o