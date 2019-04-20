#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

namespace console{

  int handlecommands(int argc, char *argv[]) {
      // // contants
      // std::string datafolder = BaseController::dataFolder();
      // test
      if (exist(argv, argv + argc, "--hello")) {
        std::string name = "";
        if (exist(argv, argv + argc, "--name")){
          name = console::get(argv, argv + argc, "--model");
        }
        std::cout << "Hello " << name;
      }
      return 0;
  }
}
