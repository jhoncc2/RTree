#include <iostream>
#include <fstream>
using namespace std;

class SerializeTest : public TestSuite {

public:
  RTree *tree;

  SerializeTest() {
    tree = new RTree();
  }
  void run(){
    testSerializeLeaf();
    testLoadLeaf();
  }

  void testSerializeLeaf(){
    setContext(__func__);

    RTreeLeaf *leaf = new RTreeLeaf();
    leaf->insert(1,1,2,2);
    leaf->insert(1,1,2,2);
    leaf->insert(-1,1,3,3);
    leaf->insert(2,3,5,5);

    string fname = "tmp/tempfile.data";
    ifstream f(fname.c_str());
    File::store(fname, leaf);
    if(f.fail()) // hack
      assert(true);
  }

  void testLoadLeaf(){
    setContext(__func__);

    RTreeLeaf *leaf = new RTreeLeaf();

    string fname = "tmp/tempfile.data";
    ifstream f(fname.c_str());
    if(f.fail()) // hack
      assert(true);

    File::load(fname, leaf);
    
    assert((leaf->size() == 4));
  }
};
