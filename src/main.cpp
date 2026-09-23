#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include <vector>

int main() {
    Lexer lexer{"while(x==5) {p++; c--}"};
    std::vector<Tok> tokens = lexer.tokenize();
    for (const Tok& tk : tokens)
        std::cout<<tk.lex<<std::endl;
}