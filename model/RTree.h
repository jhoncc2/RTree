using namespace std;
#include <vector>

#include "RTreeConf.h"

class RTree {
  RTree *parent = NULL;
  RTree *childs[];
public:
  Rectangle *insert(Rectangle &r){
    return &r;
  }

  vector<Rectangle> find(Rectangle &r){
    vector<Rectangle> res;
    return res;
  }
  bool isRoot() {

    return parent == NULL;
  }

};
