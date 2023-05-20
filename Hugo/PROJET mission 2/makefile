all : PROJET EXECUTION
code.o : code.c code.h
	gcc -c code.c -w -lm -Wall `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -ldl -lSDL2_ttf
main.o : main.c code.h
	gcc -c main.c -w -lm -Wall `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -ldl -lSDL2_ttf
PROJET : code.o main.o
	gcc -o PROJET code.o main.o -w `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -ldl -lm -lSDL2_ttf
EXECUTION : 
	./PROJET
