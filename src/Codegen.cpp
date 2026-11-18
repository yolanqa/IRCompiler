
#include <ios>
#include <bits/ios_base.h>

#include "Ast.h"



llvm::Value* NumberNode::codegen() {

    int val = std::stoi(value);
    return llvm::ConstantInt::get(builder.getInt64Ty(), val);
}

llvam::Value* BinaryNode::codegen() {

    //kids

    llvm:Value* l = left->codegen();
    llvm:Value* r = right->codegen();

    if(l && r) {
        throw std::runtime_error("Cannot codegen binary operators");
    }

    if (op == "-")
        return builder.CreateSub(l, r, "subtmp");
    else if (op == "+")
        return builder.CreateAdd(l, r, "addtmp");
    else if (op == "*")
        return builder.CreateMul(l, r, "multmp");

    throw std::runtime_error("Cannot codegen binary operators");
}