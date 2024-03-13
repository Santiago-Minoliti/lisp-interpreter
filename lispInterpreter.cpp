#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "exceptions.h"
#include "tokenizer.h"
#include "separator.h"
#include "extractor.h"
#include "interpreter.h"
#include "factory.h"
#include "parser.h"

int main(int argc, char* argv[])
{

    // --------------     SETUP    -------------------

    std::string fileToOpen;

    /**
     *  I have had problems in compiling properly in my pc and I cannot run the program with the arguments
     *  in line of code in the terminal, so, obviously it is still possible to do if someone compiles again
     *  the project, but in order to try the program myself I had to add the possibility to make it work.
     */
    if(argc == 1) {
        fileToOpen = "inputFile.txt";
    } else if(argc == 2) {
        fileToOpen = argv[1];
    } else {
        std::cerr << "(ERROR in setup: not the right number of terminal arguments)" << std::endl;
        std::cout << argv[0];
        return EXIT_FAILURE;
    }

    Factory* fctr = new Factory();
    if(fctr == NULL) {
        std::cerr << "Not enough memory" << std::endl;
        return EXIT_FAILURE;
    }


    // -------------- FILE OPENING -------------------

    std::ifstream fin;
    try{
        fin.open(fileToOpen, std::ios::in);
    } catch(std::exception e) {
        std::cerr << "ERROR: Impossible to read the file." << std::endl;
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
    if(!fin) {
        std::cerr << "ERROR: Impossible to read the file." << std::endl;
        return EXIT_FAILURE;
    }


    // -------------- TOKENIZATION -------------------
    Tokenizer tokenize;
    std::vector<Token> tokenStream;
    try{
       tokenStream = std::move(tokenize(fin));
    } catch(std::runtime_error e) {
        std::cerr << "(ERROR in tokenization: " << e.what() << ")" << std::endl;
        return EXIT_FAILURE;
    }
    // Now in the std::vector tokenStream there is the stream of token ready
    fin.close();


    // --------------    PARSING   -------------------

    Parser p(tokenStream.begin(), tokenStream.end(), fctr);
    Program* _program;
    try {
        _program = p.buildProgram();
    } catch(expectedObject e) {
        std::cerr << "(ERROR in parsing: expected " << e.what() << " before '" << e.following << "' token)" << std::endl;
        return EXIT_FAILURE;
    } catch(std::runtime_error e) {
        std::cerr << "(ERROR in parsing: " << e.what() << ")" << std::endl;
        return EXIT_FAILURE;
    }

    // --------------    RUNNING   -------------------

    try {
        _program->interpret();
    } catch(std::runtime_error e) {
        std::cerr << "(ERROR in running: " << e.what() << ")" << std::endl;
        return EXIT_FAILURE;
    }

    // --------------    EXITING   -------------------
    delete fctr;

    return EXIT_SUCCESS;
}
