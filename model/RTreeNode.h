using namespace std;
#include <vector>

class RTreeNode : public RTree {

  vector<RTree> *childs;

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
