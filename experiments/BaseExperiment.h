using namespace std;

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>

using namespace std;
using namespace chrono;


class BaseExperiment {

public:

  /******* timer coder  *******/
  high_resolution_clock::time_point tini, tend;
  std::clock_t cini, cend;

  /* storage */ 
  string path = "result_data/";

  virtual void startTimer() {
    tini = high_resolution_clock::now();
    cini = std::clock();
  }

  string stopTimer() {
    cend = std::clock();
    tend = high_resolution_clock::now();
    
    auto duration = std::chrono::duration<double, std::milli>(tend-tini).count();
    auto durationCpu = 1000.0 * (cend - cini) / CLOCKS_PER_SEC;
    
    // (*outlist).push_back(durationCpu);
    // cout << duration << '\t';

    cout << "duration: " << durationCpu << endl;
    return to_string(durationCpu / 1000.0);
  }
  
};
