program: main.c
	gcc -o program main.c algo.c SDL.c Mahir.c Hugo.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -lSDL2_ttf -lm -ldl -lSDL2_image

run: program
	./program
	
valgrind: program
	valgrind --leak-check=full ./program 