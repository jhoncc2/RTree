#include <algorithm>
#include <string>


using namespace std;

class TestSuite{

public :
    virtual void run() {}

    template <class T> bool assert(T a, T b) {
      return  a == b;
    }

    // bool assertVector(vector<T> a, vector<T> b) {
    //   for (int i=0; i<a.size(); i++){
    //
    //   }
    //   return  a.size() == b.size();
    // }

};
