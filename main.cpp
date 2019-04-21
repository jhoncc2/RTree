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
#include "model/Rectangle.h"
#include "model/RTree.h"


// import tests
#include "testing/RTreeTest.h"

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
    try
    {
        return console::handlecommands(argc, argv);
    }
    catch(const std::exception&)  // Consider using a custom exception type for intentional
    {                             // throws. A good idea might be a `return_exception`.
        cerr << endl << "error running the code" << endl;
        return EXIT_FAILURE;
    }
}
