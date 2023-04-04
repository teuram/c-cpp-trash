#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "parser.h"

typedef struct {
    size_t ins_len;
    char** ins;
} Instruction;

typedef enum {
    INTEGER_TYPE = 1,
    STRING_TYPE = 2,
    BLOCK_TYPE = 3
} TypeVariable;

typedef struct {
    TypeVariable type;
    char* value;
} Variable;

void push_variable_stack(Stack* vsp, TypeVariable type, char* value) {
    Variable* var = malloc(sizeof(Variable));
    var->type = type;
    var->value = value;

    push(vsp, var);
}

Variable* searth_variable(Stack* vsp, char* var_name) {
    Variable* var;
    if(vsp->pointer == 0) {
        return NULL;
    }
    for(int i = 0; i < vsp->pointer; i++) {
        var = (Variable*)vsp->stack[i];
        if(!strcmp(var->value, var_name)) {
            return var;
        }
    }
    return NULL;
}

void print_instruction_stack(Stack* iop) {
    Instruction* ins;
    for(int i = 0; i < iop->pointer; i++) {
        ins = (Instruction*)iop->stack[i];
        for(int j = 0; j < ins->ins_len - 1; j++) {
            printf("%s ", ins->ins[j]);
        }
        printf("%s\n", ins->ins[ins->ins_len - 1]);
    }
}

void push_instruction_stack(Stack* iop, int argc, ...) {
    Instruction* i = malloc(sizeof(Instruction));
    i->ins_len = argc;
    i->ins = malloc(argc * sizeof(char*));

    va_list ap;
    va_start(ap, argc);
    char* arg;
    for(int counter = 1; counter <= argc; counter++) {
        arg = va_arg(ap, char*);
        i->ins[counter - 1] = arg;
    }
    va_end(ap);

    push(iop, i);
}

char* new_var_name() {
    char* var = malloc(9 * sizeof(char));
    for(int i = 0; i < 8; i++) {
        var[i] = rand() % 26 + 97;
    }
    return var;
}

static Tocken* next_tocken(Parser* parser) {
    Tocken* t = (Tocken*)parser->tockens->stack[parser->count_tocken++];
    parser->tocken = t;
    return t;
}

static void match_tocken(Parser* parser, TypeTocken type) {
    Tocken* t = (Tocken*)parser->tockens->stack[parser->count_tocken];
    if(t->type == type) {
        next_tocken(parser);
        return;
    }
    printf("error parsing: count %d, expected %d, here -> %d\n", parser->count_tocken, type, t->type);
    exit(2);
}

char* addition(Parser* parser, Stack* iop);

char* unary(Parser* parser, Stack* iop) {
    Tocken* t = next_tocken(parser);
    if(t->type == WORD) {
        Tocken* t2 = next_tocken(parser);
        if(t2->type == PLUSPLUS) {
            char* output = t->value;
            char* one = malloc(2 * sizeof(char));
            one = "1\0";
            push_instruction_stack(iop, 4, "op add", output, output, one);
            return output;
        }
        if(t2->type == MINUSMINUS) {
            char* output = t->value;
            char* one = malloc(2 * sizeof(char));
            one = "1\0";
            push_instruction_stack(iop, 4, "op sub", output, output, one);
            return output;
        }
        parser->count_tocken--;
    }
    if(t->type == NUMBER || t->type == STRING || t->type == WORD) {
        return t->value;
    }
    if(t->type == LBRACKET) {
        char* var = addition(parser, iop);
        match_tocken(parser, RBRACKET);
        return var;
    }
    if(t->type == MINUS) {
        Tocken* t2 = next_tocken(parser);
        if(t2->type == NUMBER) {
            char* val = malloc((strlen(t2->value) + 1) * sizeof(char));
            sprintf(val, "-%s", t2->value);
            return val;
        }
        parser->count_tocken--;
    }
    printf("unary error: count %d, here -> %d\n", parser->count_tocken, t->type);
    exit(2);
}

