pacmanMac:
	g++ -framework OpenGL -framework GLUT -framework Cocoa -lm -std=c++0x -Wno-deprecated-declarations pacman.cpp -o pacman

pacman:
	g++ pacman.cpp -o pacman -lglut -lGLU -lGL -lm

clear:
	rm pacman

all:
	make clear; make
