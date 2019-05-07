using namespace std;

class RTreeTest : public TestSuite {
public:


  /**********write tests*************/

  void testBasic(){
    setContext(__func__);

    RTreeLeaf *leaf = new RTreeLeaf();
    assertTrue(leaf->isRoot());
    assertTrue(leaf->isLeaf());

    // test minmax algorithm
    vector<float> list = {1,2,3,4};
    vector<float> list2 = {1,2,3,3};
    RTree::triplete t = leaf->minMax(list,list2, 0, 3, 10);
    assertTrue(t.i == 0);
    assertTrue(t.j == 3);
    assertTrue(t.dist == 2);
    
    
    vector<float> l1 = {72, 22, 3, 2, 4};
    vector<float> l2 = {1, 3, 94, 3,4};

    t = leaf->minMax(l1, l2, 0, l1.size()-1, 10);
    cout << t.i << " - " << t.j << " - " << t.dist << " - " << (19/2) << endl;
    assertTrue(t.i == 3);
    assertTrue(t.j == 2);
    assertTrue(t.dist == 92);

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
    conf::CONST_LEAF_M = 5;
    
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
    conf::CONST_LEAF_M = 2;
    
    RTree *root = new RTreeLeaf();

    root = root->insert(1,1,2,2);
    root = root->insert(4,3,3,4);
    root = root->insert(3,2,4,4);
    root->logTree(); 
    root = root->insert(2,3,5,5);
    root->logTree();// first overflow 
    root = root->insert(-1,1,3,3);
    root->logTree();// second overflow
    
    assertTrue(root->isRoot());
    assertTrue(root->isNode());
    assertTrue(root->height() == 3 && root->getSize() == 2);
    assertTrue(root->treeSize() == 5);
    // assertTrue(root->boundingBox()->equals(new Rectangle(-1,1,5,5)));
  }

  void testOverflowNodeQuadratic() {
    setContext(__func__);
    
    conf::CONST_m = 1;
    conf::CONST_M = 2;
    conf::CONST_LEAF_M = 2;
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_QUADRATIC_SPLIT;
    
    RTree *root = new RTreeLeaf();

    root = root->insert(1,1,2,2);
    root = root->insert(4,3,3,4);
    root = root->insert(3,2,4,4);
    root->logTree(); 
    root = root->insert(2,3,5,5);
    root->logTree();// first overflow 
    root = root->insert(-1,1,3,3);
    root->logTree();// second overflow
    
    assertTrue(root->isRoot());
    assertTrue(root->isNode());
    assertTrue(root->height() == 3 && root->getSize() == 2);
    assertTrue(root->treeSize() == 5);
    assertTrue(root->boundingBox()->equals(new Rectangle(-1,1,5,5)));
  }

  void testOverflowNodeSecondMemory() {
    setContext(__func__);
    conf::CONST_SECOND_MEMORY = true;
    conf::fileManager = new File();
    conf::LEVELS_IN_MEMORY = 1;

    conf::dataDirectory = "tmp/";
    conf::CONST_m = 1;
    conf::CONST_M = 5;
    conf::CONST_LEAF_M = 5;
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_QUADRATIC_SPLIT;
    
    RTree *root = new RTreeLeaf();

    for (int i = 9; i < 10; ++i) {
      cout << "********CONST_QUADRATIC_SPLIT********" << endl;
      cout << "2^" << i  << ":" << endl;
      int end = pow(2,i);

      for (int j = 0; j < end ; ++j) {
        
        root = root->insertRectangle(Rectangle::createRandom());
        root->logTree();
        assertTrue(root->heightInMemory() < 3);
      }
    }
    
    assertTrue(root->isRoot());
    assertTrue(!root->isLeaf());
  }

  // test configuration
  void run(){
    this->testBasic();
    this->testInsertLeaf();
    this->testConfigureEnv();
    this->testOverflowLeaf();
    this->testOverflowNode();
    this->testOverflowNodeQuadratic();
    this->testOverflowNodeSecondMemory();
  }

};
