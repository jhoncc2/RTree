using namespace std;
#include <vector>



class RTreeLeaf: public RTree {

  vector<Rectangle*> data;

public:

  RTree *insertRectangle(Rectangle *r){
    if(bbox == nullptr) {
      bbox = new Rectangle(r);
    }

    data.push_back(r);
    bbox->rebound(r);
    // redimension if needed 

    if (data.size() > conf::CONST_M) {
      return this->split()->root();
    }

    return this->root();
  }


  vector<Rectangle> find(Rectangle *r){
    vector<Rectangle> res;
    return res;
  }

  bool isRoot() {
    return parent == NULL;
  }

  bool isLeaf() {
    return true;
  }

  int getSize() {
    return data.size();
  }

  int treeSize(){
    return data.size();
  }

  virtual int height(){
    return 1;
  }

  RTree* linearSplit() {
    cout << "leaf split "  << bbox->serialize() << parent << endl;
    RTree *left, *right, *localRoot;
    triplete trip;
    this->chooseAnchors(&trip);
    cout << trip.i << " - " << trip.j << endl;
    cout << data[trip.i] << " - " << data[trip.j] << endl;
    
    // fill up new neightbors
    localRoot = getOrCreateParent();
    left = this->newInstance();
    right = this->newInstance();
    left->insertRectangle(data[trip.i]);
    right->insertRectangle(data[trip.j]);

    // create structure
    localRoot->removeIfFound(this);
    localRoot->addNodeSilently(left);
    localRoot->addNodeSilently(right);
    localRoot->rebound(left);
    localRoot->rebound(right);

    // localRoot = localRoot->updateBoundingBoxSplitIfNeeded();
    
    // fill remaining data
    for(int i = 0; i < data.size(); i++) {
      if ((i != trip.i) && (i != trip.j)) {
        cout << i << ", " ;
        localRoot->insertRectangle(data[i]);
      }
    }
    cout << endl;

    delete this;
    if(localRoot->getSize() > conf::CONST_M) {
      return parent->split();
    }
    return localRoot->root();
  }

  triplete* chooseAnchors(triplete *trip){
    vector<Rectangle*> list = data;

    double dist = list[0]->distance(list[1]);
    trip->dist = dist;
    trip->i = 0;
    trip->j = 1;

    for(int i = 1; i < list.size(); i++) {
      for(int j = i+1; j < list.size(); j++) {
        dist = list[i]->distance(list[j]);
        if(trip->dist < dist){
          trip->dist = dist;
          trip->i = i;
          trip->j = j;
        }
      }
    }

    return trip;
    // left->insertRectangle(list[linearDist.i]);
    // right->insertRectangle(list[linearDist.j]);
  }

  void linearSplit2(RTree *resParent, RTree *left, RTree *right) {
    triplete linearDist;
    vector<Rectangle*> list = data;

    double dist = list[0]->distance(list[1]);
    linearDist.dist = dist;
    linearDist.i = 0;
    linearDist.j = 1;

    for(int i = 1; i < list.size(); i++) {
      for(int j = i+1; j < list.size(); j++) {
        dist = list[i]->distance(list[j]);
        if(linearDist.dist < dist){
          linearDist.dist = dist;
          linearDist.i = i;
          linearDist.j = j;
        }
      }
    }

    left->insertRectangle(list[linearDist.i]);
    right->insertRectangle(list[linearDist.j]);

  }

  void quadraticSplit(vector<Rectangle*> *v, RTree *left, RTree *right) {}

  
  /********** miscelanious ***********/

  virtual vector<Rectangle*> getBoundingBoxContent(){
    return data;
  }

  std::string serialize() {
    //header
    ostringstream output;
    output << 1
        << ',' << data.size()
        << endl;

    //body
    for(int i = 0; i< data.size(); i++) {
      output << data[i]->serialize();
      output << endl;
    }
    return output.str();
  }

  virtual void addRectangleSilently(Rectangle *r) {
    data.push_back(r);
  }

  RTree *newInstance(){
    return new RTreeLeaf();
  }

  virtual RTree *newInstanceParent(){
    return new RTreeNode(); 
  }

  static RTree *createInstance(string line) {
    std::istringstream iss(line);
    std::string segment;

    std::getline(iss, segment, ',');
    int b = std::stoi(segment, nullptr); // number of elements
    std::getline(iss, segment, ',');
    string c = segment; // filename
    // boudning box
    std::getline(iss, segment, ',');
    int ix = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int iy = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int ex = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int ey = std::stoi(segment, nullptr);

    RTree *t = new RTreeLeaf();
    t->setBoundingBox(new Rectangle(ix,iy,ex,ey));
    t->setFilename(c);
    t->setSize(b);

    return t;
  }


  virtual void replace(RTree *toBeReplaced, RTree *a, RTree *b) {
    throw "should not get here RTreeLeaf, replace method";
  }
  virtual void removeIfFound(RTree *b) {
    throw "should not get here RTreeLeaf, replace method";
  }
  virtual void addNode(RTree *b) {
    throw "should not get here RTreeLeaf, replace method";
  }

  virtual bool isNode() {
    return false;
  }

  virtual void printTree(string prefix) {
    cout << prefix << "(" << bbox->serialize() << ")" <<endl;
    for (int i = 0; i < data.size(); ++i){
      cout << prefix << prefix << "[" << data[i]->serialize() << "]" <<endl;
    }
    
  }


};

