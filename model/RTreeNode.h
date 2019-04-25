using namespace std;
#include <vector>

class RTreeNode : public RTree {
  vector<RTree*> children;

public:

  Rectangle *insertRectangle(Rectangle *r){
    return r;
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


  int size(){
    if (children.size() > sizee)
      sizee = children.size();

    return sizee;
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

};
