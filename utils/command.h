#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

namespace console{

  int handlecommands(int argc, char *argv[]) {
      // contants
      // std::string datafolder = BaseController::dataFolder();
      // test
      if (exist(argv, argv + argc, "--hello")) {
        std::string name = "";
        if (exist(argv, argv + argc, "--name")){
          name = console::get(argv, argv + argc, "--name");
        }
        std::cout << "Hello " << name;
      } else if (exist(argv, argv + argc, "--run-tests")) {
        std::cout << "----- running tests -----" << endl;
        try{
          (new TestSuite())->run();
          (new RectangleTest())->run();
          (new RTreeTest())->run();
          (new SerializeTest())->run();

          // test of tester
          TestSuite *suite = new TestSuite();
          suite->setContext(__func__);
          // suite->assert<int>(2,1);
          suite->assertEquals<int>(1,1);

          std::cout << "----- end test section -----" << endl;
        } catch(TestException e) {
          std::cout << "exception caught" << endl;
          std::cout << e.what() << endl;
        }

      }
      return 0;
  }
}
