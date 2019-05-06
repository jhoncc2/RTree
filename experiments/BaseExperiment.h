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

    void startTimer() {
        tini = high_resolution_clock::now();
        cini = std::clock();
    }

    void stopTimer(){

        cend = std::clock();
        tend = high_resolution_clock::now();
        
        auto duration = std::chrono::duration<double, std::milli>(tend-tini).count();
        auto durationCpu = 1000.0 * (cend - cini) / CLOCKS_PER_SEC;
        
        // (*outlist).push_back(durationCpu);
        // cout << duration << '\t';
        cout << durationCpu << '\t';
    }

};
