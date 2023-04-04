
#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <string.h>

#include "stack.h"

enum TokenType {
    NUMBER = 1,
    STRING = 2,

    PLUS   = 10,
    MINUS  = 11,
    EQ     = 12
};

class Token {
public:
    char* text;
    TokenType type;

    std::string to_string();

    ~Token() {
        delete text;
    }
};

class Lexer {
private:
    char* _raw;
    Stack<Token*> tokens;

public:

    Lexer(char* raw);

    void analyze();

private:
    char* parse_word(char* raw);

    char* parse_number(char* raw);
    char* parse_operator(char* raw);

    inline int is_alpha(char c);

    inline int is_digit(char c);

    inline int is_operator(char c);

};

#endif

