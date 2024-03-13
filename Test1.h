#ifndef TEST1_H
#define TEST1_H

#include "interpreter.h"

void test_factorial(std::vector<Variable*> var_table) {

    Block* bigBlock = new Block;

    Variable* Var_n = new Variable("n", 0, &var_table);
    var_table.push_back(Var_n);
    Statement* InputStmt = new Input_stmt(Var_n);
    bigBlock->push_back(InputStmt);

    Variable* Var_result = new Variable("result", 0, &var_table);
    var_table.push_back(Var_result);
    Num_expr* Num_1 = new Number(1);
    Statement* SetStmt = new Var_def_stmt(Var_result/*_toUse*/, Num_1);
    bigBlock->push_back(SetStmt);

    // Num_expr* Var_n_toUse = new Variable(Var_n);
    Num_expr* Num_0 = new Number(0);
    Bool_expr* ConditionStmt = new Bool_comparator(Var_n, Num_0, Bool_comparator::GT);
    Block* lilBlock = new Block;
        // Num_expr* Var_result_toUse = new Variable(Var_result);
        Num_expr* NumOperatorMul = new Num_operator(Var_result/*_toUse*/, Var_n/*_toUse*/, Num_operator::MUL);
        Statement* InnerSetStmt1 = new Var_def_stmt(Var_result, NumOperatorMul);
        lilBlock->push_back(InnerSetStmt1);

        Num_expr* NumOperatorSub = new Num_operator(Var_n/*_toUse*/, Num_1, Num_operator::SUB);
        Statement* InnerSetStmt2 = new Var_def_stmt(Var_n, NumOperatorSub);
        lilBlock->push_back(InnerSetStmt2);
    Statement* WhileStmt = new Loop_stmt(ConditionStmt, lilBlock);
    bigBlock->push_back(WhileStmt);

    Statement* PrintStmt = new Print_stmt(Var_result/*_toUse*/);
    bigBlock->push_back(PrintStmt);

    Program* p = new Program(bigBlock);
    p->interpret();
}

