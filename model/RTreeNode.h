using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

class RTreeNode : public RTree {
  vector<RTree*> children;

public:

  RTreeNode(): RTree() {
  }

  RTree *insertRectangle(Rectangle *r){
    loadChildrenIfNeeded();
    RTree *newRoot = this->insertRectangleInternal(r);
    this->unloadNodesFromMemory(conf::LEVELS_IN_MEMORY);
    return newRoot->root();
  }

  RTree *insertRectangleInternal(Rectangle *r){
    bbox->rebound(r);

    float minArea = children[0]->expandedArea(r);
    int index = 0;

    for (int i =1; i < children.size(); i++) {
      float area = children[i]->expandedArea(r);
      if(minArea > area) {
        index = i;
        minArea = area;
      }
    }

    RTree *upadtedTree = children[index]->insertRectangle(r);

    return upadtedTree->root();
  }

  vector<Rectangle> find(Rectangle &r){
    vector<Rectangle> res;
    return res;
  }

  bool isRoot() {
    return parent == NULL;
  }

  void loadChildrenIfNeeded() {
    if(children.size() == 0 && this->getScalarSize() > 0) {
      conf::fileManager->loadTreeChildren(this, 1);
    }
  }

  virtual void addNode(RTree *t) {
    this->rebound(t);
    t->setParent(this);

    children.push_back(t);
  }

  void addNodeSilently(RTree *t) {
    children.push_back(t);
    t->setParent(this);
  }

  virtual vector<Rectangle*> getBoundingBoxContent(){
    vector<Rectangle*> res;
    for (int i =0; i<children.size(); i++) {
      res.push_back(children[i]->boundingBox());
    }
    return res;  
  }

  int getSize() {
    return children.size();
  }

  int treeSize(){
    int s = 0;
    for (int i=0; i<children.size(); i++)
      s = s + children[i]->treeSize();

    return s;
  }

  std::string serialize() {
    //header
    ostringstream output;
    output << this->isLeaf()
        << ',' << children[0]->isLeaf()
        << ',' << children.size()
        << endl;

    //body
    for(int i = 0; i< children.size(); i++) {
      output 
          // << this->isLeaf() << ","
          // << children[i]->isLeaf() << ","
          << children[i]->getSize() << ","
          << children[i]->getFilename() << ","
          << children[i]->boundingBox()->serialize()
          << endl;
    }

    return output.str();
  }

  static RTree *createInstance(string line) {
    std::istringstream iss(line);
    std::string segment;

    // cout << line << endl;
    // std::getline(iss, segment, ',');
    // int a = std::stoi(segment, nullptr); // is leaf
    std::getline(iss, segment, ',');
    int b = std::stoi(segment, nullptr); // number of elements
    std::getline(iss, segment, ',');
    string c = segment; // filename

    cout << c << endl;

    // boudning box
    std::getline(iss, segment, ',');
    float ix = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float iy = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float ex = std::stof(segment, nullptr);
    std::getline(iss, segment, ',');
    float ey = std::stof(segment, nullptr);

    // std::cout << touple << endl;
    // std::cout << i << "-" << n << "-" << r << endl;

    RTree *t = new RTreeNode();
    t->setBoundingBox(new Rectangle(ix,iy,ex,ey));
    t->setFilename(c);
    t->setSize(b);

    return t;
  }

  vector<RTree*> getChildren(){
    return children;
  }

  virtual RTree *newInstance(){
    return new RTreeNode();
  }

  virtual RTree *newInstanceParent(){
    return new RTreeNode(); 
  }

  virtual void replace(RTree *toBeReplaced, RTree *a, RTree *b) {
    if(children.empty()){
      children.push_back(a);
      children.push_back(b);
      return;
    }
    for(int i = 0; i < children.size(); i++) {
      if (children.at(i) == toBeReplaced) {
        children.at(i) = a;
        children.push_back(b);
        return;
      }
    }
  }

  virtual void removeIfFound(RTree *toBeRemoved) {
    for(int i = 0; i < children.size(); i++) {
      if (children.at(i) == toBeRemoved) {
        children.erase(children.begin() + i);
        return;
      }
    }
  }

  virtual int height(){
    return 1 + children.front()->height();
  }
  int heightInMemory(){
    if(children.size() == 0) 
      return 1;
    else
      return 1 + children.front()->heightInMemory();
  }

  vector<Rectangle*> getChildrenBoundingBox() {
      return this->getBoundingBoxContent();
  }

  double distance(RTree *other) {
    return this->boundingBox()->distance(other->boundingBox());
  }

  double unusefulArea(RTree *other) {
    return this->boundingBox()->unusefulArea(other->boundingBox());
  }

  RTree* split(){
    RTree *left, *right, *parent;
    triplete trip;
    this->chooseAnchors(&trip);
    
    vector<RTree*> childrenResp;
    childrenResp = children;
    children = {};
    bbox = nullptr;

    // fill up new neightbors
    parent = getOrCreateParent();
    left = this; //recicle
    right = this->newInstance();
    left->addNode(childrenResp[trip.i]);
    right->addNode(childrenResp[trip.j]);


    // create structure
    parent->removeIfFound(this);
    parent->addNodeSilently(left);
    parent->addNodeSilently(right);
    parent->rebound(left);
    parent->rebound(right);

    // parent = parent->updateBoundingBoxSplitIfNeeded();
    
    // fill remaining children
    for(int i = 0; i < childrenResp.size(); i++) {
      if ((childrenResp[i] != childrenResp[trip.i]) && (childrenResp[i] != childrenResp[trip.j])) {
        parent->insertNode(childrenResp[i], 1);
      }
    }

    left->saveInMemory();
    right->saveInMemory();
    parent->saveInMemory();

    // this->deleteObject();
    if(parent->getSize() > conf::CONST_M) {
      return parent->split();
    }

    return parent->root();
  }


