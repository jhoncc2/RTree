using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

class File {

public:

  static void store(RTree *tree) {
    fstream output;

    output.open(tree->getFilename(), ios::out);
    output << tree->serialize();
    output.close();
  }

  /*
  * stores all the tree, stops either deepness=0 or reached 
  * the leaf level
  */
  static void storeTree(RTree *tree, int deepness) {
    // failsafe
    if(deepness == 0)
       return;

    // recursive step
    RTreeNode *node;
    if (deepness > 1 && !tree->isLeaf()) 
      node = dynamic_cast<RTreeNode*>(tree);
      vector<RTree*> children = node->getChildren();
      for (int i = 0; i < children.size(); ++i) {
        children[i]->setFilename(node->getFilename().append(std::to_string(i)));
        storeTree(children[i], deepness-1);
      }

    // store
    store(tree);

  }

  static RTree* loadFromFile(string filename, int deepness) {
    string line;
    ifstream file;
    file.open(filename.c_str(), ios::in);

    // reading header
    Header header = readHeader(line);// remove header
    RTree* tree;

    if(header.isLeaf)
      tree = new RTreeLeaf();
    else 
      tree = new RTreeNode();

    loadTreeChildren(tree, deepness-1);
    tree->updateBoundingBox();
    return tree;
  }

  
  static void loadTreeChildren(RTree *tree, int deepness) {
    if (deepness == 0) 
      return;
    string line;
    ifstream file;
    file.open(tree->getFilename().c_str(), ios::in);

    if(tree->isLeaf()) {
      getline(file, line);// remove header
      RTreeLeaf *l = dynamic_cast<RTreeLeaf*>(tree);
      while(getline(file, line)) {
        l->addRectangleSilently(Rectangle::createInstance(line));
      }
    } else {
      getline(file, line);
      Header header = readHeader(line);// remove header
      RTreeNode *n = dynamic_cast<RTreeNode*>(tree);
      RTree *maker = new RTree();
      if(header.areChildrenLeaf) {
        while(getline(file, line)) {
          RTree *tmpl = RTreeLeaf::createInstance(line);
          n->addNodeSilently(tmpl);

          // recursive load
          if (deepness>1)
            loadTreeChildren(tmpl, deepness-1);
        }
      } else {
        while(getline(file, line)) {
          RTree *tmpl = RTreeNode::createInstance(line);
          n->addNodeSilently(tmpl);

          // recursive load
          if (deepness>1)
            loadTreeChildren(tmpl, deepness-1);
        }
      }
    }

    file.close();
  }

  struct Header{
    bool isLeaf, areChildrenLeaf;
    int size;
  };

  static Header readHeader(string line) {
    std::istringstream iss(line);
    std::string segment;
    // cout << line << endl;

    std::getline(iss, segment, ',');
    bool isLeaf = std::stoi(segment, nullptr);
    std::getline(iss, segment, ',');
    bool areChildrenLeaf = std::stoi(segment, nullptr); // areChildrenLeaf
    std::getline(iss, segment, ',');
    int size = std::stoi(segment, nullptr);

    // pair<int, int> r(isLeaf, size);
    // return r;
    Header h;
    h.isLeaf = isLeaf;
    h.areChildrenLeaf = areChildrenLeaf;
    h.size = size;
    return h;
  }


};
