using namespace std;

namespace conf  {
	// heuristics for spliting
    const int CONST_LINEAR_SPLIT = 1;
    const int CONST_QUADRATIC_SPLIT = 2;
    const int CONST_GRENEE_SPLIT = 3;
    const int CONST_RTREE_SPLIT = 4;

    const int SIN_MAX_POINT = 50000;
    const int SIN_MAX_DIST = 100;

    //customisable
    int CONST_m = 10;
    int CONST_M = 100;
    int CONST_SPLIT_HEURISTIC = CONST_LINEAR_SPLIT;

    // secondary memory
    bool CONST_SECOND_MEMORY = true;
}