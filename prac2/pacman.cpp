
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include "Cell.h"
#include "MapGenerator.h"
#include "particle.h"
#include "PacMan.h"

/*
Students: Pau Balaguer and Didac Florensa
Practice 1. Exercise 2
*/

float WIDTH = 500.0;
float HEIGHT = 500.0;
int COLUMNS;
int ROWS;

PacMan* pacMan;
long last_t=0;

//-----------------------------------------------

void displayMap();
void windowReshapeFunc( GLint newWidth, GLint newHeight );
void keyboard(int key, int x, int y);
void idle();

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

  pacMan = new PacMan(COLUMNS, ROWS, WIDTH, HEIGHT);

  glutDisplayFunc(displayMap);
  glutReshapeFunc(windowReshapeFunc);
  glutSpecialFunc(keyboard);
  glutIdleFunc(idle);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WIDTH-1, 0, HEIGHT-1);

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
      pacMan->drawCorridor(i, j);
      pacMan->drawFood(i, j);
    }
  }

  pacMan->drawGhosts();
  pacMan->drawPlayer();
  glutSwapBuffers();
}

void windowReshapeFunc( GLint newWidth, GLint newHeight ) {
  glutReshapeWindow(WIDTH, HEIGHT);
}

void keyboard(int key, int x, int y){
  switch(key){
    case GLUT_KEY_UP:
      pacMan->playerUP();
      break;
    case GLUT_KEY_DOWN:
      pacMan->playerDOWN();
      break;
    case GLUT_KEY_LEFT:
      pacMan->playerLEFT();
      break;
    case GLUT_KEY_RIGHT:
      pacMan->playerRIGHT();
      break;
  }
};

void idle(){
  long t;
  t = glutGet(GLUT_ELAPSED_TIME);

  if(last_t == 0){
    last_t = t;
  }
  else{
      pacMan->integrate(t-last_t);
      last_t = t;
    }
  glutPostRedisplay();
}
