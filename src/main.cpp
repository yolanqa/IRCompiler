#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include <vector>

int main() {
    Lexer lexer{"while(x==5) {p++;}"};
    try {
        std::vector<Tok> tokens = lexer.tokenize();
        for (const Tok& tk : tokens)
            std::cout<<tk.lex<<std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Lexer error: " << e.what() << std::endl;
    }

}