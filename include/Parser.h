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

    std::unique_ptr<AstNode> parseExpr1();

    std::unique_ptr<AstNode> parseExpr2();
    std::unique_ptr<AstNode> parseUn();
    std::unique_ptr<AstNode> parseExpr3();
};

#endif //IRCOMPILER_PARSER_H