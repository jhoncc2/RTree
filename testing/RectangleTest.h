#include <string.h>
using namespace std;

class RectangleTest : public TestSuite {
public:


  /**********write tests*************/

  void testBasic(){
    Point *x = new Point(3,1);
    Point *y = new Point(1,2);

    assertTrue(!x->lessThan(y));
  }

  void testDistance(){
    setContext(__func__);

    Rectangle *a = new Rectangle(1,1,2,2);
    Rectangle *b = new Rectangle(5,5,6,6);

    double d = a->distance(b);
    double dd = b->distance(a);
    // cout << d << " " << dd << endl;
    assertTrue(d == -dd);
  }

  void generateRadomRectangleTest() {
    setContext(__func__);

    // test radom generation
    float f = 1;
    f = Rectangle::randomFloat(3,4);
    for (int i = 0; i < 10000; ++i){
      assertTrue(!(f>4) && !(f<3));
      f = Rectangle::randomFloat(3,4);
    }
    

    // test random  rectangles
    Rectangle *b = Rectangle::createRandom();
    assertTrue(!b->ini->equals(b->end));
    for (int i=0;i < 1000; i ++)  {
      b = Rectangle::createRandom();
      assertTrue(!b->ini->equals(b->end));
      assertTrue(b->ini->x <= conf::SIN_MAX_POINT &&
                  b->ini->y <= conf::SIN_MAX_POINT &&
                  b->end->x <= conf::SIN_MAX_POINT &&
                  b->end->y <= conf::SIN_MAX_POINT);
      assertTrue(b->ini->x >= 0 &&
                  b->ini->y >= 0 &&
                  b->end->x >= 0 &&
                  b->end->y >= 0);
    }

  }

  // test configuration

  void run(){
    this->testBasic();
    this->testDistance();
    this->generateRadomRectangleTest();
  }


};
