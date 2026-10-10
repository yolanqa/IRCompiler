#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include <vector>

int main() {
    try {
        Lexer lexer{"x++ +1 == 4|| 4<6"};
        std::vector<Tok> tokens = lexer.tokenize();


        for (const Tok& tk : tokens)
           std::cout<<tk.lex<<std::endl;

        Parser parser{tokens};
        std::unique_ptr<AstNode> tree = parser.parseOr();

        std::cout << "Parsed OK" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Lexer error: " << e.what() << std::endl;
    }
    return 0;
}