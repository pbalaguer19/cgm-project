
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include "Cell.h"
#include "MapGenerator.h"


int WIDTH = 700;
int HEIGHT = 500;
Cell** map;
int COLUMNS;
int ROWS;

//-----------------------------------------------

void displayMap();
void windowReshapeFunc( GLint newWidth, GLint newHeight );
//-----------------------------------------------

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("PACMAN MAP");

  if(argc != 3) {
    std::cout << "Incorrect number of parameters\n";
    return 0;
  }

  std::cout << "Pacman game\n";

  int h = atoi(argv[1]);
  int w = atoi(argv[2]);
  ROWS = h;
  COLUMNS = w;

  MapGenerator mapGenerator(h, w);
  map = mapGenerator.generateMap();

  glutDisplayFunc(displayMap);
  glutReshapeFunc(windowReshapeFunc);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

  glutMainLoop();
  return 0;
}

//------------------------------------------------------------

//------------------------------------------------------------
void displayMap()
{
  int i,j;
  Cell cell;

  glClearColor(0.0,0.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0; i<ROWS; i++) {
    for(j=0; j<COLUMNS; j++){
      cell = map[i][j];
      if(cell.getCellType() == CORRIDOR) {
        glColor3f(0.8,0.8,0.8);
        glBegin(GL_QUADS);

        glVertex2i(i*WIDTH/COLUMNS,j*HEIGHT/ROWS);
        glVertex2i((i+1)*WIDTH/COLUMNS,j*HEIGHT/ROWS);
        glVertex2i((i+1)*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS);
        glVertex2i(i*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS);

        glEnd();
      }
    }
  }

  glutSwapBuffers();
}

void windowReshapeFunc( GLint newWidth, GLint newHeight ) {
  WIDTH = newWidth;
  HEIGHT = newHeight;

  glutPostRedisplay();
}
