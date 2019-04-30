using namespace std;
#include <vector>

class RTreeNode : public RTree {
  vector<RTree*> children;

public:

  RTree *insertRectangle(Rectangle *r){
    int minArea = children[0]->expandedArea(r);
    int index = 0;

    for (int i =1; i < children.size(); i++) {
      int area = children[i]->expandedArea(r);
      if(minArea > area) {
        index = i;
        minArea = area;
      }
    }

    children[index]->insertRectangle(r);

    return this;
  }

  vector<Rectangle> find(Rectangle &r){
    vector<Rectangle> res;
    return res;
  }

  bool isRoot() {
    return parent == NULL;
  }

  void addNodeSilently(RTree *t) {
    children.push_back(t);
  }

  virtual vector<Rectangle*> getBoundingBoxContent(){
    vector<Rectangle*> res;
    for (int i =0; i<children.size(); i++) {
      res.push_back(children[i]->boundingBox());
    }
    return res;  
  }

  int size(){
    int s = 0;
    for (int i =0; i<children.size(); i++) {
      s = s + children[i]->size();
    }

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
          << "," << children[i]->size()
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

  virtual void addNode(RTree *t) {
    children.push_back(t);
  }

  virtual void linearSplit(RTree *left, RTree *right){
    //TODO
  }

};
