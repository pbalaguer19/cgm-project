ex1:
	g++ generate.cpp -o generate -std=c++0x -lm
ex2:
	gcc -lglut -lGLU -lGL -lm drawMap.cpp -Wno-deprecated-declarations -o drawMap
ex2mac:
	g++ -framework OpenGL -framework GLUT -framework Cocoa -lm -std=c++0x -Wno-deprecated-declarations drawMap.cpp -o drawMap
