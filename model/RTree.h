using namespace std;
#include <vector>


class RTree {
protected:
  Rectangle *bbox = nullptr;
  RTree *parent = nullptr;
  string filename = "";
  int sizee = 1;

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

  virtual void setParent(RTree *r) {
    parent = r;
  }

  void setFilename(string filename) {
    this->filename = filename;
  }

  string getFilename() {
    return filename;
  }

  virtual bool isLeaf() { return false;}
  virtual int size() { return this->sizee;}
  virtual int setSize(int size) {
    this->sizee = size;
  }

  virtual string serialize() { }

  Rectangle *boundingBox() {
    return bbox;
  }

  void setBoundingBox(Rectangle *r) {
    bbox = r;
  }


};
