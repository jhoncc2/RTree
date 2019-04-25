using namespace std;
#include <vector>

class RTreeLeaf: public RTree {
  RTree *parent = nullptr;
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
    return data.size();
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
    }

    return output.str();
  }


  virtual void addRectangleSilently(Rectangle *r) {
    data.push_back(r);
  }

};
