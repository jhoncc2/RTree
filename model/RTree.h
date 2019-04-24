using namespace std;
#include <vector>


class RTree {
protected:
  Rectangle *self = NULL;
  RTree *parent = NULL;

public:

  virtual Rectangle *insert(Rectangle &r) {
  }

  virtual vector<Rectangle> find(Rectangle &r) {
  }

  virtual bool isRoot() {
    return parent == NULL;
  }

};
