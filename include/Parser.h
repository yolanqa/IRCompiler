// this is a combination of Recursive Descent and Predictive because we are recalling functions and we verify a token (LL(1)) for a good "prediction"
#ifndef IRCOMPILER_PARSER_H
#define IRCOMPILER_PARSER_H
#include "Ast.h"
#include "Token.h"
#include <stdexcept>
class Parser {
    std::vector<Tok> tokens;
    size_t position =0;

public:
    explicit Parser(const std::vector<Tok> &tokens);

    std::unique_ptr<AstNode> parseOr();
    std::unique_ptr<AstNode> parseAnd();
    std::unique_ptr<AstNode> parseEq();
    std::unique_ptr<AstNode> parseCompar();




    std::unique_ptr<AstNode> parseExpr1();

    std::unique_ptr<AstNode> parseExpr2();
    std::unique_ptr<AstNode> parseUn();
    std::unique_ptr<AstNode> parsePostfix();
    std::unique_ptr<AstNode> parseExpr3();
    Tok expect(TOKEN type);
    std::unique_ptr<AstNode> parseStatement();
    std::unique_ptr<AstNode> parseBlock();
};

#endif //IRCOMPILER_PARSER_H