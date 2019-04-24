#include <algorithm>
#include <string>


using namespace std;

class TestException: public std::runtime_error {

public :
  // test methods

  TestException(char const* const message) throw()
      :std::runtime_error(message){}

    // char const * what() const throw(){
    //     return std::exception::what();
    // }

};