  void deleteObject() {
    if(isSecondMemory())
      remove(this->getFilename().c_str());
    delete this;
  }

  // chooses the most appropiate node to insert it, 
  // in deeper as in the argument level is defined
  void insertNode(RTree *r, int level) {
    if (level == 0) {
      this->addNode(r);
      return;
    }

    bbox->rebound(r->boundingBox());

    float minArea = children[0]->expandedArea(r->boundingBox());
    int index = 0;

    for (int i =1; i < children.size(); i++) {
      float area = children[i]->expandedArea(r->boundingBox());
      if(minArea > area) {
        index = i;
        minArea = area;
      }
    }

    children[index]->insertNode(r, level-1);
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
    // calculate distance between nodes (it uses its bounding boxes)

    vector<float> initialx;
    vector<float> endingx;
    vector<float> initialy;
    vector<float> endingy;

    for (int i = 0; i < children.size(); ++i) {
      initialx.push_back(children[i]->boundingBox()->ini->x);
      endingx.push_back(children[i]->boundingBox()->end->x);

      initialy.push_back(children[i]->boundingBox()->ini->y);
      endingy.push_back(children[i]->boundingBox()->end->y);
    }

    triplete t1 = minMax(endingx, initialx, 0, children.size()-1, bbox->end->x - bbox->ini->x);
    triplete t2 = minMax(endingy, initialy, 0, children.size()-1, bbox->end->y - bbox->ini->y);

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
    // calculate unusefulArea between nodes (it uses its bounding boxes)
    double dist = children[0]->unusefulArea(children[1]);
    trip->dist = dist;
    trip->i = 0;
    trip->j = 1;

    for(int i = 1; i < children.size(); i++) {
      for(int j = i+1; j < children.size(); j++) {
        dist = children[i]->unusefulArea(children[j]);
        if(trip->dist < dist){
          trip->dist = dist;
          trip->i = i;
          trip->j = j;
        }
      }
    }

    return trip;
  }

  triplete* chooseAnchorsExtra(triplete *trip){
    // calculate distance between nodes (it uses its bounding boxes)
    double dist = children[0]->distance(children[1]);
    trip->dist = dist;
    trip->i = 0;
    trip->j = 1;

    for(int i = 1; i < children.size(); i++) {
      for(int j = i+1; j < children.size(); j++) {
        dist = children[i]->distance(children[j]);
        if(trip->dist < dist){
          trip->dist = dist;
          trip->i = i;
          trip->j = j;
        }
      }
    }

    return trip;
  }


  // deprecated
  // void linearSplit2(RTree *resParent, RTree *left, RTree *right) {
  //   cout << "split node " << endl;
  //   triplete linearDist;
  //   vector<RTree*> list = children;

  //   cout << "split node 1" << endl;
  //   double dist = list[0]->distance(list[1]);
  //   cout << "split node 2" << endl;
  //   linearDist.dist = dist;
  //   linearDist.i = 0;
  //   linearDist.j = 1;

  //   for(int i = 1; i < list.size(); i++) {
  //     for(int j = i+1; j < list.size(); j++) {
  //       dist = list[i]->distance(list[j]);
  //       if(linearDist.dist < dist){
  //         linearDist.dist = dist;
  //         linearDist.i = i;
  //         linearDist.j = j;
  //       }
  //     }
  //   }

  //   if (linearDist.dist < 0) {
  //     int tmp = linearDist.i;
  //     linearDist.i = linearDist.j;
  //     linearDist.j = tmp;
  //   }

  //   left->addNode(list[linearDist.i]);
  //   right->addNode(list[linearDist.j]);

  //   for(int i = 0; i < list.size(); i++) {
  //     if ((list[i] != list[linearDist.i]) && (list[i] != list[linearDist.j])) {
  //       resParent->addNode(list[i]);
  //     }
  //   }
    
  // }

  // updates the bouding box with children bouding box, 
  // and triggers split if ecceeds the size in conf::CONST_M
  virtual RTree* updateBoundingBoxSplitIfNeeded() {
    updateBoundingBox();
    if (children.size() > conf::CONST_M)
      return this->split();

    return this;
  }

  void updateBoundingBox() {
    for(int i = 0; i < children.size(); i++) {
      this->rebound(children.at(i));
    }
  }
 
  virtual void printTree(string prefix) {
    cout << prefix << "(" << boundingBox()->serialize() << ")" <<endl;
    for (int i = 0; i < children.size(); ++i){
      children[i]->printTree(prefix + prefix);
    }
  }

  virtual bool equals(RTree *other) {
    // return (!other->isLeaf())
    //       && (bbox->equals(other->boundingBox())) 
    //       && (getSize() == other->getSize());

    return (!other->isLeaf()) && (bbox->equals(other->boundingBox())) ;
  }

  void unloadNodesFromMemory(int level) {
    if (!isSecondMemory()){
      return;
    }

    // cout<< "remove children " << children.size() << " " << level << endl;
    if(level == 0){
      children.clear();
      return;
    }

    for (int i = 0; i < children.size(); ++i){
      children[i]->unloadNodesFromMemory(level - 1);
    }
  }
};