void test_PASS_BoolExpr(std::vector<Variable*> var_table) {

    Block* bigBlock = new Block;

    Variable* Var_n = new Variable("n", 0, &var_table);
    var_table.push_back(Var_n);
    Num_expr* Num_11 = new Number(11);
    Statement* SET_n_11 = new Var_def_stmt(Var_n, Num_11);
    bigBlock->push_back(SET_n_11);

    Variable* Var_d = new Variable("d", 0, &var_table);
    var_table.push_back(Var_d);
        Num_expr* Num_2 = new Number(2);
    Num_expr* DIV_n_2 = new Num_operator(Var_n, Num_2, Num_operator::DIV);
    Statement* SET_d_DIV = new Var_def_stmt(Var_d, DIV_n_2);
    bigBlock->push_back(SET_d_DIV);

    Variable* Var_isprime = new Variable("isprime", 0, &var_table);
    var_table.push_back(Var_isprime);
    Num_expr* Num_1 = new Number(1);
    Statement* SET_isprime_1 = new Var_def_stmt(Var_isprime, Num_1);
    bigBlock->push_back(SET_isprime_1);

    Bool_comparator* GT_d_1 = new Bool_comparator(Var_d, Num_1, Bool_comparator::GT);
    Block* lilBlock = new Block;
        Variable* Var_ires = new Variable("ires", 0, &var_table);
        var_table.push_back(Var_ires);
        Num_expr* DIV_n_d = new Num_operator(Var_n, Var_d, Num_operator::DIV);
        Statement* SET_ires_DIV = new Var_def_stmt(Var_ires, DIV_n_d);
        lilBlock->push_back(SET_ires_DIV);

        Variable* Var_nearest = new Variable("nearest", 0, &var_table);
        var_table.push_back(Var_nearest);
        Num_expr* MUL_ires_d = new Num_operator(Var_ires, Var_d, Num_operator::MUL);
        Statement* SET_nearest_MUL = new Var_def_stmt(Var_nearest, MUL_ires_d);
        lilBlock->push_back(SET_nearest_MUL);

        Variable* Var_remainder = new Variable("remainder", 0, &var_table);
        var_table.push_back(Var_remainder);
        Num_expr* SUB_n_nearest = new Num_operator(Var_n, Var_nearest, Num_operator::SUB);
        Statement* SET_remainder_SUB = new Var_def_stmt(Var_remainder, SUB_n_nearest);
        lilBlock->push_back(SET_remainder_SUB);

            Bool_expr* EQ_isprime_1 = new Bool_comparator(Var_isprime, Num_1, Bool_comparator::EQ);
            Num_expr* Num_0 = new Number(0);
            Bool_expr* EQ_remainder_0 = new Bool_comparator(Var_remainder, Num_0, Bool_comparator::EQ);
        Bool_expr* AND_EQ_EQ = new Bool_operator(EQ_isprime_1, EQ_remainder_0, Bool_operator::AND);
        Block* setBlock1 = new Block;
            Statement* SET_isprime_0 = new Var_def_stmt(Var_isprime, Num_0);
            setBlock1->push_back(SET_isprime_0);
        Block* setBlock2 = new Block;
            setBlock2->push_back(SET_isprime_1);
        Statement* IF_AND_setBlock1_setBlock2 = new If_stmt(AND_EQ_EQ, setBlock1, setBlock2);
        lilBlock->push_back(IF_AND_setBlock1_setBlock2);

        Num_expr* SUB_d_1 = new Num_operator(Var_d, Num_1, Num_operator::SUB);
        Statement* SET_d_SUB = new Var_def_stmt(Var_d, SUB_d_1);
        lilBlock->push_back(SET_d_SUB);

    Statement* WHILE_GT_lilBlock = new Loop_stmt(GT_d_1, lilBlock);
    bigBlock->push_back(WHILE_GT_lilBlock);

    Statement* PRINT_isprime = new Print_stmt(Var_isprime);
    bigBlock->push_back(PRINT_isprime);

    Program* p = new Program(bigBlock);
    p->interpret();
}

