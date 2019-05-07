#include <iostream>
#include <fstream>
using namespace std;

class SerializeTest : public TestSuite {

public:
  // FileAbstract *file; 

  SerializeTest() {
    // file = new File();
  }
  

  void testSerializeLeaf(){
    setContext(__func__);
    FileAbstract *file = new File();
    conf::CONST_M = 5;

    RTree *leaf = new RTreeLeaf();
    leaf->insert(1,1,2,2);
    leaf->insert(1,1,2,2);
    leaf->insert(-1,1,3,3);
    leaf->insert(2,3,5,5);
    leaf->setFilename("tmp/tempfile.data");

    file->store(leaf);
    ifstream f(leaf->getFilename().c_str());
    // if(f.fail()) // hack
    //   assert(true);
    // else
    //   assert(false);
  }


  void testLoadLeaf(){
    setContext(__func__);
    FileAbstract *file = new File();

    RTreeLeaf *leaf = new RTreeLeaf();
    leaf->setFilename("tmp/tempfile.data");

    ifstream f(leaf->getFilename().c_str());

    if(f.fail()) // hack
      assert(true);

    file->loadTreeChildren(leaf, 1);
    // leaf->logTree();

    Rectangle *bbox = new Rectangle(-1,1,5,5);
    assertTrue(bbox->equals(bbox));

    assert((leaf->getSize() == 4));
  }

  void testSerializeNode(){
    setContext(__func__);
    FileAbstract *file = new File();

    RTreeNode  *n = new RTreeNode();
    n->setBoundingBox(new Rectangle(-3,-3,6,7));
    n->setFilename("tmp/node.data");

    RTreeLeaf *leaf1 = new RTreeLeaf();
    leaf1->setFilename("tmp/leaf1.data");
    leaf1->insert(1,1,2,2);
    leaf1->insert(1,1,2,2);

    RTreeLeaf *leaf2 = new RTreeLeaf();
    leaf2->setFilename("tmp/leaf2.data");
    leaf2->insert(-1,1,3,3);
    leaf2->insert(2,3,5,5);

    n->addNodeSilently(leaf1);
    n->addNodeSilently(leaf2);

    // string fname = "tmp/tempfile.data";
    ifstream f(n->getFilename().c_str());

    file->store(n);
    file->store(leaf1);
    file->store(leaf2);

    // if(f.fail()) // hack
    //   assert(true);
    // else
    //   assert(false);
  }

  void testLoadNode(){
    setContext(__func__);
    FileAbstract *file = new File();

    RTreeNode *tree = new RTreeNode();
    tree->setFilename("tmp/node.data");

    ifstream f(tree->getFilename().c_str());

    // if(f.fail()) // hack
    //   assert(true);

    file->loadTreeChildren(tree, 1);
    assert((tree->getChildren()[1]->getSize() == 2)); 
    assert((tree->getSize() == 2));
    assert((tree->height() == 2));

  }

  void randomGererationAndSerialize() {
    setContext(__func__);
    FileAbstract *file = new File();
    conf::CONST_m = 2;
    conf::CONST_M = 5;


    RTree *root = new RTreeLeaf();
    for (int i = 0; i < 26; ++i){
      root = root->insertRectangle(Rectangle::createRandom());
      assertTrue(root->isRoot());
    }
    cout << root->height() << endl;
    assertTrue(root->height() >= 3);
    root->setFilename("tmp/root.dat");
    root->logTree();
    file->storeTree(root, 3);
    // 
    // //
    RTree *storedRoot = file->loadFromFile(root->getFilename(), 10);
    storedRoot->logTree();
    assertTrue(root->equals(storedRoot));
  }

  void run(){
    testSerializeLeaf();
    testLoadLeaf();
    testSerializeNode();
    randomGererationAndSerialize();
  }


};
