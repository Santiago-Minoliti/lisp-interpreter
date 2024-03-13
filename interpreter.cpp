#include <iostream>
#include <algorithm>

#include "exceptions.h"
#include "interpreter.h"

int Program::interpret() {
    b->interpret();
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Variable& v) {
    os << v.id << ": " << v.value;
    return os;
}
int Variable::interpret() {
    for(Variable* v : *var_table_ptr) {
        if(v->id == id) {
            std::stringstream tmp;
            tmp << "'" << v->id << "' was not declared";
            // if Variable v isn't valid it means it hasn't been declared yet,
            // when something declares a Variable we put that valid permanently
            if(!v->valid) throw std::runtime_error(tmp.str());
            return value;
        }
    }
}

Block& Block::push_back(Statement* s) {
    statement_list.push_back(s);
    return *this;
}
int Block::interpret() {
    for(Statement* stmt : statement_list) {
        stmt->interpret();
    }
    return 0;
}

int Input_stmt::interpret() {
    // we make the input with a string and then we carry out some checks on it
    std::string str;
    std::cin >> str;
    bool negative = false;
    if(str[0] == '-') { negative = true; str.erase(0, 1); }
    // we check if there is some not number character except the eventual sign at the start
    if(std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) != str.end()) {
        throw badInput();
    }
    // here we rebuild the original value
    toSet->value = std::stoi(str);
    if(negative) toSet->value *= -1;
    // here we update the symbol table and declare that the variable is now valid
    unsigned int i = 0;
    while((*(toSet->var_table_ptr))[i++]->id != toSet->id);
    (*(toSet->var_table_ptr))[i - 1]->value = toSet->value;
    toSet->valid = true;
    return 0;
}

int Print_stmt::interpret() {
    std::cout << toPrint->interpret() << std::endl;
    return 0;
}

int Var_def_stmt::interpret() {
    toSet->value = varValue->interpret();
    // here we update the symbol table and declare the variable is now valid
    unsigned int i = 0;
    while((*(toSet->var_table_ptr))[i++]->id != toSet->id);
    (*(toSet->var_table_ptr))[i - 1]->value = toSet->value;
    toSet->valid = true;
    return 0;
}

int If_stmt::interpret() {
    if(condition->interpret()) {
        then_stmt->interpret();
    } else {
        else_stmt->interpret();
    }
    return 0;
}

int Loop_stmt::interpret() {
    while(condition->interpret()) toRepeat->interpret();
    return 0;
}

int Number::interpret() {
    return value;
}

int Num_operator::interpret() {
    int l = left->interpret();
    int r = right->interpret();
    switch(oc) {
    case Num_operator::ADD:
        return l + r;
    case Num_operator::SUB:
        return l - r;
    case Num_operator::MUL:
        return l * r;
    case Num_operator::DIV:
        if(r == 0) {
            throw std::runtime_error("cannot divide by '0'");
        } else {
            return l / r;
        }
    }
}

int Bool_comparator::interpret() {
    switch(sc) {
    case Bool_comparator::GT:
        return left->interpret() > right->interpret();
    case Bool_comparator::LT:
        return left->interpret() < right->interpret();
    case Bool_comparator::EQ:
        return left->interpret() == right->interpret();
    }
}

int Bool_const::interpret() {
    return value;
}

int Bool_operator::interpret() {
    switch(oc) {
    case Bool_operator::AND:
        return left->interpret() && right->interpret();
    case Bool_operator::OR: // in C++ operators OR and AND are already short circuited
        return left->interpret() || right->interpret();
    case Bool_operator::NOT:
        return !(left->interpret()); // the NOT operation uses only the left operand
    }
}
