#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "token.h"
#include "factory.h"


 /** PARSER:
  *
  *  Parser is a class with double purpose: to build the syntax tree and to abort the process if some syntactic error
  *  comes out. The tree is built always starting from the program: Program* Parser::buildProgram() method is called by
  *  the main function in Parsing phase. The block is built iteratively by filling his Statement* vector with found
  *  statements. The statements are built recoursively.
  *
  *  When Parser is constructed it must revice the iterators of start and finish of the tokenStream, and the pointer
  *  to the factory, created by the main function, in order to make the nodes.
  *
  */


class Parser {
public:
    Parser(std::vector<Token>::iterator ti, std::vector<Token>::iterator se, Factory* const fctr) : tokenIterator{ ti }, streamEnd{ se }, factory{ fctr } {}
    Program* buildProgram(); // this function returns true if the program is correct otherwise it returns false
    Block* buildBlock();
    Statement* buildInput_stmt();
    Statement* buildPrint_stmt();
    Statement* buildVar_def_stmt();
    Statement* buildIf_stmt();
    Statement* buildLoop_stmt();
    Num_expr* buildNum_operator(Num_operator::opCode oc);
    Bool_expr* buildBool_comparator(Bool_comparator::symbCode sc);
    Bool_expr* buildBool_operator(Bool_operator::opCode oc);
    Bool_expr* buildBool_NOTstatement();
    Num_expr* buildNum_expr();
    Bool_expr* buildBool_expr();

    void op();
    void cp();
    std::string vid();
private:
    std::vector<Token>::iterator tokenIterator;
    std::vector<Token>::iterator streamEnd;
    Factory* const factory;
};


#endif // PARSER_H
