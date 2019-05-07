using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

class RandomExperiment : public BaseExperiment {

public:

  string filename = "result_data/random.txt";

  struct Information{
    string name;
    string time;
    string writings;
  };

  void run() {

    // configuration of sencond memory
    conf::CONST_SECOND_MEMORY = true;
    conf::fileManager = new File();
    conf::LEVELS_IN_MEMORY = 1;

    conf::dataDirectory = "data/";
    conf::CONST_LEAF_M = conf::bytesInBlock / conf::bytesRectangle; // number of elements in Leaf
    conf::CONST_M = conf::bytesInBlock / conf::bytesRTree; // number of elements in Leaf
    // conf::CONST_M = 2;
    // conf::CONST_LEAF_M = 2;

    this->multipleInsert();
  }

  void multipleInsert() {
    
    vector<Information> resultData;
    // run experiments
    int start = 9;
    int exps = 20;

    cout << "********CONST_LINEAR_SPLIT********" << endl;

    conf::CONST_SECOND_MEMORY = true;
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_LINEAR_SPLIT;
    RTree *root = new RTreeLeaf();
    for (int i = start; i < exps ; ++i) {
      Information inf;
      conf::writingCounter = 0;
      this->startTimer();
      for (int j = 0; j < exps ; ++j) {
        insertRandomRectangles(root, pow(2,i));
      }
      inf.name = "2^" + to_string(i);
      inf.time = this->stopTimer();
      inf.writings = to_string(conf::writingCounter);
      resultData.push_back(inf);
    }
    this->printResults(filename, "linear", resultData);

    // quadratic 
    cout << "********CONST_QUADRATIC_SPLIT********" << endl;
    conf::CONST_SECOND_MEMORY = true;
    conf::CONST_SPLIT_HEURISTIC = conf::CONST_QUADRATIC_SPLIT;
    root = new RTreeLeaf();
    for (int i = start; i < exps ; ++i) {
      Information inf;
      conf::writingCounter = 0;
      this->startTimer();
      for (int j = 0; j < exps ; ++j) {
        insertRandomRectangles(root, pow(2,i));
      }
      inf.name = "2^" + to_string(i);
      inf.time = this->stopTimer();
      inf.writings = to_string(conf::writingCounter);
      resultData.push_back(inf);
    }
    this->printResults(filename, "quadratic", resultData);
    // root = insertRandomRectangles(root, numberOfRect);
  }

  void printResults(string filename, string title, vector<Information> data) {
    fstream output;
    output.open(filename,  ios::out | ios::app);

    string a= "", b= "", c="";
    for (int i = 0; i < data.size(); ++i) {
      a = a + data[i].name + ", ";
      b = b + data[i].time + ", ";
      c = c + data[i].writings + ", ";
    }
    // string as = a.str();
    // string bs = b.str();
    // string cs = c.str();

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    cout << "M:" << conf::CONST_M 
          << " - " << "LEAF_M:" << conf::CONST_LEAF_M << endl;

    cout << conf::CONST_SPLIT_HEURISTIC 
      << " " << conf::writingCounter
      << " " << conf::CONST_SECOND_MEMORY << endl;

    output << endl << title << endl;
    output << "M:" << conf::CONST_M 
          << " - " << "LEAF_M:" << conf::CONST_LEAF_M << endl;
    output << a << endl;
    output << b << endl;
    output << c << endl;
    
    output.close();
  }

  RTree* insertRandomRectangles(RTree *root, int num) {
    RTree *newRoot = root;
    for (int i = 0; i < num; ++i) {
      newRoot = root->insertRectangle(Rectangle::createRandom());
     }
    return newRoot;
  }

};
