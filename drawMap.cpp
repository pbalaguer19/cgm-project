
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include "Cell.h"
#include "MapGenerator.h"

/*
Students: Pau Balaguer and Didac Florensa
Practice 1. Exercise 2
*/

int WIDTH = 700;
int HEIGHT = 700;
int COLUMNS;
int ROWS;
Cell** map;

//-----------------------------------------------

void displayMap();
void windowReshapeFunc( GLint newWidth, GLint newHeight );
//-----------------------------------------------

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[]){

  if(argc < 3){
      std::cout << "./generate HEIGHT WIDTH" << "\n\n";
      std::cout << "MapGenerator rules:" << '\n';
      std::cout << " - Height >= 11. Always an even number" << '\n';
      std::cout << " - Width >= 9." << '\n';
      return 0;
  }

  int h = atoi(argv[1]);
  int w = atoi(argv[2]);
  ROWS = h;
  COLUMNS = w;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("PACMAN MAP");

  MapGenerator mapGenerator(h, w);
  map = mapGenerator.generateMap();
  mapGenerator.printMap();

  glutDisplayFunc(displayMap);
  glutReshapeFunc(windowReshapeFunc);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WIDTH-1,HEIGHT-1, 0);

  glutMainLoop();
  return 0;
}

//------------------------------------------------------------

//------------------------------------------------------------
void displayMap(){
  int i,j;
  Cell cell;

  glClearColor(0.0,0.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0; i<COLUMNS; i++) {
    for(j=0; j<ROWS; j++){
      cell = map[j][i];

      if(cell.getCellType() == CORRIDOR) {
        glColor3f(0.8,0.8,0.8);
        //glBegin(GL_QUADS);
        //glVertex2i(i*WIDTH/COLUMNS,j*HEIGHT/ROWS);
    	  //glVertex2i((i+1)*WIDTH/COLUMNS,j*HEIGHT/ROWS);
    	  //glVertex2i((i+1)*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS);
    	  //glVertex2i(i*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS);
        glBegin(GL_POLYGON);
        glVertex3f(i*WIDTH/COLUMNS, j*HEIGHT/ROWS, 0.0);
        glVertex3f((i+1)*WIDTH/COLUMNS,j*HEIGHT/ROWS, 0.0);
        glVertex3f((i+1)*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS, 0.0);
        glVertex3f(i*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS, 0.0);
        glEnd();
      }
    }
  }

  glutSwapBuffers();
}

void windowReshapeFunc( GLint newWidth, GLint newHeight ) {
  glutReshapeWindow(WIDTH, HEIGHT);
}
