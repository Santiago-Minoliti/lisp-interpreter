#ifndef TOKEN_H
#define TOKEN_H

#include <string>

 /** TOKENS:
  *
  *  Tokens are data structures that contain a tag and a word, the tag codifies the kind of token and the
  *  word carries the corresponding string in the lisp-like language.
  *
  *  The only different token is the one with tag 22, and word always "end of file", this exists in order
  *  to get every time a token when in parsing we ask for the next token in the token stream, to manage
  *  ourselves the errors given by a unexpected end of the program.
  *
  */


struct Token {
    static constexpr int OP = 0; // Open Parenthesis
    static constexpr int CP = 1; // Closed Parenthesis
    static constexpr int BLOCK = 2;
    static constexpr int SET = 3;
    static constexpr int PRINT = 4;
    static constexpr int INPUT = 5;
    static constexpr int IF = 6;
    static constexpr int WHILE = 7;
    static constexpr int ADD = 8;
    static constexpr int SUB = 9;
    static constexpr int MUL = 10;
    static constexpr int DIV = 11;
    static constexpr int NUM = 12;
    static constexpr int VID = 13;
    static constexpr int LT = 14;
    static constexpr int GT = 15;
    static constexpr int EQ = 16;
    static constexpr int AND = 17;
    static constexpr int OR = 18;
    static constexpr int NOT = 19;
    static constexpr int TRUE = 20;
    static constexpr int FALSE = 21;
    static constexpr int EF = 22;

    static constexpr const char* id_word_table[]{"(",")","BLOCK","SET","PRINT","INPUT","IF","WHILE","ADD","SUB","MUL","DIV","NUM","VID","LT","GT","EQ","AND","OR","NOT","TRUE","FALSE","end of file"};

    Token(int t, const std::string w) : tag{ t }, word{ w } {}
    Token(const Token& other) : tag{ other.tag }, word{ other.word } {}

    bool operator==(Token other) const;

    int tag;
    std::string word;
};

std::ostream& operator<<(std::ostream& os, const Token& t);

#endif // TOKEN_H
