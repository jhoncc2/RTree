using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

class RandomExperiment : public BaseExperiment {

public:

  void run() {
    RTree *root = new RTreeLeaf();

    // configuration of sencond memory
    conf::fileManager = new File();
    conf::CONST_SECOND_MEMORY = true;
    conf::LEVELS_IN_MEMORY = 1;
    conf::CONST_LEAF_M = conf::bytesInBlock / conf::bytesRectangle; // number of elements in Leaf
    conf::CONST_M = conf::bytesInBlock / conf::bytesRTree; // number of elements in Leaf
    
    // linear experiment 
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_LINEAR_SPLIT;
    int ini = 9;
    int exps = 12;

    for (int i = ini; i < exps ; ++i) {
      cout << "********CONST_QUADRATIC_SPLIT********" << endl;
      cout << "2^" << i  << ":" << endl;
      startTimer();
      insertRandomRectangles(root, pow(2,i));
      stopTimer();
    }

    // quadratic 
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_QUADRATIC_SPLIT;
    cout << "********CONST_QUADRATIC_SPLIT********" << endl;
    for (int i = ini; i < exps ; ++i) {
      cout << "2^" << i  << ":" << endl;
      startTimer();
      insertRandomRectangles(root, pow(2,i));
      stopTimer();
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
