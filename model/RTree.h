using namespace std;
#include <vector>



class RTree {
protected:
  Rectangle *bbox = nullptr;
  RTree *parent = nullptr;
  string filename = "";
  int sizee = 1;

public:

  virtual RTree *insert(int ix, int iy, int ex, int ey) {
    return insertRectangle(new Rectangle(ix, iy, ex, ey));
  }

  virtual RTree *insertRectangle(Rectangle *r){}

  virtual vector<Rectangle> find(Rectangle &r) {
  }

  virtual RTree *split(int strategy){
    // setup
    if(parent == nullptr)
      parent = this->newInstanceParent(); // parent tree

    RTree *left = this->newInstance();
    RTree *right = this->newInstance(); // new sibling tree

    
    parent->setBoundingBox(bbox);
    parent->replace(this, left, right);

    if (strategy == conf::CONST_LINEAR_SPLIT) {
      linearSplit(left,right);
    } else if (strategy == conf::CONST_QUADRATIC_SPLIT) {
      // quadraticSplit();
    }

    return parent;
  }

  virtual int expandedArea(Rectangle *r){
    Rectangle *rect = new Rectangle(bbox);
    rect->rebound(r);
    return rect->area();
  }

  virtual void replace(RTree *toBeReplaced, RTree *a, RTree *b){}

  virtual void linearSplit(RTree *left, RTree *right){}

  virtual RTree *newInstance(){}

  virtual RTree *newInstanceParent(){}

  virtual vector<Rectangle*> getBoundingBoxContent(){}

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

  virtual void addNode(RTree *t) {}

  void setBoundingBox(Rectangle *r) {
    bbox = r;
  }


};

