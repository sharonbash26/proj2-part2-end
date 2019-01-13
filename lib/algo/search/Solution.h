#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <vector>

class Solution {
    std::vector<std::string> optimalPath;
public:
    Solution(std::vector<std::string> _optimalPath) {
        this->optimalPath = _optimalPath;
    }

    std::vector<std::string> getOptimalPath() {
        return this->optimalPath;
    }

    std::string toString(){
        std::string str;
        for(const std::string &s : optimalPath){
            str += s;
            str += ',';
        }

        if(str.length() == 0){
            return "no_path";
        }
        // remove the last ,
        str.pop_back();
        return std::move(str);
    }
};

#endif
