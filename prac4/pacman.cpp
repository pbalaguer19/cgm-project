
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

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PI 3.1416
#define MIN_HEIGHT 9
#define MIN_WIDTH 11

/*
Students: Pau Balaguer and Didac Florensa
Practice 3
*/

/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 0;
int anglebeta = 0;

float WIDTH = 500.0;
float HEIGHT = 500.0;
int COLUMNS;
int ROWS;

PacMan* pacMan;
long last_t=0;

//-----------------------------------------------

void displayMap();
void windowReshapeFunc( GLint newWidth, GLint newHeight );
void specialKeyboard(int key, int x, int y);
void keyboard(unsigned char c,int x,int y);
void idle();
void PositionObserver(float alpha,float beta,int radi);

//-----------------------------------------------

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[]){

  if(argc < 4){
      std::cout << "./generate HEIGHT WIDTH GHOSTS" << "\n\n";
      std::cout << "MapGenerator rules:" << '\n';
      std::cout << " - Height >= 11. Always an even number" << '\n';
      std::cout << " - Width >= 9." << '\n';
      std::cout << " - 0 < Ghosts < 16." << '\n';
      return 0;
  }

  int h = atoi(argv[1]);
  int w = atoi(argv[2]);
  int ghostsNumber = atoi(argv[3]);

  if(h < MIN_HEIGHT) h = MIN_HEIGHT;
  if(w < MIN_WIDTH) w = MIN_WIDTH;
  if(w % 2 == 0) w += 1; //Must be even

  ROWS = h;
  COLUMNS = w;

  anglealpha=90;
  anglebeta=30;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("PACMAN MAP");
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  pacMan = new PacMan(COLUMNS, ROWS, WIDTH, HEIGHT, ghostsNumber);

  glutDisplayFunc(displayMap);
  glutReshapeFunc(windowReshapeFunc);
  glutSpecialFunc(specialKeyboard);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  glutMainLoop();
  return 0;
}

//------------------------------------------------------------

//------------------------------------------------------------
void displayMap(){
  GLint position[4];
  GLfloat color[4];
  GLfloat material[4];
  int i,j;
  Cell cell;

  glClearColor(1.0,1.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  PositionObserver(anglealpha,anglebeta,450);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH*0.6,WIDTH*0.6,-HEIGHT*0.6,HEIGHT*0.6,10,2000);

  glMatrixMode(GL_MODELVIEW);

  glPolygonMode(GL_FRONT,GL_FILL);
  glPolygonMode(GL_BACK,GL_FILL);

  //-- Ambient light

  position[0]=0; position[1]=1; position[2]=0; position[3]=0;
  glLightiv(GL_LIGHT0,GL_POSITION,position);

  color[0]=0; color[1]=0; color[2]=0; color[3]=1;
  glLightfv(GL_LIGHT0,GL_AMBIENT,color);
  glEnable(GL_LIGHT0);

  material[0]=1.0; material[1]=0.0; material[2]=0.0; material[3]=1.0;
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

  for(i=0; i<COLUMNS; i++) {
    for(j=0; j<ROWS; j++){
      pacMan->drawCorridor(i, j);
      pacMan->drawFood(i, j);
    }
  }

  pacMan->drawGhosts();
  pacMan->drawPlayer();

  // Floor
  material[0]=0.5; material[1]=0.5; material[2]=0.5; material[3]=1.0;
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

  glBegin(GL_QUADS);
  glNormal3f(0,0.2,0);
  glVertex3i(WIDTH/2,0,HEIGHT/2);
  glVertex3i(-WIDTH/2,0,HEIGHT/2);
  glVertex3i(-WIDTH/2,0,-HEIGHT/2);
  glVertex3i(WIDTH/2,0,-HEIGHT/2);
  glEnd();

  glutSwapBuffers();
}

void windowReshapeFunc( GLint newWidth, GLint newHeight ) {
  glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void specialKeyboard(int key, int x, int y){
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

void keyboard(unsigned char c,int x,int y){
  int i,j;

  if (c=='i' && anglebeta<=(90-4))
    anglebeta=(anglebeta+3);
  else if (c=='k' && anglebeta>=(-90+4))
    anglebeta=anglebeta-3;
  else if (c=='j')
    anglealpha=(anglealpha+3)%360;
  else if (c=='l')
    anglealpha=(anglealpha-3+360)%360;

  glutPostRedisplay();
}

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

void PositionObserver(float alpha,float beta,int radi)
{
  float x,y,z;
  float upx,upy,upz;
  float modul;

  x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
  y = (float)radi*sin(beta*2*PI/360.0);
  z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

  if (beta>0)
    {
      upx=-x;
      upz=-z;
      upy=(x*x+z*z)/y;
    }
  else if(beta==0)
    {
      upx=0;
      upy=1;
      upz=0;
    }
  else
    {
      upx=x;
      upz=z;
      upy=-(x*x+z*z)/y;
    }


  modul=sqrt(upx*upx+upy*upy+upz*upz);

  upx=upx/modul;
  upy=upy/modul;
  upz=upz/modul;

  gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}
