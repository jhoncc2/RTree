using namespace std;

class RTreeTest : public TestSuite {
public:

  void run(){
    this->testBasic();
    this->testInsertLeaf();
  }

  /**********write tests*************/

  void testBasic(){
    setContext(__func__);
    RTreeLeaf *leaf = new RTreeLeaf();

    assertTrue(leaf->isRoot());
    assertTrue(leaf->isLeaf());
  }

  void testInsertLeaf(){
    setContext(__func__);

    RTreeLeaf *leaf = new RTreeLeaf();
    leaf->insert(1,1,2,2);
    Rectangle *bbox = new Rectangle(1,1,2,2);

    assertTrue(bbox->equals(bbox));
    assertTrue(leaf->boundingBox() != 0);
    assertTrue(bbox->equals(leaf->boundingBox()));

// multiple insert, increase boudning box
    leaf->insert(1,1,2,2);
    leaf->insert(-1,1,3,3);
    leaf->insert(2,3,5,5);
    Rectangle *b = new Rectangle(-1,1,5,5);
    assertTrue(b->equals(leaf->boundingBox()));
  }

  void testMultipleInsertLeaf(){
    setContext(__func__);

    RTreeLeaf *leaf = new RTreeLeaf();
    leaf->insert(1,1,2,2);
    leaf->insert(1,1,2,2);
    leaf->insert(1,1,2,2);
    leaf->insert(1,1,2,2);

    assert(leaf);
  }

};