void test_PASS_BoolExpr_inputVersion(std::vector<Variable*> var_table) {

    Block* bigBlock = new Block;

    Variable* Var_n = new Variable("n", 0, &var_table);
    var_table.push_back(Var_n);
    Statement* INPUT_n = new Input_stmt(Var_n);
    bigBlock->push_back(INPUT_n);

    Variable* Var_d = new Variable("d", 0, &var_table);
    var_table.push_back(Var_d);
        Num_expr* Num_2 = new Number(2);
    Num_expr* DIV_n_2 = new Num_operator(Var_n, Num_2, Num_operator::DIV);
    Statement* SET_d_DIV = new Var_def_stmt(Var_d, DIV_n_2);
    bigBlock->push_back(SET_d_DIV);

    Variable* Var_isprime = new Variable("isprime", 0, &var_table);
    var_table.push_back(Var_isprime);
    Num_expr* Num_1 = new Number(1);
    Statement* SET_isprime_1 = new Var_def_stmt(Var_isprime, Num_1);
    bigBlock->push_back(SET_isprime_1);

    Bool_comparator* GT_d_1 = new Bool_comparator(Var_d, Num_1, Bool_comparator::GT);
    Block* lilBlock = new Block;
        Variable* Var_ires = new Variable("ires", 0, &var_table);
        var_table.push_back(Var_ires);
        Num_expr* DIV_n_d = new Num_operator(Var_n, Var_d, Num_operator::DIV);
        Statement* SET_ires_DIV = new Var_def_stmt(Var_ires, DIV_n_d);
        lilBlock->push_back(SET_ires_DIV);

        Variable* Var_nearest = new Variable("nearest", 0, &var_table);
        var_table.push_back(Var_nearest);
        Num_expr* MUL_ires_d = new Num_operator(Var_ires, Var_d, Num_operator::MUL);
        Statement* SET_nearest_MUL = new Var_def_stmt(Var_nearest, MUL_ires_d);
        lilBlock->push_back(SET_nearest_MUL);

        Variable* Var_remainder = new Variable("remainder", 0, &var_table);
        var_table.push_back(Var_remainder);
        Num_expr* SUB_n_nearest = new Num_operator(Var_n, Var_nearest, Num_operator::SUB);
        Statement* SET_remainder_SUB = new Var_def_stmt(Var_remainder, SUB_n_nearest);
        lilBlock->push_back(SET_remainder_SUB);

            Bool_expr* EQ_isprime_1 = new Bool_comparator(Var_isprime, Num_1, Bool_comparator::EQ);
            Num_expr* Num_0 = new Number(0);
            Bool_expr* EQ_remainder_0 = new Bool_comparator(Var_remainder, Num_0, Bool_comparator::EQ);
        Bool_expr* AND_EQ_EQ = new Bool_operator(EQ_isprime_1, EQ_remainder_0, Bool_operator::AND);
        Block* setBlock1 = new Block;
            Statement* SET_isprime_0 = new Var_def_stmt(Var_isprime, Num_0);
            setBlock1->push_back(SET_isprime_0);
        Block* setBlock2 = new Block;
            setBlock2->push_back(SET_isprime_1);
        Statement* IF_AND_setBlock1_setBlock2 = new If_stmt(AND_EQ_EQ, setBlock1, setBlock2);
        lilBlock->push_back(IF_AND_setBlock1_setBlock2);

        Num_expr* SUB_d_1 = new Num_operator(Var_d, Num_1, Num_operator::SUB);
        Statement* SET_d_SUB = new Var_def_stmt(Var_d, SUB_d_1);
        lilBlock->push_back(SET_d_SUB);

    Statement* WHILE_GT_lilBlock = new Loop_stmt(GT_d_1, lilBlock);
    bigBlock->push_back(WHILE_GT_lilBlock);

    Statement* PRINT_isprime = new Print_stmt(Var_isprime);
    bigBlock->push_back(PRINT_isprime);

    Program* p = new Program(bigBlock);
    p->interpret();
}

void test_PASS_SimpleStatement(std::vector<Variable*> var_table) {

    Block* b = new Block;

        Num_expr* Num_5 = new Number(5);
        Num_expr* Num_4 = new Number(4);
    Num_expr* MUL_5_4 = new Num_operator(Num_5, Num_4, Num_operator::MUL);
    Statement* PRINT_MUL = new Print_stmt(MUL_5_4);
    b->push_back(PRINT_MUL);

    Program* p = new Program(b);
    p->interpret();
}

