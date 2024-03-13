#include <iostream>

#include "exceptions.h"
#include "parser.h"


// op and cp functions are called whenever it needs to be absorbed necessarely an open or close parenthesis
void Parser::op() {
    if(tokenIterator->tag != Token::OP) {
        throw expectedObject("'('", tokenIterator->word);
    }
    ++tokenIterator;
}
void Parser::cp() {
    if(tokenIterator->tag != Token::CP) {
        throw expectedObject("')'", tokenIterator->word);
    }
    ++tokenIterator;
}

// this function occours when it needs to be checked a valid variable identifier because there is
// a Variable expected, not a general Num_expr
std::string Parser::vid() {
    if(tokenIterator->tag != Token::VID) {
        throw expectedObject("a valid variable identifier", tokenIterator->word);
    }
    std::string s = tokenIterator->word;
    ++tokenIterator;
    return s;
}


Program* Parser::buildProgram() {
    op();
    Program* p = factory->makeProgram(buildBlock());
    // now we check if the file ends after the cp of the initial (and main) block
    if(tokenIterator->tag != Token::EF) {
        throw std::runtime_error("the program must be a single block");
    }
    return p;
}


/// The next functions are called with tokenIterator standing on the keyword token
// this because the previews open parenthesis is expected

Block* Parser::buildBlock() {
    Block* b = factory->makeBlock();
    // A correct block is a BLOCK token followed by one or more correct statements, otherwise a single correct statement
    switch(tokenIterator->tag) {
    case Token::BLOCK:
        // if there is the BLOCK token we must expect an indefinite number of statements
        ++tokenIterator;
        do{
            // every correct statement begins with a "(" token
            op();
            switch(tokenIterator->tag) {
                case Token::INPUT:
                    b->push_back(buildInput_stmt());
                    break;
                case Token::PRINT:
                    b->push_back(buildPrint_stmt());
                    break;
                case Token::SET:
                    b->push_back(buildVar_def_stmt());
                    break;
                case Token::IF:
                    b->push_back(buildIf_stmt());
                    break;
                case Token::WHILE:
                    b->push_back(buildLoop_stmt());
                    break;
                default:
                    std::cout << "..." << std::endl;
                    throw expectedObject("'BLOCK' or a statement keyword", tokenIterator->word);
            }
        } while(tokenIterator->tag != Token::CP);
        ++tokenIterator;
        break;
    case Token::INPUT:
        b->push_back(buildInput_stmt());
        break;
    case Token::PRINT:
        b->push_back(buildPrint_stmt());
        break;
    case Token::SET:
        b->push_back(buildVar_def_stmt());
        break;
    case Token::IF:
        b->push_back(buildIf_stmt());
        break;
    case Token::WHILE:
        b->push_back(buildLoop_stmt());
        break;
    default:
        throw expectedObject("'BLOCK' or a statement keyword", tokenIterator->word);
    }
    return b;
}

Statement* Parser::buildInput_stmt() {
    ++tokenIterator;
    // after the keyword is expected a variable identifier
    Statement* s = factory->makeInput_stmt(factory->makeVariable(vid()));
    // then there is always the closed parenthesis
    cp();
    return s;
}

Statement* Parser::buildPrint_stmt() {
    ++tokenIterator;
    // after the keyword there must be a correct numerical expression (variable,  number or operator)
    Statement* s = factory->makePrint_stmt(buildNum_expr());
    cp();
    return s;
}

Statement* Parser::buildVar_def_stmt() {
    ++tokenIterator;
    Variable* v = factory->makeVariable(vid());
    Statement* s = factory->makeVar_def_stmt(v, buildNum_expr());
    cp();
    return s;
}

Statement* Parser::buildIf_stmt() {
    ++tokenIterator;
    Bool_expr* b = buildBool_expr();
    op();
    Block* b1 = buildBlock();
    op();
    Block* b2 = buildBlock();
    cp();
    return factory->makeIf_stmt(b, b1, b2);
}

