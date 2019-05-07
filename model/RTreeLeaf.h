using namespace std;
#include <vector>



class RTreeLeaf: public RTree {

  vector<Rectangle*> data;

public:

  RTree *insertRectangle(Rectangle *r){
    needsSave = true;
    RTree *res = this->insertRectangleInternal(r);
    this->saveInMemory();
    return res->root();
  }

  RTree *insertRectangleInternal(Rectangle *r){
    if(bbox == nullptr) {
      bbox = new Rectangle(r);
    }
    loadDataIfNeeded();

    data.push_back(r);
    bbox->rebound(r);
    // redimension if needed 

    if (data.size() > conf::CONST_LEAF_M) {
      return this->split()->root();
    }

    return this->root();
  }

  void loadDataIfNeeded() {
    if(data.size() == 0 && this->getScalarSize() > 0) {
      conf::fileManager->loadTreeChildren(this, 1);
    }
  }

  vector<Rectangle*> find(Rectangle *r) {
    if(!bbox->intersect(r))
      return {};

    vector<Rectangle*> res;
    loadDataIfNeeded();
    for (int i =1; i < data.size(); i++) {
      if (data[i]->intersect(r)) {
        res.push_back(data[i]);
      }
    }
    return res;
  }

  bool isRoot() {
    return parent == NULL;
  }

  bool isLeaf() {
    return true;
  }

  vector<Rectangle*> getData() {
    return data;
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
  int heightInMemory(){
    return 1;
  }


  RTree* split() {
    // cout << "leaf split "  << bbox->serialize() << parent << endl;
    RTree *left, *right, *localRoot;
    triplete trip;
    this->chooseAnchors(&trip);
    // cout << trip.i << " - " << trip.j << endl;
    // cout << data[trip.i] << " - " << data[trip.j] << endl;
    
    // reuse
    vector<Rectangle*> dataResp;
    dataResp = data;
    data = {};
    bbox = nullptr;

    // fill up new neightbors
    localRoot = getOrCreateParent();
    left = this->newInstance();
    right = this->newInstance();
    left->insertRectangleInternal(dataResp[trip.i]);
    right->insertRectangleInternal(dataResp[trip.j]);

    // create structure
    localRoot->removeIfFound(this);
    localRoot->addNodeSilently(left);
    localRoot->addNodeSilently(right);
    localRoot->rebound(left);
    localRoot->rebound(right);

    // localRoot = localRoot->updateBoundingBoxSplitIfNeeded();
    
    // fill remaining data
    for(int i = 0; i < dataResp.size(); i++) {
      if ((i != trip.i) && (i != trip.j)) {
        localRoot->insertRectangleInternal(dataResp[i]);
      }
    }

    // delete this;
    if(localRoot->getSize() > conf::CONST_LEAF_M) {
      return parent->split();
    }
    return localRoot->root();
  }

  triplete* chooseAnchors(triplete *trip){
    int strategy = conf::CONST_SPLIT_HEURISTIC;
    if (strategy == conf::CONST_LINEAR_SPLIT) {
      return chooseAnchorsLinear(trip);
    } else if (strategy == conf::CONST_QUADRATIC_SPLIT) {
      return chooseAnchorsQuadratic(trip);
    }
  }

  triplete* chooseAnchorsLinear(triplete *trip){
    vector<float> initialx;
    vector<float> endingx;
    vector<float> initialy;
    vector<float> endingy;

    for (int i = 0; i < data.size(); ++i) {
      initialx.push_back(data[i]->ini->x);
      endingx.push_back(data[i]->end->x);

      initialy.push_back(data[i]->ini->y);
      endingy.push_back(data[i]->end->y);
    }

    triplete t1 = minMax(endingx, initialx, 0, data.size()-1, bbox->end->x - bbox->ini->x);
    triplete t2 = minMax(endingy, initialy, 0, data.size()-1, bbox->end->y - bbox->ini->y);

    trip->dist = t1.dist;
    trip->i = t1.i;
    trip->j = t1.j;
    if (t1.dist < t2.dist) {
      trip->dist = t2.dist;
      trip->i = t2.i;
      trip->j = t2.j;
    }

    return trip;
  }

  triplete* chooseAnchorsQuadratic(triplete *trip){
    vector<Rectangle*> list = data;

    double dist = list[0]->unusefulArea(list[1]);
    trip->dist = dist;
    trip->i = 0;
    trip->j = 1;

    for(int i = 1; i < list.size(); i++) {
      for(int j = i+1; j < list.size(); j++) {
        dist = list[i]->unusefulArea(list[j]);
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

  triplete* chooseAnchorsExtra(triplete *trip){
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
    output << this->isLeaf()
        << ',' << 3 // rectangles, not used
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
    float ix = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float iy = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float ex = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float ey = std::stof(segment, nullptr);

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

  void updateBoundingBox() {
    for(int i = 0; i < data.size(); i++) {
      bbox->rebound(data.at(i));
    }
  }


  virtual bool equals(RTree *other) {
    return other->isLeaf() 
          && bbox->equals(other->boundingBox()) 
          && getSize() == getSize();
  }

  void unloadNodesFromMemory(int level) {
    if (!isSecondMemory()){
      return;
    }

    if(level == 0){
      data.clear();
    }

      
  }

};

