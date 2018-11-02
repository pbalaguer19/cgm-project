#include <iostream>
#include "Cell.h"
#include "MapGenerator.h"


int main(int argc, char const *argv[]){
  MapGenerator mapGenerator(5, 10);
  Cell** map = mapGenerator.generateMap();
  std::cout << map[0][0].getY() << "\n";
}
