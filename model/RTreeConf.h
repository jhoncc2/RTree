using namespace std;

namespace conf  {
	// heuristics for spliting
    const int CONST_LINEAR_SPLIT = 1;
    const int CONST_QUADRATIC_SPLIT = 2;
    const int CONST_GRENEE_SPLIT = 3;
    const int CONST_RTREE_SPLIT = 4;

    const int SIN_MAX_POINT = 50000;
    const int SIN_MAX_DIST = 100;

    // system configuration
    int bytesInBlock = 512; // bytes
    int bytesRectangle = 4; //bytes 1 byte per float
    int bytesRTree = 8 + 4;
    //customisable

    int CONST_m = 10;
    int CONST_M = 100;
    int CONST_LEAF_M = 100;
    int CONST_SPLIT_HEURISTIC = CONST_LINEAR_SPLIT;

    // secondary memory
    bool CONST_SECOND_MEMORY = false;
    FileAbstract *fileManager;
    int LEVELS_IN_MEMORY = 1;
    string dataDirectory = "data/";
}