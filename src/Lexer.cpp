#include <iostream>
#include "Lexer.h"
#include <stdexcept>

    Lexer::Lexer(std::string text) : position(0), buffer(text) {}
    char Lexer::peek() {
        if (position+1<buffer.size())
            return buffer[position+1];
        return '\0';
    }

    Tok Lexer::scannerLex() {




        while (position<buffer.size()) {
            switch (buffer[position]) {
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
                    if (peek() == '+') {
                        position += 2;
                        return Tok{"++", 0, 0, INCREMENT};
                    }
                    position++;
                    return Tok{"+",0,0,PLUS};

                case '-':
                    if (peek() == '-') {
                        position += 2;
                        return Tok{"--", 0, 0, DECREMENT};
                    }
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

                case ';' :
                    position++;
                    return Tok{";",0,0,SEMICOL};


                case '/' :
                    position++;
                    return Tok{"/",0,0,SLASH};


                case '=' :
					if (peek()=='=') {
                        position += 2;
                        return Tok{"==",0,0,EQ};
                    }
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
                    }throw std::runtime_error("not OR");

                case '!' :
                    if (peek()=='=') {
                        position += 2;
                        return Tok{"!=",0,0,NEQ};
                    }
                    position++;
                    return Tok{"+",0,0,NOT};




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
                    for (size_t i=position;i<buffer.size();i++) {
                        if (buffer[i]=='"') {
                            position = i+1;
                            return Tok{buffer.substr(start, i- start),0,0,STRING};
                        }
                    }
                    throw std::runtime_error("unterminated string");
                }

                default:
                    if (isdigit(buffer[position])) {

                        size_t start = position;
                        while (position < buffer.size() && isdigit(buffer[position])) {
                            position++;}
                        return Tok{buffer.substr(start, position- start),0,0,NUMBER};

                    }
                    else if (isalpha(buffer[position])) {
                        std::string identifier;
                        while (position<buffer.size() && isalnum(buffer[position])) {
                            identifier += buffer[position];
                            position++;
                        }
                        auto it = keywords.find(identifier);
                        if (it!= keywords.end())
                            return Tok{identifier, 0,0,it->second };
                        else return Tok{identifier, 0,0, IDENTIFIER};
                    }
                    throw std::runtime_error("unexpected char");
            }
        }
        return Tok{"",0,0,END_OF_FILE};
    }

        std::vector<Tok> Lexer::tokenize() {
            Tok t;
            do {
                t = scannerLex();
                tokens.push_back(t);
            }while (t.token_type!=END_OF_FILE);
            return tokens;
        }




