#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include "token.h"

struct tokenNotRecognized : std::runtime_error {
    tokenNotRecognized(const char* str) : std::runtime_error(str) {}
    tokenNotRecognized(std::string str) : std::runtime_error(str.c_str()) {}
};

struct invalidNumber : std::runtime_error {
    invalidNumber(const char* str) : std::runtime_error(str) {}
    invalidNumber(std::string str) : std::runtime_error(str.c_str()) {}
};

struct expectedObject : std::runtime_error {
    expectedObject(const char* str, std::string f) : std::runtime_error(str), following{ f } {}
    expectedObject(std::string str, std::string f) : std::runtime_error(str), following{ f } {}

    std::string following;
};

struct badEnd : std::runtime_error {
    badEnd() : std::runtime_error("the program cannot end like this") {}
};

struct badInput : std::runtime_error {
    badInput() : std::runtime_error("bad input, it's only possible to insert integers") {}
};

#endif // EXCEPTIONS_H
