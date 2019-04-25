using namespace std;
#include <vector>

class RTreeLeaf: public RTree {

  vector<Rectangle*> data;

public:

  Rectangle *insertRectangle(Rectangle *r){
    RTree::insertRectangle(r);

    if(bbox == nullptr) {
      bbox = new Rectangle(r);
    }
    data.push_back(r);
    bbox->rebound(r);
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