Statement* Parser::buildLoop_stmt() {
    ++tokenIterator;
    Bool_expr* b = buildBool_expr();
    op();
    Block* b1 = buildBlock();
    cp();
    return factory->makeLoop_stmt(b, b1);
}

Num_expr* Parser::buildNum_operator(Num_operator::opCode oc) {
    ++tokenIterator;
    Num_expr* ne1 = buildNum_expr();
    Num_expr* n = factory->makeNum_operator(ne1, buildNum_expr(), oc);
    cp();
    return n;
}

Bool_expr* Parser::buildBool_comparator(Bool_comparator::symbCode sc) {
    ++tokenIterator;
    Num_expr* ne1 = buildNum_expr();
    Bool_expr* b = factory->makeBool_comparator(ne1, buildNum_expr(), sc);
    cp();
    return b;
}

Bool_expr* Parser::buildBool_operator(Bool_operator::opCode oc) {
    ++tokenIterator;
    Bool_expr* be1 = buildBool_expr();
    Bool_expr* b = factory->makeBool_operator(be1, buildBool_expr(), oc);
    cp();
    return b;
}

Bool_expr* Parser::buildBool_NOTstatement() {
    ++tokenIterator;

    // plhldr is a placeholder meant not to create another abstract class of unary bool operators:
    // we manage with the NOT operator as a binary one but then, in its interpret function it will
    // be using only the left operand as the only one
    Bool_expr* plhldr = new Bool_const(1);

    Bool_expr* b = factory->makeBool_operator(buildBool_expr(), plhldr, Bool_operator::NOT);
    delete plhldr;
    cp();
    return b;
}

/// The next functions are called with tokenIterator standing on the open parenthesis if there is one,
/// elsewise on the only token that the whole Num_expr consists in
// this because it isn't mandatory an open parenthesis, we could expect a constant or a variable

Num_expr* Parser::buildNum_expr() {
    Num_expr* v = nullptr;
    switch(tokenIterator->tag) {
    case Token::VID:
        v = factory->makeVariable(tokenIterator->word);
        ++tokenIterator;
        return v;
    case Token::NUM:
        v = factory->makeNumber(std::stoi(tokenIterator->word));
        ++tokenIterator;
        return v;
    case Token::OP:
        ++tokenIterator;
        switch(tokenIterator->tag) {
        case Token::ADD:
            return buildNum_operator(Num_operator::ADD);
        case Token::SUB:
            return buildNum_operator(Num_operator::SUB);
        case Token::MUL:
            return buildNum_operator(Num_operator::MUL);
        case Token::DIV:
            return buildNum_operator(Num_operator::DIV);
        default:
            throw expectedObject("a numerical operator keyword", tokenIterator->word);
        }
    default:
        throw expectedObject("a numerical expression", tokenIterator->word);
    }
}

Bool_expr* Parser::buildBool_expr() {
    switch(tokenIterator->tag) {
    case Token::TRUE:
        {
            Bool_expr* be = factory->makeBool_const(true);
            ++tokenIterator;
            return be;
        }
    case Token::FALSE:
        {
            Bool_expr* be = factory->makeBool_const(false);
            ++tokenIterator;
            return be;
        }
    case Token::OP:
        ++tokenIterator;
        switch(tokenIterator->tag) {
        case Token::GT:
            return buildBool_comparator(Bool_comparator::GT);
        case Token::LT:
            return buildBool_comparator(Bool_comparator::LT);
        case Token::EQ:
            return buildBool_comparator(Bool_comparator::EQ);
        case Token::AND:
            return buildBool_operator(Bool_operator::AND);
        case Token::OR:
            return buildBool_operator(Bool_operator::OR);
        case Token::NOT:
            return buildBool_NOTstatement();
        default:
            throw expectedObject("a boolean comparator or operator keyword", tokenIterator->word);

        }
    default:
        throw expectedObject("a boolean expression", tokenIterator->word);
    }
}