char* multiplication(Parser* parser, Stack* iop) {
    Tocken* t;
    char* val = unary(parser, iop);
    char* val2;
    while(1) {
        t = next_tocken(parser);
        if(t->type == STAR) {
            val2 = unary(parser, iop);
            char* output = new_var_name();
            push_instruction_stack(iop, 4, "op mul", output, val, val2);
            val = output;
            continue;
        }
        if(t->type == MINUS) {
            val2 = unary(parser, iop);
            char* output = new_var_name();
            push_instruction_stack(iop, 4, "op div", output, val, val2);
            val = output;
            continue;
        }
        parser->count_tocken--;
        break;
    }
    return val;
}

char* addition(Parser* parser, Stack* iop) {
    Tocken* t;
    char* val = multiplication(parser, iop);
    char* val2;
    while(1) {
        t = next_tocken(parser);
        if(t->type == PLUS) {
            val2 = multiplication(parser, iop);
            char* output = new_var_name();
            push_instruction_stack(iop, 4, "op add", output, val, val2);
            val = output;
            continue;
        }
        if(t->type == MINUS) {
            val2 = multiplication(parser, iop);
            char* output = new_var_name();
            push_instruction_stack(iop, 4, "op sub", output, val, val2);
            val = output;
            continue;
        }
        parser->count_tocken--;
        break;
    }
    return val;
}

void statement(Parser* parser, Stack* iop) {
    Tocken* t;
    Tocken* t2;
    while(1) {
        t = next_tocken(parser);

        if(t->type == WORD) {
            if(!strcmp(t->value, "let")) {
                match_tocken(parser, WORD);
                char* var_name = parser->tocken->value;
                match_tocken(parser, EQ);
                Variable* var = searth_variable(parser->variables, var_name);
                t2 = next_tocken(parser);
                if(var == NULL) {
                    switch(t2->type) {
                        case NUMBER:
                            push_variable_stack(parser->variables, INTEGER_TYPE, var_name);
                            break;
                        case STRING:
                            push_variable_stack(parser->variables, STRING_TYPE, var_name);
                            break;
                        default:
                            printf("error assigment statement: uknown type data\n");
                            exit(2);
                    }
                    match_tocken(parser, SEMICOLON);
                    continue;
                }
                printf("error assigment statement\n");
                exit(2);
            }
            if(!strcmp(t->value, "print")) {
                match_tocken(parser, LBRACKET);

                char* output;
                t2 = next_tocken(parser);
                if(t2->type == STRING) {
                    char* val = malloc((strlen(t2->value) + 2) * sizeof(char));
                    sprintf(val, "\"%s\"", t2->value);
                    output = t2->value;
                } else {
                    parser->count_tocken--;
                    output = addition(parser, iop);
                }

                push_instruction_stack(iop, 2, "print", output);

                match_tocken(parser, RBRACKET);
                match_tocken(parser, SEMICOLON);
                continue;
            }
            t2 = next_tocken(parser);
            if(t2->type == PLUSPLUS) {
                char* output = t->value;
                char* one = malloc(2 * sizeof(char));
                one = "1\0";
                push_instruction_stack(iop, 4, "op add", output, output, one);
                match_tocken(parser, SEMICOLON);
                continue;
            }
            if(t2->type == EQ) {
                char* output = t->value;

                int iop_before = iop->pointer;
                char* math_output = addition(parser, iop);
                int iop_after = iop->pointer - iop_before;

                if(iop_after == 0) {
                    push_instruction_stack(iop, 3, "set", output, math_output);
                } else {
                    Instruction* ins = (Instruction*)iop->stack[iop->pointer - 1];
                    free(ins->ins[1]);
                    ins->ins[1] = output;
                }

                match_tocken(parser, SEMICOLON);
                continue;
            }
            parser->count_tocken--;
        }

        parser->count_tocken--;
        break;
    }
}
void parser_analyze(Parser* parser) {
    Stack iop;
    init_stack(&iop);

    statement(parser, &iop);

    print_instruction_stack(&iop);
}



