using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

class RandomExperiment : public BaseExperiment {

public:

  // static int numberOfRect = 10000;

  void run() {
    RTree *root = new RTreeLeaf();
    // linear experiment 
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_LINEAR_SPLIT;
    int exps = 10; 
    for (int i = 0; i < exps ; ++i) {
      insertRandomRectangles(root, pow(2,i));
    }

    // root = insertRandomRectangles(root, numberOfRect);
    
  }

  RTree* insertRandomRectangles(RTree *root, int num) {
    RTree *newRoot = root;
    for (int i = 0; i < num; ++i)
    {
      newRoot = root->insertRectangle(Rectangle::createRandom());
    }
    return newRoot;
  }

};
