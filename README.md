# IRCompiler
A compiler for a small custom programming language, written in C++, targeting LLVM IR.

## Summary
IRCompiler converts source code written in a minimal language into LLVM Intermediate Representation (IR). This IR is then processed by the LLVM toolchain to produce native assembly and an executable binary. The project handles the entire front-end compilation process—including lexical analysis, parsing, semantic analysis, and code generation—and leverages LLVM for optimization and final machine code generation.

## Compilation Stages

The compiler processes source code in five stages:

Lexical analysis (Lexer) — converts raw source text into a stream of tokens (identifiers, keywords, literals, operators, punctuators).
Parsing (Parser) — consumes the token stream and builds an Abstract Syntax Tree (AST) representing the program's structure.
Semantic analysis — walks the AST to resolve scopes, build symbol tables, and perform type checking, flagging invalid programs before code generation.
Code generation — walks the verified AST and emits LLVM IR using the LLVM C++ API.
Compilation to native code — the generated IR is passed to the LLVM toolchain (llc/clang), which handles optimization and produces assembly and an executable binary.
