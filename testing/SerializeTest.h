#include <iostream>
#include <fstream>
using namespace std;

class SerializeTest : public TestSuite {

public:
  RTree *tree;

  SerializeTest() {
    tree = new RTree();
  }
  

  void testSerializeLeaf(){
    setContext(__func__);
    conf::CONST_M = 5;

    RTree *leaf = new RTreeLeaf();
    leaf->insert(1,1,2,2);
    leaf->insert(1,1,2,2);
    leaf->insert(-1,1,3,3);
    leaf->insert(2,3,5,5);

    string fname = "tmp/tempfile.data";
    ifstream f(fname.c_str());
    File::store(fname, leaf);
    // if(f.fail()) // hack
    //   assert(true);
    // else
    //   assert(false);
  }


  void testLoadLeaf(){
    setContext(__func__);

    RTreeLeaf *leaf = new RTreeLeaf();

    string fname = "tmp/tempfile.data";
    ifstream f(fname.c_str());

    if(f.fail()) // hack
      assert(true);

    File::load(fname, leaf);
    assert((leaf->getSize() == 4));
  }

  void testSerializeNode(){
    setContext(__func__);

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

    File::store(n->getFilename(), n);
    File::store(leaf1->getFilename(), leaf1);
    File::store(leaf2->getFilename(), leaf2);

    // if(f.fail()) // hack
    //   assert(true);
    // else
    //   assert(false);
  }

  void testLoadNode(){
    setContext(__func__);

    RTreeNode *tree = new RTreeNode();
    tree->setFilename("tmp/node.data");

    ifstream f(tree->getFilename().c_str());

    // if(f.fail()) // hack
    //   assert(true);

    File::load(tree->getFilename(), tree);
    assert((tree->getChildren()[1]->getSize() == 2));
    assert((tree->getSize() == 2));
  }

  void randomGererationAndSerialize() {
    setContext(__func__);
    conf::CONST_m = 2;
    conf::CONST_M = 5;


    RTree *root = new RTreeNode();
    for (int i = 0; i < 11; ++i){
      root = root->insertRectangle(Rectangle::createRandom());
      assertTrue(root->isRoot());
    }
    // assertTrue(root->height() >= 3);
  }

  void run(){
    testSerializeLeaf();
    testLoadLeaf();
    testSerializeNode();
    randomGererationAndSerialize();
  }


};
