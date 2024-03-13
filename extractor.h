#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <vector>
#include <string>
#include <fstream>


 /** EXTRACTOR:
  *
  *  Extractor is a function object whose purpose is to extract raw strings from the given stream,
  *  put them in a string vector then return it to the caller.
  *  Normally the caller is a std::vector<std::string> Separator::operator()(std::ifstream&) function object.
  *
  *  the vector "asw" stands for "almost separated words", it worns that the strings in there aren't fully separated yet,
  *  strings like: "(BLOCK", "-1)))" or even "varName))(BLOCK(IF(GT" are possible to appear.
  *
  */


class Extractor{
public:
    // We accept the default constructors and distructor
    std::vector<std::string> operator()(std::ifstream& fin); // The operator takes out as strings the characters in the file, it returns the vector of the strings almost separated
private:
    std::vector<std::string> asw;
};

#endif // EXTRACTOR_H
