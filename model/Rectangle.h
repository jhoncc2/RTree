using namespace std;


class Point{
public:
  int x,y;

  Point(int x, int y)  {
    this->x = x;
    this->y = y;
  }
};

class Rectangle{
public:
  Point *ini,*end;
  Rectangle(int ix, int iy, int ex, int ey) {
    ini = new Point(ix, iy);
    end = new Point(ex, ey);
  }
};
