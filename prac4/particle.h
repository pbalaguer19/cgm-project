#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

//-----------------------------------------------

class particle {
  float x,y;   //-- Current position
  float vx,vy; //-- Velocity vector
  int state;

  long time_remaining;

public:

  particle();
  void set_position(int x,int y);
  void init_movement(int destination_x,int destination_y,int duration);
  void integrate(long t);
  void draw(int radius, float r, float g, float b, float bx, float bz);
  bool isReady();
};


//-----------------------------------------------

particle::particle()
{
  state=QUIET;
}

//-----------------------------------------------

void particle::set_position(int x,int y)
{
  this->x = x;
  this->y = y;
}

//-----------------------------------------------

void particle::init_movement(int destination_x,int destination_y,int duration)
{
  vx = (destination_x - x)/duration;
  vy = (destination_y - y)/duration;

  state=MOVE;
  time_remaining=duration;
}

//-----------------------------------------------

void particle::integrate(long t)
{
  if(state==MOVE && t<time_remaining)
    {
      x = x + vx*t;
      y = y + vy*t;
      time_remaining-=t;
    }
  else if(state==MOVE && t>=time_remaining)
    {
      x = x + vx*time_remaining;
      y = y + vy*time_remaining;
      state=QUIET;
    }
}

//-----------------------------------------------

void particle::draw(int radius, float r, float g, float b, float baseX, float baseZ){
  glPushMatrix();
  glColor3f(r, g, b);
  GLUquadric *quad;
  quad = gluNewQuadric();
  glTranslatef(baseX + x, radius, baseZ - y);
  gluSphere(quad,radius,100,20);
  glEnd();
  glPopMatrix();
}

bool particle::isReady(){
  return state == QUIET;
}
