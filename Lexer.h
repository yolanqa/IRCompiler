
#ifndef IRCOMPILER_LEXER_H
#define IRCOMPILER_LEXER_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Token.h"

class Lexer {
    size_t position;
    std::string text;
    std::vector<Tok> tokens;
    std::unordered_map<std::string, TOKEN> keywords;
public:
    Lexer(std::string text);
    Tok scannerLex();
    std::vector<Tok> tokenize();
};

#endif //IRCOMPILER_LEXER_H