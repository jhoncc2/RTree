#include <algorithm>
#include <string>

#ifndef GESTORDB_2_2018_UTILS_H
#define GESTORDB_2_2018_UTILS_H

#endif

namespace console{

    char* get(char ** begin, char ** end, const std::string & option)
    {
        char ** itr = std::find(begin, end, option);
        if (itr != end && ++itr != end)
        {
            return *itr;
        }
        return 0;
    }

    bool exist(char **begin, char **end, const std::string &option) {
        return std::find(begin, end, option) != end;
    }

}
