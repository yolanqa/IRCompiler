// this is a combination of Recursive Descent and Predictive because we are recalling functions and we verify a token (LL(1)) for a good "prediction"

#include "Ast.h"
#include "Token.h"
#include <stdexcept>
#include "Parser.h"
// recursive descent parser with predictive (LL(1)) decisions



    //parseExpr1 is for when we have an expression with + or - and we have to separate it in the ast
    //parseExpr2 is for when we have a * or / expression - for example 7*8+2 we take the left part separate from the +2
    //parseExpr3 when we have a single atom and we create a node


    //when we make the ast the order matters

    Parser::Parser(const std::vector<Tok> &tokens): tokens(tokens) {}

    std::unique_ptr<AstNode> Parser::parseExpr1(){

        auto left = parseExpr2();
        while(tokens[position].token_type == PLUS || tokens[position].token_type == MINUS){


            std::string oper = tokens[position].lex;
            position++;
            auto right = parseExpr2();


            left = std::make_unique<Binary_ExprNode>(oper, std::move(left),std::move(right));}

        return left;
    }
    std::unique_ptr<AstNode> Parser::parseExpr2(){

        auto left = parseUn();
        while (tokens[position].token_type == STAR || tokens[position].token_type==SLASH){
            std::string oper = tokens[position].lex;
            position ++;
            auto right = parseUn();

            left = std::make_unique<Binary_ExprNode>(oper, std::move(left), std::move(right));}
        return left;

    }
    std::unique_ptr<AstNode> Parser::parseUn() {
        if (tokens[position].token_type == MINUS || tokens[position].token_type== NOT) {
             std::string op = tokens[position].lex;
            position++;
            auto operand = parseUn();
            return std::make_unique<UnNode>(op, std::move(operand));
        }
        return parseExpr3();

//todo
// continue w x++ or ++x and ! is separte from != ---- Token.h, exception for Rparen

    }
    std::unique_ptr<AstNode> Parser::parseExpr3(){

        if(tokens[position].token_type == NUMBER) {
            auto val = tokens[position].lex;
            position++;
            return std::make_unique<NumberNode>(val);
        }

        if (tokens[position].token_type == IDENTIFIER) {
            auto val = tokens[position].lex;
            position++;
            return std::make_unique<IdentifierNode>(val);
        }

        if (tokens[position].token_type == LPAREN) {
            position++;
            auto e = parseExpr1(); // ex: 7+(7*8) for 7*8 we call the function to revaluate this expression
            if (tokens[position].token_type==RPAREN) position++;
            return e;
        }
        throw std::runtime_error("number, identifier, LPAREN or RPAREN - expected");



    }

