program: main.c
	gcc -o program main.c algo.c SDL.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -lSDL2_ttf -lm -ldl

run: program
	./program
	
