# IRCompiler
A compiler for a small custom programming language, written in C++, targeting LLVM IR.

## Summary
IRCompiler converts source code written in a minimal language into LLVM Intermediate Representation (IR). This IR is then processed by the LLVM toolchain to produce native assembly and an executable binary. The project handles the entire front-end compilation process—including lexical analysis, parsing, semantic analysis, and code generation—and leverages LLVM for optimization and final machine code generation.

## Compilation Stages

The compiler processes source code in five stages:

Lexical analysis (Lexer) — converts raw source text into a stream of tokens (identifiers, keywords, literals, operators, punctuators).
Parsing (Parser) — a hand-written recursive descent parser that consumes the token stream and builds an Abstract Syntax Tree (AST) representing the program's structure.
Semantic analysis — walks the AST to resolve scopes, build symbol tables, and perform type checking, flagging invalid programs before code generation.
Code generation — walks the verified AST and emits LLVM IR using the LLVM C++ API.
Compilation to native code — the generated IR is passed to the LLVM toolchain (llc/clang), which handles optimization and produces assembly and an executable binary.

    source code → tokens → AST → verified AST → LLVM IR → assembly / binary


### Parser design

The parser is a recursive descent parser with predictive (LL(1)) decisions, written by hand in C++ rather than generated from a grammar by a tool such as Bison (which produces LALR(1) bottom-up parsers).

Recursive descent: each construct of the language has its own parsing function, and these functions call each other recursively, following the structure of the grammar.
Predictive, LL(1): every decision is made by looking at a single token ahead, so the parser never needs to backtrack.

Operator precedence is handled by a chain of functions, one per precedence level. Each level asks the next one for its operands, so operators lower in the chain bind tighter:
parseExpr1 (+ -)  →  parseExpr2 (* /)  →  parseUn (unary - !)  →  parseExpr3 (numbers, identifiers, parentheses)

The AST is built from a hierarchy of node classes (expressions, statements, declarations) that support the Visitor pattern, so semantic analysis and code generation can be separate passes over the same tree.


## STRUCTURE
```
IRCompiler/
├── include/          # header files (.h)
├── src/              # implementation files (.cpp)
├── examples/         # sample programs written in the language
└── tests/            # test cases
```

## Status

In development. Current focus: the parser.

 - [x] Token definitions
 - [x] Lexer
 - [x] AST node classes and Visitor interface
 - [ ] Parser → AST (expressions with precedence and unary operators done; statements and declarations in progress)
 - [ ] Semantic analysis
 - [ ] LLVM IR code generation
 - [ ] Optimizations
 - [ ] End-to-end example programs
