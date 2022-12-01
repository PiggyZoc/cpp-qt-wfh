//
// Created by Mac on 2022/12/1.
//

#include "utilities.h"

std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> tokens;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find('\n', prev)) != std::string::npos) {
        tokens.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    tokens.push_back(str.substr(prev));

    return tokens;
}