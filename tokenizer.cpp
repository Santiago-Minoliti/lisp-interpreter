#include <iostream>
#include <string>

#include "exceptions.h"
#include "tokenizer.h"
#include "separator.h"



std::vector<Token> Tokenizer::operator()(std::ifstream& fin) {

    // SEPARATION
    // The function accepts a std::ifstream already open, the function ends with the file still open.
    Separator separate; // separate is a function object that prepares the separated strings the tokenizer will create tokens of.
    separated_words = std::move(separate(fin));

    // TOKENIZATION
    // Now in separated_words we find the list of strings containing token candidates
    for(unsigned int i = 0; i < separated_words.size(); ++i) {
        std::string str = separated_words[i];
        if(str == Token::id_word_table[Token::OP]) {
            tokenStream.push_back(Token(Token::OP, Token::id_word_table[Token::OP]));
        } else if(str == Token::id_word_table[Token::CP]) {
            tokenStream.push_back(Token(Token::CP, Token::id_word_table[Token::CP]));
        } else if(str == Token::id_word_table[Token::BLOCK]) {
            tokenStream.push_back(Token(Token::BLOCK, Token::id_word_table[Token::BLOCK]));
        } else if(str == Token::id_word_table[Token::SET]) {
            tokenStream.push_back(Token(Token::SET, Token::id_word_table[Token::SET]));
        } else if(str == Token::id_word_table[Token::PRINT]) {
            tokenStream.push_back(Token(Token::PRINT, Token::id_word_table[Token::PRINT]));
        } else if(str == Token::id_word_table[Token::INPUT]) {
            tokenStream.push_back(Token(Token::INPUT, Token::id_word_table[Token::INPUT]));
        } else if(str == Token::id_word_table[Token::IF]) {
            tokenStream.push_back(Token(Token::IF, Token::id_word_table[Token::IF]));
        } else if(str == Token::id_word_table[Token::WHILE]) {
            tokenStream.push_back(Token(Token::WHILE, Token::id_word_table[Token::WHILE]));
        } else if(str == Token::id_word_table[Token::ADD]) {
            tokenStream.push_back(Token(Token::ADD, Token::id_word_table[Token::ADD]));
        } else if(str == Token::id_word_table[Token::SUB]) {
            tokenStream.push_back(Token(Token::SUB, Token::id_word_table[Token::SUB]));
        } else if(str == Token::id_word_table[Token::MUL]) {
            tokenStream.push_back(Token(Token::MUL, Token::id_word_table[Token::MUL]));
        } else if(str == Token::id_word_table[Token::DIV]) {
            tokenStream.push_back(Token(Token::DIV, Token::id_word_table[Token::DIV]));
        } else if(str == Token::id_word_table[Token::LT]) {
            tokenStream.push_back(Token(Token::LT, Token::id_word_table[Token::LT]));
        } else if(str == Token::id_word_table[Token::GT]) {
            tokenStream.push_back(Token(Token::GT, Token::id_word_table[Token::GT]));
        } else if(str == Token::id_word_table[Token::EQ]) {
            tokenStream.push_back(Token(Token::EQ, Token::id_word_table[Token::EQ]));
        } else if(str == Token::id_word_table[Token::AND]) {
            tokenStream.push_back(Token(Token::AND, Token::id_word_table[Token::AND]));
        } else if(str == Token::id_word_table[Token::OR]) {
            tokenStream.push_back(Token(Token::OR, Token::id_word_table[Token::OR]));
        } else if(str == Token::id_word_table[Token::NOT]) {
            tokenStream.push_back(Token(Token::NOT, Token::id_word_table[Token::NOT]));
        } else if(str == Token::id_word_table[Token::TRUE]) {
            tokenStream.push_back(Token(Token::TRUE, Token::id_word_table[Token::TRUE]));
        } else if(str == Token::id_word_table[Token::FALSE]) {
            tokenStream.push_back(Token(Token::FALSE, Token::id_word_table[Token::FALSE]));
        } else if(std::isalpha(str[0])) {
            tokenStream.push_back(Token(Token::VID, str));
        } else if((std::isdigit(str[0]) || str[0] == '-') && str != "-") {
            tokenStream.push_back(Token(Token::NUM, str));
        } else {
            std::stringstream tmp;
            tmp << "the string: \"" << str << "\" is not recognized.";
            throw tokenNotRecognized(tmp.str());
        }
    }

    // thanks to this we don't need a safeNext function in the parser, we can simply increment
    // the iterator, and at the time we will come across a premature end of the input stream of tokens
    // the parser will have been fed with the 'end of file' token in the place of the expected one,
    // therefore there will be an unexpected token error
    tokenStream.push_back(Token(Token::EF, Token::id_word_table[Token::EF]));

    return tokenStream;
}
