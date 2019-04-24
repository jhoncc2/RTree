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
        (new RTreeTest())->run();
        (new SerializeTest())->run();
        std::cout << "----- end test section -----" << endl;
      }
      return 0;
  }
}
