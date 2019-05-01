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
      cout << "************* Running " << funName << "*************" << endl;
    }

    virtual void run() {
      assertTrue(true);
      assertNull(NULL);
      assertEquals(1,1);
      try {
        assertNull(1);
      } catch(TestException t) {}
    }

    bool assertTrue(bool a) {
      if (a)
        return true;
        throwException();
    }

    bool assertFalse(bool a) {
      return assertTrue(!a);
    }

    bool assert(bool a) {
      return assertTrue(a);
    }


    template <class T>
    bool assertEquals(T a, T b) {
      if (a == b)
        return true;
      throwException();
    }

    template <class T>
    bool assertNull(T a) {
      if (a == 0) // null pointer, points to 0
        return true;
      throwException();
    }

    void throwException() {
      std::stringstream logstream;
      logstream << "This is my exception error. :( " << context;
      throw TestException(logstream.str().c_str());
    }


};
