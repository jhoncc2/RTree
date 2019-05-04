using namespace std;
#include <sstream>
#include <cmath>

class Point{
public:
  float x,y;

  Point(float x, float y)  {
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

  bool greatherThan(Point *point) {
    int c = (x - point->x) + (y - point->y);
    return c > 0;
  }

  bool lessThan(Point *point) {
    int c = (x - point->x) + (y - point->y);
    return c < 0;
  }

  double distance(Point *other) {
    return sqrt(pow(2, this->x - other->x) + 
                pow(2, this->y - other->y));
  }
};

class Rectangle{
public:
  Point *ini,*end;

  Rectangle(Rectangle *r) {
    ini = new Point(r->ini);
    end = new Point(r->end);
  }

  Rectangle(float ix, float iy, float ex, float ey) {
    ini = new Point(ix, iy);
    end = new Point(ex, ey);
  }

  bool equals(Rectangle *r) {
    return (ini->x == r->ini->x) &&
      (ini->y == r->ini->y) &&
      (end->x == r->end->x) &&
      (end->y == r->end->y);
  }

  void rebound(Rectangle *r){
    ini->keepMin(r->ini);
    end->keepMax(r->end);
  }

  int area(){
    return (ini->x - end->x) * (ini->y - end->y);
  }

  double distance(Rectangle *other) {
    if(other->ini->lessThan(this->ini)) {
      return -abs(other->end->distance(this->ini));
    } else {
      return abs(this->end->distance(other->ini));
    }
  }

  string serialize(){
    std::ostringstream output;
    output << this->ini->x
        << ',' << this->ini->y
        << ',' << this->end->x
        << ',' << this->end->y;

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
