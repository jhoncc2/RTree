#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#ifndef GESTORDB_2_2018_UTILS_H
#define GESTORDB_2_2018_UTILS_H
#endif

using namespace std;


// import Models
#include "utils/FileAbstract.h"
#include "model/RTreeConf.h"
#include "model/Rectangle.h"
#include "model/RTree.h"
#include "model/RTreeNode.h"
#include "model/RTreeLeaf.h"
// #include "model/RTreeSerialization.h"
#include "utils/File.h"

// import tests
#include "testing/TestException.h"
#include "testing/TestSuite.h"
#include "testing/RectangleTest.h"
#include "testing/RTreeTest.h"
#include "testing/SerializeTest.h"

// Experiments
#include "experiments/BaseExperiment.h"
#include "experiments/RandomExperiment.h"

// importing utils for pre-computing
#include "utils/utils.h"
#include "utils/command.h"



// #include "models/Node.h"
// #include "models/Product.h"
// #include "models/Customer.h"
//
// #include "controller/BaseController.h"
// #include "models/Database.h"
// #include "models/DBMergeSort.h"
// #include "models/DBMergeBSort.h"
//
// #include "models/BTree.h"
// #include "models/BTreeLeaf.h"
// #include "models/BTreeNode.h"
//
//
// #include "controller/AbstractController.h"
// #include "controller/CustomerController.h"
// #include "controller/ProductController.h"
// #include "controller/QueryDatabase.h"


int main (int argc, char *argv[]) {
    // try
    // {
        return console::handlecommands(argc, argv);
    // }
    // catch(const std::exception&)  // Consider using a custom exception type for intentional
    // {                             // throws. A good idea might be a `return_exception`.
    //     cerr << endl << "error running the code" << endl;
    //     return EXIT_FAILURE;
    // }
}
