#include <iostream>
#include "ctime"

class MapGenerator{
private:
  int width;
  int height;
  Cell** map;

  void mapGeneratorDFS(Cell** map, int x, int y);
  bool cornersVisited(int i, int j);
  void shuffle(int a[], int n);
  void swap(int &a, int &b);
public:
  MapGenerator(int h, int w);
  Cell** generateMap();
  void printMap();

  int getWidth();
  int getHeight();
};

MapGenerator::MapGenerator(int h, int w){
  height = h;
  width = w;

  map = new Cell*[h];

  for (int x = 0; x < h; ++x) {
    for (int y = 0; y < w; ++y) {
      if(y == 0) map[x] = new Cell[w];
      map[x][y] = Cell(x, y, WALL);
    }
  }
}

Cell** MapGenerator::generateMap(){
  srand(time(0));
  mapGeneratorDFS(map, 0, 0);
  return map;
}

void MapGenerator::printMap(){
  for (int x = 0; x < height; ++x) {
    for (int y = 0; y < width; ++y) {
      if(map[x][y].getCellType() == WALL) std::cout << "#";
      else std::cout << "·";
    }
    std::cout << "\n";
  }
}

int MapGenerator::getWidth(){
  return width;
}

int MapGenerator::getHeight(){
  return height;
}

void MapGenerator::mapGeneratorDFS(Cell** map, int x, int y){
  int direct[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
  int visitOrder[] = {0,1,2,3};

  // If one of this three cases are true, then we don't change the Cell state.
  if(x < 0 || y < 0 || x >= height || y >= width) return ;
  if(map[x][y].getCellType() == CORRIDOR) return ;
  if(cornersVisited(x, y)) return ;

  // If the three previous conditions are false, then the cell state will be CORRIDOR
  map[x][y].setCellType(CORRIDOR);

  // Shuffle the visitOrder Array
  shuffle(visitOrder, 4);

  for (int k = 0; k < 4; ++k){
    int ni = x + direct[visitOrder[k]][0];
    int nj = y + direct[visitOrder[k]][1];
    mapGeneratorDFS(map, ni, nj);
  }
}

// This function is the responsible of avoiding a 2x2 matrix of corridors cells.
bool MapGenerator::cornersVisited(int i, int j){
  /*
  Array with all neighbors of a given position. This is sorted following:
       ___________________________
      | {1,-1}  | {1,0}  | {1,1}  |
      | {0,-1}  | {i,j}  | {0,1}  |
      | {-1,-1} | {-1,0} | {-1,1} |
      |___________________________|
  */
  int neightbors[][2] = {{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};

  // Looping over the 4 corner neightbors.
  for (int k = 1; k < 8; k+=2){
      // {ni, nj} -> corner
      int ni = i + neightbors[k][0];
      int nj = j + neightbors[k][1];
      // {niprev, njprev} -> previous neighbor.
      int niprev = i + neightbors[((k-1) % 8)][0];
      int njprev = j + neightbors[((k-1) % 8)][1];
      // {ninext, njnext} -> next neighbor.
      int ninext = i + neightbors[((k+1) % 8)][0];
      int njnext = j + neightbors[((k+1) % 8)][1];

      //out of boundary tests
      if(ni < 0 || nj < 0 || ni >= height || nj >= width) continue;
      if(niprev < 0 || njprev < 0 || niprev >= height || njprev >= width) continue;
      if(ninext < 0 || njnext < 0 || ninext >= height || njnext >= width) continue;

      //If the corner and its next and previous neighbors are corridors, then return true
      if(map[ni][nj].getCellType() == CORRIDOR &&
         map[niprev][njprev].getCellType() == CORRIDOR &&
         map[ninext][njnext].getCellType() == CORRIDOR) return true;
  }
  return false;
}

void MapGenerator::shuffle(int a[], int n){
    for (int i = 0; i < n; ++i)
    {
        swap(a[i], a[rand() % n]);
    }
}

void MapGenerator::swap(int & a, int &b){
    int c = a;
    a = b;
    b = c;
}
