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

  // test configuration

  void run(){
    this->testBasic();
    this->testDistance();
    
  }


};
