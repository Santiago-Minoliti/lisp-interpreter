#ifndef FACTORY_H
#define FACTORY_H

#include <vector>

#include "interpreter.h"


 /** FACTORY:
  *
  *  Factory is a class whom every Composite object belongs to. This class has the factory methods that
  *  can allocate the nodes and the destructor of a Factory object will delete all the allocated nodes.
  *
  *  Factory keeps track of the nodes in the node_list vector.
  *
  *  Factory has also to include every variable it creates into the symbol table: the var_table vector.
  *
  */


class Factory {
public:
    Factory() = default;
    Factory(const Factory& other) = delete;
    Factory& operator=(const Factory& other) = delete;
    ~Factory(); // the destructor has to deallocate all nodes

    // Block and Program factories:
    Block* makeBlock();
    Program* makeProgram();
    Program* makeProgram(Block* b);

    // Statement factories:
    Statement* makeInput_stmt(Variable* Var);
    Statement* makePrint_stmt(Num_expr* Var);
    Statement* makeVar_def_stmt(Variable* Var, Num_expr* nexpr);
    Statement* makeIf_stmt(Bool_expr* condition, Block* thenBlock, Block* elseBlock);
    Statement* makeLoop_stmt(Bool_expr* condition, Block* toRepeat);

    // Num_expr factories:
    //Variable* findVariable(std::string nid);
    Variable* makeVariable(std::string nid);
    Variable* makeVariable(std::string nid, int initialValue);
    Num_expr* makeNumber(int value);
    Num_expr* makeNum_operator(Num_expr* l, Num_expr* r, Num_operator::opCode noc);

    // Bool_expr factories:
    Bool_expr* makeBool_comparator(Num_expr* l, Num_expr* r, Bool_comparator::symbCode nsc);
    Bool_expr* makeBool_const(int value);
    Bool_expr* makeBool_const(bool value);
    Bool_expr* makeBool_operator(Bool_expr* l, Bool_expr* r, Bool_operator::opCode noc);

private:
    std::vector<Composite*> node_list;
    std::vector<Variable*> var_table;
};

#endif // FACTORY_H
