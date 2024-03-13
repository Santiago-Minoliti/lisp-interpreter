#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <string>
#include <vector>
#include <fstream>


 /** SEPARATOR:
  *
  *  Separator is a function object whose purpose is to separate the words in the vector "asw" (filled
  *  by an Extractor function object), put them in a vector and return it to the caller.
  *  Normally the caller is a std::vector<Token> Tokenizer::operator()(std::ifstream&) function object.
  *
  *  The characters are extracted as strings in order to avoid the problem of the different length of
  *  the keywords, although another problem shows up: when we extract a string, it get characters from
  *  a space character (tab, newline, etc...) to the next. Strings like: "(BLOCK", "-1)))" or even
  *  "varName))(BLOCK(IF(GT" are possible to appear.
  *
  *  The vector "sw" stands for "separated words", Separator role is to fill this vector with the words
  *  found in "asw" ready to tokenize: they will be strings like "BLOCK", "(", ")", "-20" or "varName".
  *
  */


class Separator{
public:
    // we accept the default constructors and distructor
    std::vector<std::string> operator()(std::ifstream& fin); // this operator returns the list of separated symbols or words like:
                                                             // "(", ")", "BLOCK", "INPUT", "n", "Fib1", "121", "-4" found in the file.
private:
    std::vector<std::string> sw; // separated words
};

#endif // SEPARATOR_H
