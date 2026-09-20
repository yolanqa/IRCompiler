#include <iostream>
#include "Lexer.h"
#include <stdexcept>


    char Lexer::peek() {
        if (text[position]+1,text.size())
            return text[position+1];
    }

    Tok Lexer::scannerLex() {

        std::string identifier;

        /*while(position<text.size() && isalnum(text[position])) {
            identifier += text[position];
            position++;
        }

        TOKEN tok;
        auto it = keywords.find(identifier);
        if(it!=keywords.end()) {
            tok = it->second;
        }
        else {
            tok =  IDENTIFIER;}

        return Tok{identifier, 0, 0, tok};*/

    while (position<text.size()) {
        switch (text[position]) {
            case ' ':
                position++; break;
            case '\n':
                position++;
                break;

            case '(':
                position++;
                return Tok{"(", 0, 0, LPAREN};

            case ')':
                position++;
                return Tok{")",0,0,RPAREN};

            case '+':
                position++;
                return Tok{"+",0,0,PLUS};

            case '-':
                position++;
                return Tok{"-",0,0,MINUS};

            case '*':
                position++;
                return Tok{"*",0,0,STAR};

            case '{':
                position++;
                return Tok{"{",0,0,LBRACE};

            case '}':
                position++;
                return Tok{"}",0,0,RBRACE};

            case ',' :
                position++;
                return Tok{",",0,0,COMMA};


            case '/' :
                position++;
                return Tok{"/",0,0,SLASH};


            case '=' :
                position++;
                return Tok{"=",0,0,EQUAL};


            case '&' :
                if (peek()=='&') {
                    position += 2;
                    return Tok{"&&",0,0,AND};
                }throw std::runtime_error("not AND");


            case '|' :
                if (peek()=='|') {
                    position += 2;
                    return Tok{"||",0,0,OR};
                }
                throw std::runtime_error("not OR");


            case '!' :
                if (peek()=='=') {
                    position += 2;
                    return Tok{"!=",0,0,NOT};
                }
                throw std::runtime_error("not NOT");


            case '^' :
                position++;
                return Tok{"^",0,0,XOR};


            case '<' :
                position++;
                return Tok{"<",0,0,LESSTHAN};


            case '>' :
                position++;
                return Tok{">",0,0,GREATERTHAN};


            case '"' : {
                position++;
                size_t start = position;
                for (size_t i=position;i<text.size();i++) {
                    if (text[i]=='"') {
                        position = i+1;
                        return Tok{text.substr(start, i- start),0,0,STRING};
                    }
                }
                throw std::runtime_error("unterminated string");
            }
            default:
                if (isdigit(text[position])) {

                    size_t start = position;
                    while (position < text.size() && isdigit(text[position])) {
                        position++;
                    }
                    return Tok{text.substr(start, position- start),0,0,NUMBER};

                }
                throw std::runtime_error("unexpected char");
        }
    }
        return Tok{"",0,0,END_OF_FILE};

        /// continue here




