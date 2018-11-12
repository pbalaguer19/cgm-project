#include <iostream>
#include "ctime"

class PacMan{
private:
  Cell** map;
  MapGenerator* mapGenerator;
  int playerXPos;
  int playerYPos;

  int COLUMNS;
  int ROWS;
  float WIDTH;
  float HEIGHT;
  float PIXELS_PER_COLUMN;
  float PIXELS_PER_ROW;

  void definePlayerPosition(){
    for(playerXPos = 1; playerXPos < ROWS; playerXPos++){
      for(playerYPos = 1; playerYPos < COLUMNS; playerYPos++){
        if(map[playerXPos][playerYPos].getCellType() == FOOD){
          map[playerXPos][playerYPos].setCellType(PLAYER);
          return;
        }
      }
    }
  }

  float getPosition(int n, float pixels) {
    return ((n * pixels) + (pixels / 2)) ;
  }

  void setPlayerPosition(int newX, int newY){
    int oldX = playerXPos;
    int oldY = playerYPos;
    playerXPos = newX;
    playerYPos = newY;

    map[oldX][oldY].setCellType(CORRIDOR);
    map[playerXPos][playerYPos].setCellType(PLAYER);
  }

  bool checkWall(int x, int y) {
    Cell cell = map[x][y];
    if(cell.getCellType() == WALL)
      return true;
    else return false;
  }

public:
  PacMan(int c, int r, float w, float h){
    mapGenerator = new MapGenerator(c, r);
    map = mapGenerator->generateMap();
    mapGenerator->printMap();

    ROWS = mapGenerator->getHeight();
    COLUMNS = mapGenerator->getWidth();
    WIDTH = w;
    HEIGHT = h;

    PIXELS_PER_COLUMN = WIDTH / COLUMNS;
    PIXELS_PER_ROW = HEIGHT / ROWS;

    definePlayerPosition();
  }

  void drawCorridor(int i, int j){
    Cell cell = map[i][j];
    if(cell.getCellType() != WALL) {
      glColor3f(0.8,0.8,0.8);
      glBegin(GL_QUADS);
      glVertex2i(i*PIXELS_PER_COLUMN,j*PIXELS_PER_ROW);
      glVertex2i((i+1)*PIXELS_PER_COLUMN,j*PIXELS_PER_ROW);
      glVertex2i((i+1)*PIXELS_PER_COLUMN,(j+1)*PIXELS_PER_ROW);
      glVertex2i(i*PIXELS_PER_COLUMN,(j+1)*PIXELS_PER_ROW);
      glEnd();
    }
  }

  void drawFood(int i, int j) {
    float x, y;
    Cell cell = map[i][j];
    if(cell.getCellType() == FOOD){
      x = getPosition(i, PIXELS_PER_COLUMN);
      y = getPosition(j, PIXELS_PER_ROW);
      glColor3f(1,1,1);
      glBegin(GL_QUADS);
      glVertex2i(x-3,y-3);
      glVertex2i(x+3,y-3);
      glVertex2i(x+3,y+3);
      glVertex2i(x-3,y+3);
      glEnd();
    }
  }

  void checkPlayer(int i, int j) {
    float x, y;
    Cell cell = map[i][j];
    if(cell.getCellType() == PLAYER){
      x = getPosition(i, PIXELS_PER_COLUMN);
      y = getPosition(j, PIXELS_PER_ROW);
      glColor3f(1,1,0);
      glBegin(GL_QUADS);
      glVertex2i(x-4,y-4);
      glVertex2i(x+4,y-4);
      glVertex2i(x+4,y+4);
      glVertex2i(x-4,y+4);
      glEnd();
    }
  }

  void playerUP(){
    if(!checkWall(playerXPos, playerYPos+1))
      setPlayerPosition(playerXPos, playerYPos++);
  }

  void playerDOWN(){
    if(!checkWall(playerXPos, playerYPos-1))
      setPlayerPosition(playerXPos, playerYPos--);
  }

  void playerLEFT(){
    if(!checkWall(playerXPos-1, playerYPos))
      setPlayerPosition(playerXPos--, playerYPos);
  }

  void playerRIGHT(){
    if(!checkWall(playerXPos+1, playerYPos))
      setPlayerPosition(playerXPos++, playerYPos);
  }
};
