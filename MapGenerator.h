#include <iostream>

class MapGenerator{
private:
  int width;
  int height;
  Cell** map;

  Cell** mapGeneratorDFS(int x, int y);
  bool cornersVisited(int i, int j);
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
  return mapGeneratorDFS(0, 0);
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

Cell** MapGenerator::mapGeneratorDFS(int x, int y){
  int direct[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
  int visitOrder[] = {0,1,2,3};

  if(x < 0 || y < 0 || x >= height || y >= width) return ;
  if(map[x][y].getCellType() == CORRIDOR) return;
  if(cornersVisited(x, y)) return;
}

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
      if(ni < 0 || nj < 0 || ni >= map.size() || nj >= map[0].size()) continue;
      if(niprev < 0 || njprev < 0 || niprev >= map.size() || njprev >= map[0].size()) continue;
      if(ninext < 0 || njnext < 0 || ninext >= map.size() || njnext >= map[0].size()) continue;

      //If the corner and its next and previous neighbors are corridors, then return true
      if(map[ni][nj].getCellType() == CORRIDOR &&
         map[niprev][njprev].getCellType() == CORRIDOR &&
         map[ninext][njnext].getCellType() == CORRIDOR) return true;
  }
  return false;
}
