using namespace std;

class RTreeTest : public TestSuite {
public:


  /**********write tests*************/

  void testLinearSplit(){
    setContext(__func__);

    RTree *root = new RTreeLeaf();
    conf::CONST_m = 2;
    conf::CONST_M = 5;
    
    root->insert(1,1,2,2);
    root->insert(1,1,2,2);
    root->insert(-1,1,3,3);
    root->insert(2,3,5,5);
    root->insert(1,1,3,2);
    Rectangle *b = new Rectangle(-1,1,5,5);
    assertTrue(b->equals(root->boundingBox()));
    assertTrue(root->isRoot());

    RTree *newRoot = root->insert(1,1,3,6);
    b = new Rectangle(-1,1,5,6);
    assertTrue(b->equals(newRoot->boundingBox()));
    assertTrue(newRoot->isRoot());
    assertTrue(!root->isRoot());
  }

  // test configuration

  void run(){
    this->testLinearSplit();
  }


};
