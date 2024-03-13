#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <fstream>

#include "token.h"


 /** TOKENIZER:
  *
  *  Tokenizer is a function object whose purpose is to observe the list of separated words of the file
  *  and to create the stream of token on that, then return it to the caller.
  *  Normally the caller is the main function in tokenization phase.
  *
  *  Tokenizer as the second purpose to abort the process if some lexical error comes out.
  *
  */


class Tokenizer{
public:
    std::vector<Token> operator()(std::ifstream& inFile); // Method that fills the inTokens vector with the tokens found in the file
private:
    std::vector<std::string> separated_words;
    std::vector<Token> tokenStream;
};

#endif // TOKENIZER_H
