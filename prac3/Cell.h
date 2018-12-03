enum CellType{WALL, CORRIDOR, FOOD, JAIL, GHOST, PLAYER};
enum CellDirection{UP, DOWN, RIGHT, LEFT};

class Cell{
private:
  int x;
  int y;
  CellType type;
  CellType previousType;
  CellDirection cellDirection;
public:
  Cell();
  Cell(int x_pos, int y_pos, CellType cellType);
  CellType getCellType();
  CellType getPreviousCellType();
  void setCellType(CellType type);
  void setX(int x);
  int getX();
  void setY(int y);
  int getY();
  CellDirection getCellDirection();
  void setCellDirection(CellDirection c);
};

Cell::Cell(){};
Cell::Cell(int x_pos, int y_pos, CellType cellType){
  x = x_pos;
  y = y_pos;
  type = cellType;
  previousType = type;
  cellDirection = UP;
}

CellType Cell::getCellType(){
  return type;
}

CellType Cell::getPreviousCellType(){
  return previousType;
}

void Cell::setCellType(CellType cellType){
  if(cellType != type) previousType = type;
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
CellDirection Cell::getCellDirection(){
  return cellDirection;
}
void Cell::setCellDirection(CellDirection c){
  cellDirection = c;
}
