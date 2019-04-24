using namespace std;

class RTreeTest : public TestSuite {
public:

  void run(){
    this->testBasic();
  }

  /**********write tests*************/

  void testBasic(){
    RTreeLeaf *leaf = new RTreeLeaf();
    new RTreeNode();

    assertTrue(leaf->isRoot());
    assertTrue(leaf->isLeaf());
    // (RTree.newTree()).isRoot();
  }

};
