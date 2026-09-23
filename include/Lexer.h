
#ifndef IRCOMPILER_LEXER_H
#define IRCOMPILER_LEXER_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include "Token.h"

class Lexer {
    size_t position;
    std::string text;
    std::vector<Tok> tokens;
    std::unordered_map<std::string, TOKEN> keywords = {
        {"if", IF}, {"else", ELSE}, {"while", WHILE}, {"return", RETURN},{"func", FUNC}, {"int", INT}, {"void", VOID}, {"bool", BOOL}, {"float", FLOAT}};
    char peek();
public:
    Lexer(std::string text);
    Tok scannerLex();
    std::vector<Tok> tokenize();
};

#endif //IRCOMPILER_LEXER_H