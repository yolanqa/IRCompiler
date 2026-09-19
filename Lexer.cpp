#include <iostream>
#include "Lexer.h"
#include <stdexcept>

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


        while(position<text.size()) {
            if (text[position]== ' ' || text[position]='\n')
                position++;
            else if (text[position]=='(') {
                position++;
                return Tok{"(", 0, 0, LPAREN};
            }
            else if (text[position]==')') {
                position++;
                return Tok{")",0,0,RPAREN};
            }
            else if (text[position]=='+') {
                position++;
                return Tok{"+",0,0,PLUS};
            }
            else if (text[position]=='-') {
                position++;
                return Tok{"-",0,0,MINUS};
            }
            else if (text[position]=='*') {
                position++;
                return Tok{"*",0,0,STAR};
            }
            else if(text[position]=='{') {
                position++;
                return Tok{"{",0,0,LBRACE};}

            else if (text[position]=='}') {
                position++;
                return Tok{"}",0,0,RBRACE};
            }
            else if(text[position]==',') {
                position++;
                return Tok{",",0,0,COMMA};
            }

            else if (text[position]=='/') {
                position++;
                return Tok{"/",0,0,SLASH};
            }

            else if (text[position]=='=') {
                position++;
                return Tok{"=",0,0,EQUAL};
            }

            else if (text[position]=='&') {
                if (peek()=='&') {
                    position += 2;
                    return Tok{"&&",0,0,AND};
                }
                else {throw std::runtime_error("mesaj aici");}
            }

            else if (text[position]=='|') {
                if (peek()=='|') {
                    position += 2;
                    return Tok{"||",0,0,OR};
                }
                else {throw std::runtime_error("mesaj aici");}
            }

            else if (text[position]=='!') {
                if (peek()=='=') {
                    position += 2;
                    return Tok{"!=",0,0,NOT};
                }
                else {throw std::runtime_error("mesaj aici");}
            }

            else if (text[position]=='^') {
                position++;
                return Tok{"^",0,0,XOR};
            }

            else if (text[position]=='<') {
                position++;
                return Tok{"<",0,0,LESSTHAN};
            }

            else if (text[position]=='>') {
                position++;
                return Tok{">",0,0,GREATERTHAN};
            }

            else if (text[position]=='"') {
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
            else{throw std::runtime_error("unexpected char");}
        }

        /// TODO: continue here




