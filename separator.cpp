#include <iostream>
#include <cctype>

#include "exceptions.h"
#include "separator.h"
#include "extractor.h"


std::vector<std::string> Separator::operator()(std::ifstream& fin) {

    // EXTRACTION
    Extractor extract;
    std::vector<std::string> asw = std::move(extract(fin));

    // SEPARATION
    for(unsigned int i = 0; i < asw.size(); ++i) {
        std::string str = asw[i];
        unsigned int j = 0;
        while(j < str.size()) {

            // we separate all possible cases:

            // '('
            if(str[j] == '(') {
                sw.push_back("(");
                ++j;
                continue;
            }

            // ')'
            if(str[j] == ')') {
                sw.push_back(")");
                ++j;
                continue;
            }

            // Alphabetic string (keyword or not):
            if(std::isalpha(str[j])) {
                std::stringstream tmp;
                while(std::isalpha(str[j])) {
                    tmp << str[j];
                    ++j;
                }
                sw.push_back(tmp.str());
                continue;
            }

            // Numerical string (pure):
            if(std::isdigit(str[j])) {
                if(str[j] == '0' && std::isdigit(str[j + 1])) {
                    std::stringstream tmp;
                    tmp << "the number in this piece of code is not valid: '" << str << "', the only number that begins with '0' is '0' itself";
                    throw invalidNumber(tmp.str());
                } else {
                    std::stringstream tmp;
                    while(std::isdigit(str[j])) {
                        tmp << str[j];
                        ++j;
                    }
                    sw.push_back(tmp.str());
                    continue;
                }
            }

            // A minus followed by a numerical string:
            if(str[j] == '-') {
                if(str[++j] == '0' && std::isdigit(str[j + 1])) {
                    std::stringstream tmp;
                    tmp << "the number in this piece of code is not valid: '" << str << "', the only number that begins with '0' is '0' itself";
                    throw invalidNumber(tmp.str());
                } else {
                    std::stringstream tmp;
                    tmp << '-';
                    while(std::isdigit(str[j])) {
                        tmp << str[j];
                        ++j;
                    }
                    sw.push_back(tmp.str());
                    continue;
                }
            }

            // if comes out an external character:
            std::stringstream tmp;
            tmp << "the string: \"" << str << "\" is not recognized";
            throw tokenNotRecognized(tmp.str());
        }
    }

    return sw;
}
