#include <iostream>

class MapGenerator{
private:
  int width;
  int height;
  Cell** map;
public:
  MapGenerator(int h, int w);
  Cell** generateMap();
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
  return map;
}
