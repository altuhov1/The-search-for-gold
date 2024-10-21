mp : main.o
	gcc main.o  global.c drawing.c mechanics.c -lncurses -o mp

const.o : main.c
	gcc -c main.c -o main.o
glonal.o : global.c
	gcc -c global.c -o global.o
drawing.o : drawing.c
	gcc -c drawing.c -o drawing.o
mechanics.o : mechanics.c
	gcc -c mechanics.c -o mechanics.o
clean : 
	rm mp *.o