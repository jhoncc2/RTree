using namespace std;
#include <vector>

virtual RTree * RTree::createInstance(string line) {
  std::istringstream iss(line);
  std::string segment;

  // cout << line << endl;
  std::getline(iss, segment, ',');
  int a = std::stoi(segment, nullptr); // is leaf
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

  RTree t;
  if (a) {
    t = new RTreeLeaf();
    t->setBoundingBox(new Rectangle(ix,iy,ex,ey));
    t->setFilename(c);
  } else {
    t = new RTreeNode();
    t->setBoundingBox(new Rectangle(ix,iy,ex,ey));
    t->setFilename(c);
  }

  return t;
}
