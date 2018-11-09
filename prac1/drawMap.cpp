
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

float WIDTH = 500.0;
float HEIGHT = 500.0;
int COLUMNS;
int ROWS;
float pixelsPerColmns;
float pixelsPerRow;
Cell** map;
int sizeCellX;
int sizeCellY;

int playerXPos = 1;
int playerYPos = 1;

//-----------------------------------------------

void displayMap();
void drawCorridor(Cell cell, int i, int j);
void drawFood(Cell cell, int i, int j);
void checkPlayer(Cell cell, int i, int j);
float getPosition(int n, float CellSize);
void windowReshapeFunc( GLint newWidth, GLint newHeight );
void keyboard(int key, int x, int y);

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

  pixelsPerColmns = WIDTH / COLUMNS;
  pixelsPerRow = HEIGHT / ROWS;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("PACMAN MAP");

  MapGenerator mapGenerator(h, w);
  map = mapGenerator.generateMap();
  map[playerXPos][playerYPos].setCellType(PLAYER);
  mapGenerator.printMap();

  glutDisplayFunc(displayMap);
  glutReshapeFunc(windowReshapeFunc);
  glutSpecialFunc(keyboard);

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
      cell = map[j][i];
      drawCorridor(cell, i, j);
      drawFood(cell, i, j);
      checkPlayer(cell, i, j);
    }
  }
  glutSwapBuffers();
}

void windowReshapeFunc( GLint newWidth, GLint newHeight ) {
  glutReshapeWindow(WIDTH, HEIGHT);
}

void keyboard(int key, int x, int y){
  int oldX = playerXPos;
  int oldY = playerYPos;

  switch(key){
    case GLUT_KEY_UP:
      playerXPos ++;
      break;
    case GLUT_KEY_DOWN:
      playerXPos --;
      break;
    case GLUT_KEY_LEFT:
      playerYPos --;
      break;
    case GLUT_KEY_RIGHT:
      playerYPos ++;
      break;
  }
  map[oldX][oldY].setCellType(CORRIDOR);
  map[playerXPos][playerYPos].setCellType(PLAYER);
  glutPostRedisplay();

};

void drawCorridor(Cell cell, int i, int j){
  if(cell.getCellType() != WALL) {
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
    glVertex2i(i*pixelsPerColmns,j*pixelsPerRow);
    glVertex2i((i+1)*pixelsPerColmns,j*pixelsPerRow);
    glVertex2i((i+1)*pixelsPerColmns,(j+1)*pixelsPerRow);
    glVertex2i(i*pixelsPerColmns,(j+1)*pixelsPerRow);
    glEnd();
  }
}

void drawFood(Cell cell, int i, int j) {
  float x, y;
  if(cell.getCellType() == FOOD){
    x = getPosition(i, pixelsPerColmns);
    y = getPosition(j, pixelsPerRow);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex2i(x-3,y-3);
    glVertex2i(x+3,y-3);
    glVertex2i(x+3,y+3);
    glVertex2i(x-3,y+3);
    glEnd();
  }
}

void checkPlayer(Cell cell, int i, int j) {
  float x, y;
  if(cell.getCellType() == PLAYER){
    x = getPosition(i, pixelsPerColmns);
    y = getPosition(j, pixelsPerRow);
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glVertex2i(x-4,y-4);
    glVertex2i(x+4,y-4);
    glVertex2i(x+4,y+4);
    glVertex2i(x-4,y+4);
    glEnd();
  }
}

float getPosition(int n, float pixels) {
  return ((n * pixels) + (pixels / 2)) ;
}
