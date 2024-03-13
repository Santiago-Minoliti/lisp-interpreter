#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>


 /** INTERPRETER:
  *
  *  Composite is an abstract class, every object deriving from this is part of a composite hierarchy
  *  described in the UML class table: "lispInterpreterComposite1.dia"
  *  Composite class impose the "interpret" method to its descendants, according to the interpreter pattern.
  *
  *  The first "interpret" method that is called (by the main) is Program::interpret, despite "interpret"
  *  method is an int, nothing useful is returned by Statements, Blocks or Program, the type is only meaningful
  *  for low level nodes like boolean or numerical expression.
  *
  */


class Composite {
public:
    virtual ~Composite() {};
    virtual int interpret() = 0;
};

class Statement : public Composite {
public:
    virtual ~Statement() {};
    virtual int interpret() = 0;
};

class Num_expr : public Composite {
public:
    virtual ~Num_expr() {};
    virtual int interpret() = 0;
};

class Bool_expr : public Composite {
public:
    virtual ~Bool_expr() {};
    virtual int interpret() = 0;
};

class Block : public Composite {
public:
    Block() = default;
    ~Block() {};
    Block& push_back(Statement* s);
    int interpret() override;
private:
    std::vector<Statement*> statement_list;
};

class Variable : public Num_expr {
public:
    Variable() = default;
    Variable(std::string nid, int nvalue, std::vector<Variable*>* vtp) : id{ nid }, value{ nvalue }, var_table_ptr{ vtp }, valid{ false } {}
    Variable(const Variable& other) : id{ other.id }, value{ other.value } {}
    ~Variable() {}
//    Variable& operator=(const Variable& other);
//    friend std::ostream& operator<<(std::ostream& os, const Variable& v);
    int interpret() override;

    std::string id;
    int value;
    std::vector<Variable*>* var_table_ptr;
    bool valid;
};

class Program : public Composite {
public:
    Program(Block* nb) : b{ nb } {}
    ~Program() {};
    int interpret() override;
private:
    Block* b;
};

class Input_stmt : public Statement {
public:
    Input_stmt(Variable* ts) : toSet(ts) {}
    ~Input_stmt() {};
//    Input_stmt& operator=(const Input_stmt& other);
    int interpret() override;
private:
    Variable* toSet;
};

class Print_stmt : public Statement {
public:
    Print_stmt(Num_expr* tp) : toPrint{ tp } {}
    ~Print_stmt() {};
//    Print_stmt& operator=(const Print_stmt& other);
    int interpret() override;
private:
    Num_expr* toPrint;
};

class Var_def_stmt : public Statement {
public:
    Var_def_stmt(Variable* ts, Num_expr* vv) : toSet{ ts }, varValue{ vv } {}
    ~Var_def_stmt() {};
//    Var_def_stmt& operator=(const Var_def_stmt& other);
    int interpret() override;
private:
    Variable* toSet;
    Num_expr* varValue;
};

class If_stmt : public Statement {
public:
    If_stmt(Bool_expr* c, Block* ts, Block* es) : condition{ c }, then_stmt{ ts }, else_stmt{ es } {}
    ~If_stmt() {};
//    If_stmt& operator=(const If_stmt& other);
    int interpret() override;
private:
    Bool_expr* condition;
    Block* then_stmt;
    Block* else_stmt;
};

class Loop_stmt : public Statement {
public:
    Loop_stmt(Bool_expr* c, Block* tr) : condition{ c }, toRepeat{ tr } {}
    ~Loop_stmt() {};
//    Loop_stmt& operator=(const Loop_stmt& other);
    int interpret() override;
private:
    Bool_expr* condition;
    Block* toRepeat;
};

class Number : public Num_expr {
public:
    Number(int v) : value{ v } {}
//    Number(const Number& other) : value{ other.value } {}
    ~Number() {};
//    Number& operator=(const Number& other) : value{ other.value } {}
    int interpret() override;
private:
    int value;
};

class Num_operator : public Num_expr {
public:
    enum opCode { ADD, SUB, MUL, DIV };
    Num_operator(Num_expr* l, Num_expr* r, Num_operator::opCode noc) : left{ l }, right{ r }, oc{ noc } {}
//    Num_operator(const Num_operator& other) : oc(other.oc)
    ~Num_operator() {};
//    Num_operator& operator=(const Num_operator& other);
    int interpret() override;
private:
    Num_expr* left;
    Num_expr* right;
    Num_operator::opCode oc;
};

class Bool_comparator : public Bool_expr {
public:
    enum symbCode { GT, LT, EQ };
    Bool_comparator(Num_expr* l, Num_expr* r, Bool_comparator::symbCode nsc) : left{ l }, right{ r }, sc{ nsc } {}
    ~Bool_comparator() {};
    int interpret() override;
private:
    Num_expr* left;
    Num_expr* right;
    Bool_comparator::symbCode sc;
};

class Bool_const : public Bool_expr {
public:
    Bool_const(int v) : value{ v } {}
    ~Bool_const() {};
    int interpret() override;
private:
    int value;
};

class Bool_operator : public Bool_expr {
public:
    enum opCode { AND, OR, NOT };
    Bool_operator(Bool_expr* l, Bool_expr* r, Bool_operator::opCode noc) : left{ l }, right{ r }, oc{ noc } {}
    ~Bool_operator() {};
    int interpret() override;
private:
    Bool_expr* left;
    Bool_expr* right;
    Bool_operator::opCode oc;
};

#endif // INTERPRETER_H
