#include <algorithm>
#include <string>

#endif
using namespace std;

namespace test{

    bool assert(std::int a, std::int b) {
        return  a == b;
    }

    bool assertList(std::int a, std::int b) {
        return  a.size() == b.size();
    }

}
