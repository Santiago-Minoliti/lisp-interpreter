#include <iostream>

#include "extractor.h"

// The operator takes in a std::ifstream object whose file is already open and it doesn't close it
std::vector<std::string> Extractor::operator()(std::ifstream& fin) {

    std::string s;
    while(fin >> s) asw.push_back(s);

    return asw;
}
