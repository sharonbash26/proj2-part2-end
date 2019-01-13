#include <sstream>
#include "Util.h"

std::vector<std::string> Util::split(std::string str, char sep) {
    std::vector<std::string> v;
    std::istringstream iss(str);
    std::string tok;
    while (std::getline(iss, tok, sep)) {
        v.push_back(tok);
    }
    return std::move(v);
}