using namespace std;
#include <vector>



class RTree {
protected:
  Rectangle *bbox = nullptr;
  RTree *parent = nullptr;
  string filename = "";
  int sizee = 0;

public:

  RTree (){
  }

  virtual RTree *insert(int ix, int iy, int ex, int ey) {
    return insertRectangle(new Rectangle(ix, iy, ex, ey));
  }


  virtual RTree *insertRectangle(Rectangle *r){}

  virtual vector<Rectangle> find(Rectangle &r) {
  }


  // virtual RTree *split() {
  //   int strategy = conf::CONST_SPLIT_HEURISTIC;
  //   if (strategy == conf::CONST_LINEAR_SPLIT) {
  //     return treeSplit();
  //   } else if (strategy == conf::CONST_QUADRATIC_SPLIT) {
  //     // quadraticSplit();
  //   }
  // }


  virtual RTree *getOrCreateParent() {
    if(parent == nullptr) {
      
      return this->newInstanceParent(); // parent tree
    }
    return parent;
  }
  struct triplete {
    double dist;
    int i,j;
  };

  /* split */
  virtual double distance(RTree *r) {}

  virtual double unusefulArea(RTree *other) {
    return this->boundingBox()->unusefulArea(other->boundingBox());
  }

  virtual void addNode(RTree *t) {}
  // calculates the node where the area grows less, 
  // look into the tree as deep as is defined in level
  virtual void insertNode(RTree *t, int level) {}
  virtual void addNodeSilently(RTree *t) {}

  /* linear split */
  virtual RTree *split(){}
  virtual RTree* updateBoundingBoxSplitIfNeeded() {}
  // virtual triplete* chooseAnchors(RTree *left, RTree *right){}
  triplete* chooseAnchors(triplete *trip){}
  triplete* chooseAnchorsLinear(triplete *trip){}
  triplete* chooseAnchorsQuadratic(triplete *trip){}

  /* end linear split */

  // deprecated
  // virtual RTree *split2(int strategy) {
  //   // setup
  //   RTree *treeParent = nullptr;
  //   if(parent == nullptr) 
  //     treeParent = this->newInstanceParent(); // parent tree
  //   else 
  //     treeParent = parent;
    
  //   RTree *left = this->newInstance();
  //   RTree *right = this->newInstance(); // new sibling tree

  //   treeParent->removeIfFound(this);
  //   treeParent->addNode(left);
  //   treeParent->addNode(right);


  //   if (strategy == conf::CONST_LINEAR_SPLIT) {
  //     linearSplit(treeParent, left, right);
  //     this->multipleInsert();
  //   } else if (strategy == conf::CONST_QUADRATIC_SPLIT) {
  //     // quadraticSplit();
  //   }

  //   if(treeParent->getSize() > conf::CONST_M){
  //     return (treeParent->split(strategy))->root();
  //   } else {
  //     return treeParent->root();
  //   }

  //   // parent->replace(this, left, right);
    
  // }

  void rebound(RTree *t){
    if(bbox == nullptr)
      bbox = new Rectangle(t->boundingBox());

    bbox->rebound(t->boundingBox());
  }

  RTree* root(){
    if (this->isRoot()){
      return this;
    }
    
    return parent->root();
  }

  /*
  * Current node bounding box expanded area 
  */ 
  virtual float expandedArea(Rectangle *r){
    Rectangle *rect = new Rectangle(bbox);
    rect->rebound(r);
    return rect->area();
  }

  virtual void replace(RTree *toBeReplaced, RTree *a, RTree *b){}

  virtual RTree *newInstance(){}

  virtual RTree *newInstanceParent(){}

  virtual vector<Rectangle*> getBoundingBoxContent(){}

  virtual bool isLeaf() { return false; }

  virtual string serialize() { }
  virtual string serializeTree() { }
  
  virtual int height(){}

  virtual void removeIfFound(RTree *t){}

  virtual int treeSize() {}

  virtual int getSize() {}

  virtual int setSize(int size) {
    this->sizee = size;
  }

  Rectangle *boundingBox() {
    return bbox;
  }

  void setBoundingBox(Rectangle *r) {
    bbox = r;
  }

  void setFilename(string filename) {
    this->filename = filename;
  }

  string getFilename() {
    return filename;
  }

  virtual bool isRoot() {
    return parent == NULL;
  }

  virtual bool isNode() {
    return true;
  }

  virtual void setParent(RTree *r) {
    parent = r;
  }

  virtual RTree* getParent() {
    return parent;
  }

  virtual bool isFull() {
    return this->getSize() == conf::CONST_M;
  }

  void logTree(){
    this->printTree("-");
  }
  virtual void printTree(string prefix) {}

  virtual void updateBoundingBox() {}

  virtual bool equals(RTree *other) {}

  virtual triplete minMax(vector<float> minlist,
                          vector<float> maxlist, 
                          int min, 
                          int max, 
                          int ratio) {
    triplete t;
    if(abs(max - min) <= 1){
      
      // calculate min
      t.i= min; 
      if (minlist[min] > minlist[max]){
        t.i = max;
      }

      // calculate max
      t.j= max;
      if ((maxlist[min] > maxlist[max]) && min != t.i){ // safe to not pick the same item
        t.j = min;
      }
      
      t.dist = maxlist[t.j] - minlist[t.i];

      

    } else {
      int div = (min + max) /2;

      triplete t1 = minMax(minlist, maxlist, min, div-1, ratio);
      triplete t2 = minMax(minlist, maxlist, div, max, ratio);

      // calculate min
      t.i = t2.i;
      if (minlist[t1.i] < minlist[t2.i]){
        t.i = t1.i;
      }
        
      // calculate max
      t.j = t1.j;
      if ((maxlist[t1.j] < maxlist[t2.j]) && t2.j != t.i){ // safe to not pick the same item
        t.j = t2.j;
      }

      t.dist = maxlist[t.j] - minlist[t.i];
    }

    return t;
  }



};

