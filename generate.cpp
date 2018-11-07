#include <iostream>
#include "Cell.h"
#include "MapGenerator.h"

/*
Students: Pau Balaguer and Didac Florensa
Practice 1. Exercise 1
*/

int main(int argc, char const *argv[]){
  int width = 11;
  int height = 9;

  if(argc < 3){
      std::cout << "./generate HEIGHT WIDTH" << "\n\n";
      std::cout << "MapGenerator rules:" << '\n';
      std::cout << " - Height >= 11. Always an even number" << '\n';
      std::cout << " - Width >= 9." << '\n';
      return 0;
  }
  height = atoi(argv[1]);
  width = atoi(argv[2]);

  MapGenerator mapGenerator(height, width);
  Cell** map = mapGenerator.generateMap();
  mapGenerator.printMap();
}
