// this is a combination of Recursive Descent and Predictive because we are calling functions and we check one token (LL(1)) for a good "prediction"

#include "Ast.h"
#include "Token.h"
#include <stdexcept>
#include "Parser.h"
// recursive descent parser with predictive (LL(1)) decisions

// the expression functions form a chain ordered by operator precedence, from weakest to strongest: || < && < ==/!= < </> < +/- < * / < unary < postfix < atoms
// each level calls the next one for its operands, so operators lower in the chain bind tighter

    std::unique_ptr<AstNode> Parser::parseOr() {
        auto left = parseAnd();
        while (tokens[position].token_type == OR) {
            std::string oper = tokens[position].lex;
            position++;
            auto right = parseAnd();
            left = std::make_unique<Binary_ExprNode>(oper, std::move(left), std::move(right));
        }
        return left;


        // left holds the partial result
        // each loop iteration wraps it in a new node (left-deep)
    }

    std::unique_ptr<AstNode> Parser::parseAnd() {
        auto left = parseEq();
        while (tokens[position].token_type == AND) {
            std::string oper = tokens[position].lex;
            position++;
            auto right = parseEq();
            left = std::make_unique<Binary_ExprNode>(oper, std::move(left), std::move(right));
        }
        return left;

    }


    std::unique_ptr<AstNode> Parser::parseEq() {
        auto left = parseCompar();
        while (tokens[position].token_type == EQ || tokens[position].token_type==NEQ) {
            std::string oper = tokens[position].lex;
            position++;
            auto right = parseCompar();
            left = std::make_unique<Binary_ExprNode>(oper, std::move(left), std::move(right));
        }
        return left;

    }

    std::unique_ptr<AstNode> Parser::parseCompar() {
        auto left = parseExpr1();
        while (tokens[position].token_type == LESSTHAN || tokens[position].token_type == GREATERTHAN) {
            std::string oper = tokens[position].lex;
            position++;
            auto right = parseExpr1();
            left = std::make_unique<Binary_ExprNode>(oper, std::move(left), std::move(right));
        }
        return left;

    }


    // parseExpr1: handles + and -, building a left-deep tree
    // parseExpr2: handles * and /, in 7*8+2 it consumes 7*8 as one node and stops at '+' which parseExpr1 then handles.
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
        if (tokens[position].token_type == MINUS || tokens[position].token_type== NOT || tokens[position].token_type == PLUS || tokens[position].token_type == INCREMENT || tokens[position].token_type == DECREMENT) {
             std::string op = tokens[position].lex;
            position++;
            auto operand = parseUn();
            return std::make_unique<UnNode>(op, std::move(operand));
        }
        return parsePostfix();
    }

// when we have an increment like this x++ +1
    std::unique_ptr<AstNode> Parser::parsePostfix() {
        auto left = parseExpr3();
        if (tokens[position].token_type == INCREMENT || tokens[position].token_type == DECREMENT) {
            std::string oper = tokens[position].lex;
            position++;
            left = std::make_unique<UnNode>(oper, std::move(left), true);
        }
        return left;

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
            auto e = parseOr(); // ex: 7+(7*8) for 7*8 we call the function and we restart with parseOr() this expression
            if (tokens[position].token_type==RPAREN) position++;
            return e;
        }
        throw std::runtime_error("number, identifier, LPAREN or RPAREN - expected");

    }

//we have to take every node to see how we parse everything

    Tok Parser::expect(TOKEN type) {
        if (tokens[position].token_type != type)
            throw std::runtime_error("unexpected token");
        position++;
        return tokens[position];
    }

    std::unique_ptr<AstNode> Parser::parseBlock() {
        expect(LBRACE);
        std::vector<std::unique_ptr<AstNode>> statements;
        while (tokens[position].token_type != RBRACE) {
            if (tokens[position].token_type == END_OF_FILE)
                throw std::runtime_error("'}' expected");
            statements.push_back(parseStatement());
        }


        return std::make_unique<BlockNode>(std::move(statements));

    }

