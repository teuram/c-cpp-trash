
#ifndef _PARSER_H_
#define _PARSER_H_

#include "stack.h"
#include "lexer.h"

typedef struct parser {
    int count_tocken;
    Stack* tockens;
    Stack* variables;
    Tocken* tocken;
} Parser;

void parser_analyze(Parser* parser);

#endif

