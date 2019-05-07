using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

class RTree;

class FileAbstract {

public:

  struct Header{
    bool isLeaf, areChildrenLeaf;
    int size;
  };
  
  virtual void store(RTree *tree){}
  virtual void storeTree(RTree *tree, int deepness){}
  virtual RTree* loadFromFile(string filename, int deepness){}
  virtual void loadTreeChildren(RTree *tree, int deepness){}
  virtual Header readHeader(string line){}

  
};