void test_PASS_Fibonacci1_inputVersion(std::vector<Variable*> var_table) {

    Block* bigBlock = new Block;

    Variable* Var_n = new Variable("n", 0, &var_table);
    var_table.push_back(Var_n);
    Statement* INPUT_n = new Input_stmt(Var_n);
    bigBlock->push_back(INPUT_n);

    Num_expr* Num_0 = new Number(0);
    Bool_expr* EQ_n_1 = new Bool_comparator(Var_n, Num_0, Bool_comparator::EQ);
    Block* printBlock = new Block;
        Num_expr* Num_1 = new Number(1);
        Statement* PRINT_1 = new Print_stmt(Num_1);
        printBlock->push_back(PRINT_1);
    Block* midBlock = new Block;
        Variable* Var_fibzero = new Variable("fibzero", 0, &var_table);
        var_table.push_back(Var_fibzero);
        Statement* SET_fibzero_1 = new Var_def_stmt(Var_fibzero, Num_1);
        midBlock->push_back(SET_fibzero_1);

        Variable* Var_fibone = new Variable("fibone", 0, &var_table);
        var_table.push_back(Var_fibone);
        Statement* SET_fibone_1 = new Var_def_stmt(Var_fibone, Num_1);
        midBlock->push_back(SET_fibone_1);

        Variable* Var_i = new Variable("i", 0, &var_table);
        var_table.push_back(Var_i);
        Num_expr* Num_2 = new Number(2);
        Statement* SET_i_2 = new Var_def_stmt(Var_i, Num_2);
        midBlock->push_back(SET_i_2);

        Num_expr* ADD_n_1 = new Num_operator(Var_n, Num_1, Num_operator::ADD);
        Bool_expr* LT_i_ADD = new Bool_comparator(Var_i, ADD_n_1, Bool_comparator::LT);
        Block* lilBlock = new Block;
            Variable* Var_result = new Variable("result", 0, &var_table);
            var_table.push_back(Var_result);
            Num_expr* ADD_fibzero_fibone = new Num_operator(Var_fibzero, Var_fibone, Num_operator::ADD);
            Statement* SET_result_ADD = new Var_def_stmt(Var_result, ADD_fibzero_fibone);
            lilBlock->push_back(SET_result_ADD);

            Statement* SET_fibzero_fibone = new Var_def_stmt(Var_fibzero, Var_fibone);
            lilBlock->push_back(SET_fibzero_fibone);

            Statement* SET_fibone_result = new Var_def_stmt(Var_fibone, Var_result);
            lilBlock->push_back(SET_fibone_result);

            Num_expr* ADD_i_1 = new Num_operator(Var_i, Num_1, Num_operator::ADD);
            Statement* SET_i_ADD = new Var_def_stmt(Var_i, ADD_i_1);
            lilBlock->push_back(SET_i_ADD);

            Statement* PRINT_result = new Print_stmt(Var_result);
            lilBlock->push_back(PRINT_result);
        Statement* WHILE_LT_lilBlock = new Loop_stmt(LT_i_ADD, lilBlock);
        midBlock->push_back(WHILE_LT_lilBlock);
    Statement* IF_EQ_PRINT_IF = new If_stmt(EQ_n_1, printBlock, midBlock);
    bigBlock->push_back(IF_EQ_PRINT_IF);

    Program* p = new Program(bigBlock);
    p->interpret();
}

void test_PASS_Logarithm1_inputVersion(std::vector<Variable*> var_table) {

    Block* bigBlock = new Block;

    Variable* Var_a = new Variable("a", 0, &var_table);
    var_table.push_back(Var_a);
    Statement* INPUT_a = new Input_stmt(Var_a);
    bigBlock->push_back(INPUT_a);

    Variable* Var_b = new Variable("b", 0, &var_table);
    var_table.push_back(Var_b);
    Statement* INPUT_b = new Input_stmt(Var_b);
    bigBlock->push_back(INPUT_b);

    Variable* Var_result = new Variable("result", 0, &var_table);
    var_table.push_back(Var_result);
    Num_expr* Num_0 = new Number(0);
    Statement* SET_result_0 = new Var_def_stmt(Var_result, Num_0);
    bigBlock->push_back(SET_result_0);

    Num_expr* Num_1 = new Number(1);
    Bool_expr* GT_a_1 = new Bool_comparator(Var_a, Num_1, Bool_comparator::GT);
    Block* lilBlock = new Block;
        Num_expr* DIV_a_b = new Num_operator(Var_a, Var_b, Num_operator::DIV);
        Statement* SET_a_DIV = new Var_def_stmt(Var_a, DIV_a_b);
        lilBlock->push_back(SET_a_DIV);

        Num_expr* ADD_result_1 = new Num_operator(Var_result, Num_1, Num_operator::ADD);
        Statement* SET_result_ADD = new Var_def_stmt(Var_result, ADD_result_1);
        lilBlock->push_back(SET_result_ADD);
    Statement* WHILE_GT_lilBlock = new Loop_stmt(GT_a_1, lilBlock);
    bigBlock->push_back(WHILE_GT_lilBlock);

    Statement* PRINT_result = new Print_stmt(Var_result);
    bigBlock->push_back(PRINT_result);

    Program* p = new Program(bigBlock);
    p->interpret();
}

#endif // TEST1_H
