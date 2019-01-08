//
// Created by sharon_i4 on 07/01/2019.
//

#include <string>
#include <algorithm>
#include "StringReverser.h"

std::basic_string<char> server_side::StringReverser::solve(std::string p) {
    std::string cpy(p);
    std::reverse(cpy.begin(), cpy.end());
    return cpy;
}
