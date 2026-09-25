
#ifndef IRCOMPILER_AST_H
#define IRCOMPILER_AST_H
#include<vector>
#include <memory>
#include <string>

class NumberNode;
class IdentifierNode;
class Binary_ExprNode;
class CallExprNode;
class BlockNode;
class DeclVar;
class DeclFunct;
class Assign;
class ReturnNode;
class IfNode;
class WhileNode;
//using visitor pattern for a verification -  semantic analysis
struct Visitor {
    virtual void visit (NumberNode& nod)=0;
    virtual void visit (IdentifierNode& nod)=0;
    virtual void visit (Binary_ExprNode& nod)=0;
    virtual void visit (CallExprNode& nod) = 0;
    virtual void visit (BlockNode& nod) = 0;
    virtual void visit (DeclVar& nod) = 0;
    virtual void visit (DeclFunct& nod) = 0;
    virtual void visit (Assign& nod) = 0;
    virtual void visit (ReturnNode& nod) = 0;
    virtual void visit (IfNode& nod) = 0;
    virtual void visit (WhileNode& nod) = 0;


    virtual ~Visitor() = default;
};
class AstNode {
public:
    AstNode() = default;

    virtual void accept(Visitor& vis )=0;
    virtual ~AstNode(){};
};

class BlockNode:public AstNode {
public:
    std::vector<std::unique_ptr<AstNode>> text;

    explicit BlockNode(std::vector<std::unique_ptr<AstNode>> text): text(std::move(text)) {}
    void accept(Visitor &vis) override{vis.visit(*this);}
};

class DeclVar:public AstNode {
public:
    std::unique_ptr<AstNode> variable_init;
    std::string name;
    std::string type;

    DeclVar(std::unique_ptr<AstNode> variable_init, const std::string &name, const std::string &type): variable_init(std::move(variable_init)),name(name),type(type) {}
    void accept(Visitor& vis) override{ vis.visit(*this);}
};

//declarare
struct Parameter {
    std::string type;
    std::string name;
};


class DeclFunct:public AstNode {
public:
    std::unique_ptr<BlockNode> function_body;
    std::string return_type;
    std::string name;
    std::vector<Parameter> param;

    DeclFunct(std::unique_ptr<BlockNode> function_body, std::string return_type, const std::string &name, std::vector<Parameter> param)
        : function_body(std::move(function_body)), return_type(std::move(return_type)), name(name), param(std::move(param)) {}
    void accept(Visitor& vis) override{ vis.visit(*this);}
};


class Assign:public AstNode {
public:

    std::unique_ptr<AstNode> value;
    std::string var;

    Assign(std::unique_ptr<AstNode> value, const std::string &var): value(std::move(value)),var(var) {}
    void accept(Visitor& vis) override{ vis.visit(*this);}
};

class Binary_ExprNode:public AstNode{
public:
    std::string operation;
    std::unique_ptr<AstNode> right;
    std::unique_ptr<AstNode> left;

    Binary_ExprNode(const std::string &operation,std::unique_ptr<AstNode> right,std::unique_ptr<AstNode> left): operation(operation), right(std::move(right)), left(std::move(left)) {}

    void accept(Visitor& vis) override{ vis.visit(*this);}
};

class NumberNode:public AstNode{
public:
    std::string value;

    explicit NumberNode(const std::string &value): value(value) {}

    void accept(Visitor& vis) override{ vis.visit(*this);}

};

class IdentifierNode:public AstNode {
public:
    std::string name;

    explicit IdentifierNode(const std::string &name): name(name) {}

    void accept(Visitor& vis) override{ vis.visit(*this);}

};
//apel
class CallExprNode:public AstNode {
public:
    std::string function_name;
    std::vector<std::unique_ptr<AstNode>> arg;

    CallExprNode(const std::string &function_name, std::vector<std::unique_ptr<AstNode>> arg): function_name(function_name), arg(std::move(arg)) {}

    void accept(Visitor& vis) override{ vis.visit(*this);}

};

class ReturnNode:public AstNode{
public:
    std::unique_ptr<AstNode> value;

    explicit ReturnNode(std::unique_ptr<AstNode> value): value(std::move(value)){}

    void accept(Visitor& vis) override{ vis.visit(*this);}


};

class IfNode:public AstNode {
public:

    std::unique_ptr<AstNode> condition;
    std::unique_ptr<BlockNode> thenblock;
    std::unique_ptr<BlockNode> elseblock; //or null if we don't have an else branch
    IfNode(std::unique_ptr<AstNode> condition, std::unique_ptr<BlockNode> thenblock, std::unique_ptr<BlockNode> elseblock): condition(std::move(condition)), thenblock(std::move(thenblock)), elseblock(std::move(elseblock) ){}

    void accept(Visitor& vis) override{ vis.visit(*this);}


};

class WhileNode:public AstNode {
public:
    std::unique_ptr<AstNode> condition;
    std::unique_ptr<BlockNode> body;

    WhileNode(std::unique_ptr<AstNode> condition, std::unique_ptr<BlockNode> body): condition(std::move(condition)), body(std::move(body)) {
    }


    void accept(Visitor& vis) override{ vis.visit(*this);}
};




#endif //IRCOMPILER_AST_H