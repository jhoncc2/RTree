using namespace std;
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
    getline(file, line);// remove header

    if(tree->isLeaf()) {
      RTreeLeaf *l = dynamic_cast<RTreeLeaf*>(tree);
      while(getline(file, line)) {
        l->addRectangleSilently(Rectangle::createInstance(line));
      }
    } else {
      // while(getline(file, line)) {
      //   tree->addElementSilently(Rectangle::createInstance(line));
      // }
    }
    file.close();
  }


};
