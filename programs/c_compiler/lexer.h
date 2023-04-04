
#ifndef _LEXER_H_
#define _LEXER_H_

#include "stack.h"

typedef enum {
    NUMBER = 1,
    WORD = 2,
    STRING = 3,

    PLUS = 10,
    MINUS = 11,
    STAR = 12,
    SLASH = 13,
    PROCENT = 14,

    PLUSPLUS = 30,
    MINUSMINUS = 31,

    LBRACKET = 21,
    RBRACKET = 22,

    LCURLYBRACES = 23,
    RCURLYBRACES = 24,

    EQ = 20,

    SEMICOLON = 50,
    COLON = 51,
    COMMA = 52,
    QUOTE = 53,
    EOP = 100

} TypeTocken;

typedef struct {
    TypeTocken type;
    char* value;
    int line;
    int ch;
} Tocken;

typedef struct {
    char* text;
    char current_char;
    Stack* tockens;
    int counter;
    int line;
    int line_char;
} Lexer;

void lexer_analyze(Lexer* lexer);
void print_tocken(Tocken* tocken);

#endif

