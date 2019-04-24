#include <algorithm>
#include <sstream>
#include <string>
#include <string.h>
// #include <stdio.h>

using namespace std;

class TestSuite {

public :
  // test methods
    const char *context;

    void setContext(const char *funName){
      context = funName;
    }

    virtual void run() {}

    bool assertTrue(bool a) {
      if (a)
        return true;

      throwException();
    }

    template <class T>
    bool assertEquals(T a, T b) {
      if (a == b)
        return true;
      throwException();
    }

    void throwException() {
      std::stringstream logstream;
      logstream << "This is my exception error. :( " << context;
      throw TestException(logstream.str().c_str());
    }

    // bool assertVector(vector<T> a, vector<T> b) {
    //   for (int i=0; i<a.size(); i++){
    //
    //   }
    //   return  a.size() == b.size();
    // }

};
