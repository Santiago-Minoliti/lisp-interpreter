#include "factory.h"

// the effective "clear function" lays within the destructor
Factory::~Factory() {
    for(Composite* c : node_list) {
        delete c;
    }
}

// Block and Program factories:
Block* Factory::makeBlock() {
    Block* b = new Block();
    node_list.push_back(b);
    return b;
}

Program* Factory::makeProgram(Block* b) {
    Program* p = new Program(b);
    node_list.push_back(p);
    return p;
}

// Statement factories:
Statement* Factory::makeInput_stmt(Variable* Var) {
    Statement* s = new Input_stmt(Var);
    node_list.push_back(s);
    return s;
}
Statement* Factory::makePrint_stmt(Num_expr* toPrint) {
    Statement* s = new Print_stmt(toPrint);
    node_list.push_back(s);
    return s;
}
Statement* Factory::makeVar_def_stmt(Variable* Var, Num_expr* nexpr) {
    Statement* s = new Var_def_stmt(Var, nexpr);
    node_list.push_back(s);
    return s;
}
Statement* Factory::makeIf_stmt(Bool_expr* condition, Block* thenBlock, Block* elseBlock) {
    Statement* s = new If_stmt(condition, thenBlock, elseBlock);
    node_list.push_back(s);
    return s;
}
Statement* Factory::makeLoop_stmt(Bool_expr* condition, Block* toRepeat) {
    Statement* s = new Loop_stmt(condition, toRepeat);
    node_list.push_back(s);
    return s;
}

// Num_expr factories:
Variable* Factory::makeVariable(std::string nid) {

    // we don't want to create twice a variable
    for(Variable* v : var_table) {
        if(v->id == nid) return v;
    }

    Variable* v = new Variable(nid, 0, &var_table);
    // as soon as the variable is created, is introduced in the symbol table
    var_table.push_back(v);
    node_list.push_back(v);
    return v;
}
Num_expr* Factory::makeNumber(int value) {
    Num_expr* n = new Number(value);
    node_list.push_back(n);
    return n;
}
Num_expr* Factory::makeNum_operator(Num_expr* l, Num_expr* r, Num_operator::opCode noc) {
    Num_expr* n = new Num_operator(l, r, noc);
    node_list.push_back(n);
    return n;
}

// Bool_expr factories:
Bool_expr* Factory::makeBool_comparator(Num_expr* l, Num_expr* r, Bool_comparator::symbCode nsc) {
    Bool_expr* b = new Bool_comparator(l, r, nsc);
    node_list.push_back(b);
    return b;
}
Bool_expr* Factory::makeBool_const(bool value) {
    Bool_expr* b = new Bool_const(static_cast<int>(value));
    node_list.push_back(b);
    return b;
}
Bool_expr* Factory::makeBool_operator(Bool_expr* l, Bool_expr* r, Bool_operator::opCode noc) {
    Bool_expr* b = new Bool_operator(l, r, noc);
    node_list.push_back(b);
    return b;
}

