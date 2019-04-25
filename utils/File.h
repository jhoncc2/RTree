using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

class File {

public:

  static void store(std::string filename, RTree *tree) {
    fstream output;

    output.open(filename, ios::out);
    output << tree->serialize();
    output.close();
  }

  static void load(std::string filename , RTree *tree) {

    string line;
    ifstream file;
    file.open(filename.c_str(), ios::in);

    if(tree->isLeaf()) {
      getline(file, line);// remove header
      while(getline(file, line)) {
        RTreeLeaf *l = dynamic_cast<RTreeLeaf*>(tree);
        l->addRectangleSilently(Rectangle::createInstance(line));
      }
    } else {
      getline(file, line);
      pair<int,int> header = readHeader(line);// remove header
      header.first; // kind (leaf or node)
      header.second; // size of the file

      RTreeNode *n = dynamic_cast<RTreeNode*>(tree);
      RTree *maker = new RTree();
      if(header.first) {
        while(getline(file, line)) {
          RTree *tmpl = RTreeLeaf::createInstance(line);
          tmpl->setParent(n);
          n->addNodeSilently(tmpl);
        }
      } else {
        while(getline(file, line)) {
          RTree *tmpl = RTreeNode::createInstance(line);
          tmpl->setParent(n);
          n->addNodeSilently(tmpl);
        }
      }
    }

    file.close();
  }

  static pair<int, int> readHeader(string line) {
    std::istringstream iss(line);
    std::string segment;
    // cout << line << endl;

    std::getline(iss, segment, ',');
    int isLeaf = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    int size = std::stoi(segment, nullptr);

    pair<int, int> r(isLeaf, size);
    return r;
  }

};
