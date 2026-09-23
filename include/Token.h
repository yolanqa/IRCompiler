
#ifndef IRCOMPILER_TOKEN_H
#define IRCOMPILER_TOKEN_H
#include <iostream>
#include <string>


enum TOKEN {
    LPAREN, RPAREN,
    LBRACE, RBRACE,
    COMMA, PLUS, INCREMENT, MINUS,
    STAR, SLASH, EQUAL, EQ,
    NUMBER, IDENTIFIER,
    STRING, INT, RETURN, FLOAT, VOID, BOOL, WHILE, IF, ELSE,
    AND, OR, NOT, XOR, FUNC, SEMICOL,
    LESSTHAN, GREATERTHAN, END_OF_FILE
};

struct Tok {
    std::string lex;
    size_t col;
    size_t lin;
    TOKEN token_type;
};

#endif //IRCOMPILER_TOKEN_H