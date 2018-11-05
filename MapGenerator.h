#include <iostream>

class MapGenerator{
private:
  int width;
  int height;
  Cell** map;
public:
  MapGenerator(int h, int w);
  Cell** generateMap();
  void printMap();
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
  for (int x = 0; x < height; ++x) {
    for (int y = 0; y < width; ++y) {
      if(y%2 == 0) map[x][y].setCellType(CORRIDOR);
    }
  }
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
