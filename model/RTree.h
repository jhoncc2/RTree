using namespace std;
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>


typedef unsigned int uint;

class RTree {
protected:
  Rectangle *bbox = nullptr;
  RTree *parent = nullptr;
  string filename = "";
  int sizee = 0;

  // 
  bool needsSave = false;

  
public:
  static FileAbstract *fileManager;

  RTree (){
  }

  virtual RTree *insert(int ix, int iy, int ex, int ey) {
    return insertRectangle(new Rectangle(ix, iy, ex, ey));
  }

  virtual RTree *insertRectangle(Rectangle *r){}
  virtual RTree *insertRectangleInternal(Rectangle *r){}

  virtual vector<Rectangle*> find(Rectangle *r) {}


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
  virtual int heightInMemory(){}

  virtual void removeIfFound(RTree *t){}

  virtual int treeSize() {}

  virtual int getSize() {}

  virtual int getScalarSize() {
    return this->sizee;
  }

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
    if (filename.empty()) {
      filename = conf::dataDirectory + randomStringName();
    }

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

  bool isSecondMemory() {
    return conf::CONST_SECOND_MEMORY;
  }


  FileAbstract *getFileManager() {
    return conf::fileManager;
  }

  virtual void unloadNodesFromMemory(int level) {}

  std::string randomString(uint maxLength = 15, std::string charIndex = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890")
  { // maxLength and charIndex can be customized, but I've also initialized them.
      uint length = rand() % maxLength + 1; // length of the string is a random value that can be up to 'l' characters.

      uint indexesOfRandomChars[15]; // array of random values that will be used to iterate through random indexes of 'charIndex'
      for (uint i = 0; i < length; ++i) // assigns a random number to each index of "indexesOfRandomChars"
          indexesOfRandomChars[i] = rand() % charIndex.length();

      std::string randomString = ""; // random string that will be returned by this function
      for (uint i = 0; i < length; ++i)// appends a random amount of random characters to "randomString"
      {
          randomString += charIndex[indexesOfRandomChars[i]];
      } 
      return randomString;
  }

  string randomStringName(){
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    // oss << std::put_time(&tm, "%d-%m-%Y%H-%M-%S");
    oss << to_string(ms.count());
    // auto str = oss.str();
    return oss.str() + ".dat";
  }

  void saveInMemory() {
    if (isSecondMemory() && needsSave)
      conf::fileManager->store(this);

    needsSave = false;
  }


};

