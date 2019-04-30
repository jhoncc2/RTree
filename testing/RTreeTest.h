using namespace std;

class RTreeTest : public TestSuite {
public:


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

  void testConfigureEnv(){
    setContext(__func__);

    conf::CONST_m = 10;
    assert(conf::CONST_m == 10);

    conf::CONST_m = 49494;
    assert(conf::CONST_m == 49494);
    
  }

  void testInsertNode() {

    RTree *l = new RTreeLeaf();
    RTree *r = new RTreeLeaf();
    conf::CONST_m = 2;
    conf::CONST_M = 5;
    l->insert(1,1,2,2);
    l->insert(1,2,3,3);

    r->insert(7,7,8,8);
    r->insert(7,8,9,9);

    
    RTree *root = new RTreeNode();
    root->addNode(l);
    root->addNode(r);

    assert(l->size() == 2);
    assert(r->size() == 2);

    r->insert(7,6,8,8);

    Rectangle *b = new Rectangle(7,6,9,9);
    assertTrue(r->boundingBox()->equals(b));

  }

  void testMultipleInsertLeaf(){
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

    // cout << newRoot->size() << endl;
    assertTrue(newRoot->size() == 6);
  }


  // test configuration

  void run(){
    this->testBasic();
    this->testInsertLeaf();
    this->testConfigureEnv();
    this->testMultipleInsertLeaf();
  }


};
