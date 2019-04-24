using namespace std;

class RTreeTest : public TestSuite {
public:

  RTreeTest() {
  }

  void run(){
    this->testBasic();
  }

  /**********write tests*************/

  void testBasic(){
    new RTreeLeaf();
    new RTreeNode();

    // (RTree.newTree()).isRoot();
  }

};
