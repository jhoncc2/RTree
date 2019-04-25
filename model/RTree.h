using namespace std;
#include <vector>


class RTree {
protected:
  Rectangle *bbox = nullptr;
  RTree *parent = nullptr;

public:

  virtual void insert(int ix, int iy, int ex, int ey) {
    insertRectangle(new Rectangle(ix, iy, ex, ey));
  }

  virtual Rectangle *insertRectangle(Rectangle *r) {

  }

  virtual vector<Rectangle> find(Rectangle &r) {
  }

  virtual bool isRoot() {
    return parent == NULL;
  }
  virtual bool isLeaf() { return false;}

  virtual string serialize() { }

  Rectangle *boundingBox() {
    return bbox;
  }

};
