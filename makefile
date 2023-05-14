program: main.c
	gcc -o program main.c `sdl2-config --cflags --libs` -lSDL2_gfx -lm -ldl

run: program
	./program
	


