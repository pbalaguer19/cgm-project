enum CellType{WALL, CORRIDOR};

class Cell{
private:
  int x;
  int y;
  CellType type;
public:
  Cell();
  Cell(int x_pos, int y_pos, CellType cellType);
  CellType getCellType();
  void setCellType(CellType type);
  void setX(int x);
  int getX();
  void setY(int y);
  int getY();
};

Cell::Cell(){};
Cell::Cell(int x_pos, int y_pos, CellType cellType){
  x = x_pos;
  y = y_pos;
  type = cellType;
}

CellType Cell::getCellType(){
  return type;
}

void Cell::setCellType(CellType cellType){
  type = cellType;
}

void Cell::setX(int x_pos){
  x = x_pos;
}

int Cell::getX(){
  return x;
}

void Cell::setY(int y_pos){
  y = y_pos;
}
int Cell::getY(){
  return y;
}
