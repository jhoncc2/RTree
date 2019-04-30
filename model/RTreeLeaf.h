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
      return this->split(conf::CONST_SPLIT_HEURISTIC);
    }

    return this;
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

  int size(){
    if (data.size() > sizee)
      sizee = data.size();

    return sizee;
  }

  struct triplete {
    double dist;
    int i,j;
  };

  void linearSplit(RTree *left, RTree *right) {
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

    if (linearDist.dist < 0) {
      int tmp = linearDist.i;
      linearDist.i = linearDist.j;
      linearDist.j = tmp;
    }

    left->insertRectangle(list[linearDist.i]);
    right->insertRectangle(list[linearDist.j]);

    for(int i = 0; i < list.size(); i++) {
      if ((list[i] != list[linearDist.i]) && (list[i] != list[linearDist.j])) {
        parent->insertRectangle(list[i]);
      }
    }
  }


  void quadraticSplit(vector<Rectangle*> *v, RTree *left, RTree *right) {
    
  }

  
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

  virtual void replace(RTree *toBeReplaced, RTree *a, RTree *b) {
    throw "should not get here RTreeLeaf, replace method";
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

    RTree *t = new RTreeLeaf();
    t->setBoundingBox(new Rectangle(ix,iy,ex,ey));
    t->setFilename(c);
    t->setSize(b);

    return t;
  }

};
