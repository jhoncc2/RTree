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
    conf::CONST_m = 4;
    conf::CONST_M = 10;

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
    // assertTrue(b->equals(leaf->boundingBox()));
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

    assert(l->treeSize() == 2);
    assert(r->treeSize() == 2);

    r->insert(7,6,8,8);

    Rectangle *b = new Rectangle(7,6,9,9);
    assertTrue(r->boundingBox()->equals(b));

  }

  void testOverflowLeaf(){
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

    newRoot->logTree();

    assertTrue(newRoot->getSize() == 2);
    assertTrue(newRoot->height() == 2); 
    assertTrue(!newRoot->isFull());
    assertTrue(newRoot->treeSize() == 6);

  }

  void testOverflowNode() {
    setContext(__func__);
    
    conf::CONST_m = 1;
    conf::CONST_M = 2;
    
    RTree *root = new RTreeLeaf();

    root = root->insert(1,1,2,2);
    root = root->insert(3,2,4,4);
    root->logTree(); 
    root = root->insert(2,3,5,5);
    root->logTree();// first overflow 
    root = root->insert(-1,1,3,3);
    root->logTree();// second overflow
    
    assertTrue(root->isRoot());
    assertTrue(root->isNode());
    assertTrue(root->height() == 3 && root->getSize() == 2);
    assertTrue(root->treeSize() == 4);
    assertTrue(root->boundingBox()->equals(new Rectangle(-1,1,5,5)));
  }


  // test configuration

  void run(){
    this->testBasic();
    this->testInsertLeaf();
    this->testConfigureEnv();
    this->testOverflowLeaf();
    this->testOverflowNode();
  }

};
