using namespace std;
#include <sstream>

class Point{
public:
  int x,y;

  Point(int x, int y)  {
    this->x = x;
    this->y = y;
  }

  Point(Point *p) {
    this->x = p->x;
    this->y = p->y;
  }

  void keepMin(Point *p) {
    this->x = std::min(x, p->x);
    this->y = std::min(y, p->y);
  }

  void keepMax(Point *p) {
    this->x = std::max(x, p->x);
    this->y = std::max(y, p->y);
  }
};

class Rectangle{
public:
  Point *ini,*end;

  Rectangle(Rectangle *r) {
    ini = new Point(r->ini);
    end = new Point(r->end);
  }

  Rectangle(int ix, int iy, int ex, int ey) {
    ini = new Point(ix, iy);
    end = new Point(ex, ey);
  }

  bool equals(Rectangle *r){
    return (ini->x == r->ini->x) &&
      (ini->y == r->ini->y) &&
      (end->x == r->end->x) &&
      (end->y == r->end->y);
  }

  void rebound(Rectangle *r){
    ini->keepMin(r->ini);
    end->keepMax(r->end);
  }

  string serialize(){
    std::ostringstream output;
    output << ini->x
        << ',' << ini->y
        << ',' << end->x
        << ',' << end->y;

    return output.str();
  }

  static Rectangle *createInstance(string line) {
    std::istringstream iss(line);
    std::string segment;

    
    std::getline(iss, segment, ',');
    int a = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int b = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int c = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int d = std::stoi(segment, nullptr);
    // std::cout << touple << endl;
    // std::cout << i << "-" << n << "-" << r << endl;

    return new Rectangle(a,b,c,d);
  }
};
