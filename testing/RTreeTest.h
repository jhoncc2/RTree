using namespace std;

class RTreeTest {
public:
  RTree *target;

  RTreeTest() {
    target = new RTree();
  }

  run(){
    this->testBasic();
  }

  testBasic(){
    Rectangle *r = new Rectangle(1,1,3,3);
    target->insert(*r);
  }

};
