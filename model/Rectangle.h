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
    this->x = std::min(this->x, p->x);
    this->y = std::min(this->y, p->y);
  }

  void keepMax(Point *p) {
    this->x = std::max(x, p->x);
    this->y = std::max(y, p->y);
  }

  bool greatherThan(Point *point) {
    float c = (x - point->x) + (y - point->y);
    return c > 0;
  }

  bool lessThan(Point *point) {
    float c = (x - point->x) + (y - point->y);
    return c < 0;
  }

  double distance(Point *other) {
    return sqrt(pow(2, this->x - other->x) + 
                pow(2, this->y - other->y));
  }

  bool equals(Point *r) {
    return isEqual(x, r->x) &&
            isEqual(y, r->y);
  }

  inline bool isEqual(double x, double y) {
    const double epsilon = 0.0001;/* some small number such as 1e-5 */
    return std::abs(x - y) <= epsilon * std::abs(x);
    // see Knuth section 4.2.2 pages 217-218
  }
};

class Rectangle{
public:
  Point *ini,*end;

  Rectangle(Rectangle *r) {
    ini = new Point(r->ini);
    end = new Point(r->end);
  }

  Rectangle(Point *i, Point *e) {
    ini = new Point(i);
    end = new Point(e);
  }

  Rectangle(float ix, float iy, float ex, float ey) {
    ini = new Point(ix, iy);
    end = new Point(ex, ey);
  }

  bool equals(Rectangle *r) {
    return ini->equals(r->ini) &&
        end->equals(r->end);
  }

  void rebound(Rectangle *r){
    ini->keepMin(r->ini);
    end->keepMax(r->end);
  }

  float area(){
    return (ini->x - end->x) * (ini->y - end->y);
  }


  double unusefulArea(Rectangle *other) {
    Rectangle *tmp= new Rectangle(this);
    tmp->rebound(other); 
    return tmp->area() - this->area() - other->area();
  }

  bool intersect(Rectangle *other) {
    return ((ini->x > other->ini->x < end->x) || 
              (ini->x > other->end->x < end->x)) &&
            ((ini->y > other->ini->y < end->y) || 
              (ini->y > other->end->y < end->y));
  }

  bool intersect2(Rectangle *other) {
    return containsPoint(other->ini->x, other->ini->y) 
            || containsPoint(other->ini->x, other->end->y) 
            || containsPoint(other->end->x, other->end->y) 
            || containsPoint(other->end->x, other->ini->y);
  }

  bool containsPoint(int x, int y) {
    return ((x > ini->x) && (y >  ini->y))
          && ((x < end->x) && (y <  end->y));
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

  static Rectangle *createRandom(){
    float inix,iniy, endx,endy;
    inix = randomFloat(0,conf::SIN_MAX_POINT - conf::SIN_MAX_DIST);
    iniy = randomFloat(0,conf::SIN_MAX_POINT - conf::SIN_MAX_DIST);

    endx = randomFloat(inix+1,inix+1 + conf::SIN_MAX_DIST);
    endy = randomFloat(iniy+1,iniy+1 + conf::SIN_MAX_DIST);

    return new Rectangle(inix, iniy, endx, endy);
  }

  static float randomFloat(float lower, float higher) {
    return lower + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(higher-lower)));
  }
 
  static Rectangle *createInstance(string line) {
    std::istringstream iss(line);
    std::string segment;

    
    std::getline(iss, segment, ',');
    float a = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float b = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float c = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float d = std::stof(segment, nullptr);
    // std::cout << touple << endl;
    // std::cout << i << "-" << n << "-" << r << endl;

    return new Rectangle(a,b,c,d);
  }
};
