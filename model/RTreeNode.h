using namespace std;
#include <vector>

class RTreeNode : public RTree {
  vector<RTree*> children;

public:

  RTreeNode(): RTree() {
  }

  RTree *insertRectangle(Rectangle *r){
    bbox->rebound(r);

    int minArea = children[0]->expandedArea(r);
    int index = 0;

    for (int i =1; i < children.size(); i++) {
      int area = children[i]->expandedArea(r);
      if(minArea > area) {
        index = i;
        minArea = area;
      }
    }

    return children[index]->insertRectangle(r)->root();
  }

  vector<Rectangle> find(Rectangle &r){
    vector<Rectangle> res;
    return res;
  }

  bool isRoot() {
    return parent == NULL;
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
    output << 1
        << ',' << children.size()
        << endl;

    //body
    for(int i = 0; i< children.size(); i++) {
      output << children[i]->isLeaf()
          << "," << children[i]->getSize()
          << "," << children[i]->getFilename()
          << "," << children[i]->boundingBox()->serialize()
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
    // boudning box
    std::getline(iss, segment, ',');
    int ix = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int iy = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int ex = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int ey = std::stoi(segment, nullptr);

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

  vector<Rectangle*> getChildrenBoundingBox() {
      return this->getBoundingBoxContent();
  }

  double distance (RTree *other) {
    return this->boundingBox()->distance(other->boundingBox());
  }

  RTree* linearSplit(){
    RTree *left, *right, *parent;
    triplete trip;
    this->chooseAnchors(&trip);
    
    // fill up new neightbors
    parent = getOrCreateParent();
    left = this->newInstance();
    right = this->newInstance();
    left->addNode(children[trip.i]);
    right->addNode(children[trip.j]);

    // create structure
    parent->removeIfFound(this);
    parent->addNodeSilently(left);
    parent->addNodeSilently(right);
    parent->rebound(left);
    parent->rebound(right);

    // parent = parent->updateBoundingBoxSplitIfNeeded();
    
    // fill remaining children
    for(int i = 0; i < children.size(); i++) {
      if ((children[i] != children[trip.i]) && (children[i] != children[trip.j])) {
        parent->insertNode(children[i], 1);
      }
    }

    delete this;
    return parent->root();
  }

  // chooses the most appropiate node to insert it, 
  // in deeper as in the argument level is defined
  void insertNode(RTree *r, int level) {
    if (level == 0) {
      this->addNode(r);
      return;
    }

    bbox->rebound(r->boundingBox());

    int minArea = children[0]->expandedArea(r->boundingBox());
    int index = 0;

    for (int i =1; i < children.size(); i++) {
      int area = children[i]->expandedArea(r->boundingBox());
      if(minArea > area) {
        index = i;
        minArea = area;
      }
    }

    children[index]->insertNode(r, level-1);
  }


  triplete* chooseAnchors(triplete *trip){
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
    for(int i = 0; i < children.size(); i++) {
      this->rebound(children.at(i));
    }
    if (children.size() > conf::CONST_M)
      return this->split();

    return this;
  }


 
  virtual void printTree(string prefix) {
    cout << prefix << "(" << boundingBox()->serialize() << ")" <<endl;
    for (int i = 0; i < children.size(); ++i){
      children[i]->printTree(prefix + prefix);
    }
  }

};
