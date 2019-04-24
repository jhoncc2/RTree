using namespace std;
#include <vector>

class RTreeLeaf: public RTree {
  RTree *parent = NULL;
  vector<Rectangle> data;

public:

  Rectangle *insert(Rectangle &r){
  }

  vector<Rectangle> find(Rectangle &r){
    vector<Rectangle> res;
    return res;
  }

  bool isRoot() {
    return parent == NULL;
  }

  bool isLeaf() {
    return true;
  }

};
