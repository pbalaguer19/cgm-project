#include <iostream>
#include "ctime"

#define DURATION 200

#define MOVE 1
#define QUIET 2


class PacMan{
private:
  Cell** map;
  MapGenerator* mapGenerator;
  int playerXPos;
  int playerYPos;
  particle player;

  int *ghostsXPos;
  int *ghostsYPos;
  particle *ghosts;

  int COLUMNS;
  int ROWS;
  float WIDTH;
  float HEIGHT;
  float PIXELS_PER_COLUMN;
  float PIXELS_PER_ROW;

  int GHOSTS;

  void definePlayerPosition(){
    ghostsXPos = new int[GHOSTS];
    ghostsYPos = new int[GHOSTS];
    ghosts = new particle[GHOSTS];

    for(playerXPos = 1; playerXPos < COLUMNS; playerXPos++){
      for(playerYPos = 1; playerYPos < ROWS; playerYPos++){
        if(map[playerYPos][playerXPos].getCellType() == FOOD){
          map[playerYPos][playerXPos].setCellType(PLAYER);
          return;
        }
      }
    }
  }

  void defineGhostsPositions(){
    int c = -2;
    int r = -1;

    for(int i = 0; i < GHOSTS; i++){
      ghostsXPos[i] = COLUMNS / 2 + c;
      ghostsYPos[i] = ROWS / 2 + r;
      r += 1;
      if(r >= 2){
        r = -1;
        c++;
      }

      map[ghostsYPos[i]][ghostsXPos[i]].setCellType(GHOST);
      ghosts[i].set_position(getPosition(ghostsXPos[i], PIXELS_PER_COLUMN), getPosition(ghostsYPos[i], PIXELS_PER_ROW));
    }
  }

  float getPosition(int n, float pixels) {
    return ((n * pixels) + (pixels / 2)) ;
  }

  void setPlayerPosition(int newX, int newY){
    if(isWall(newX, newY)) return;

    int oldXPos = playerXPos;
    int oldYPos = playerYPos;

    playerXPos = newX;
    playerYPos = newY;

    player.init_movement(getPosition(playerXPos, PIXELS_PER_COLUMN), getPosition(playerYPos, PIXELS_PER_ROW), DURATION);

    map[newY][newX].setCellType(PLAYER);
    map[oldYPos][oldXPos].setCellType(CORRIDOR);
  }

  bool isWall(int x, int y) {
    Cell cell = map[y][x];
    if(cell.getCellType() == WALL || cell.getCellType() == JAIL || cell.getCellType() == GHOST)
      return true;
    else return false;
  }

public:
  PacMan(int c, int r, float w, float h, int ghostsNumber){
    mapGenerator = new MapGenerator(r, c);
    map = mapGenerator->generateMap();
    mapGenerator->printMap();

    ROWS = mapGenerator->getHeight();
    COLUMNS = mapGenerator->getWidth();
    WIDTH = w;
    HEIGHT = h;

    GHOSTS = ghostsNumber;
    if(ghostsNumber < 1) GHOSTS = 1;
    if(ghostsNumber > 16) GHOSTS = 15;

    PIXELS_PER_COLUMN = WIDTH / COLUMNS;
    PIXELS_PER_ROW = HEIGHT / ROWS;

    definePlayerPosition();
    defineGhostsPositions();

    player.set_position(getPosition(playerXPos, PIXELS_PER_COLUMN), getPosition(playerYPos, PIXELS_PER_ROW));
  }

  void drawCorridor(int i, int j){
    Cell cell = map[j][i];
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
    Cell cell = map[j][i];
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

  void drawGhosts() {
    for(int i = 0; i < GHOSTS; i++){
      ghosts[i].draw(false);
    }
  }

  void drawPlayer() {
    player.draw(true);
  }

  void playerUP(){
    setPlayerPosition(playerXPos, playerYPos+1);
  }

  void playerDOWN(){
    setPlayerPosition(playerXPos, playerYPos-1);
  }

  void playerLEFT(){
    setPlayerPosition(playerXPos-1, playerYPos);
  }

  void playerRIGHT(){
    setPlayerPosition(playerXPos+1, playerYPos);
  }

  void integrate(long t){
    int direct[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};

    player.integrate(t);
    for(int i = 0; i < GHOSTS; i++){
      if(ghosts[i].isReady()){
        int pos;
        int ni, nj;

        do{
          pos = rand() % 4;
          ni = ghostsXPos[i] + direct[pos][0];
          nj = ghostsYPos[i] + direct[pos][1];
        }while(map[nj][ni].getCellType() == WALL);

        CellType cellType = map[ghostsYPos[i]][ghostsXPos[i]].getPreviousCellType();
        map[nj][ni].setCellType(GHOST);
        map[ghostsYPos[i]][ghostsXPos[i]].setCellType(cellType);
        ghostsXPos[i] = ni;
        ghostsYPos[i] = nj;
        ghosts[i].init_movement(getPosition(ni, PIXELS_PER_COLUMN), getPosition(nj, PIXELS_PER_ROW), DURATION);
      }

      ghosts[i].integrate(t);
    }
  }
};
