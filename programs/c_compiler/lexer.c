#include <stdlib.h>

#include "stack.h"
#include "lexer.h"

static Tocken* new_tocken(TypeTocken type, char* value) {
    Tocken* tocken = malloc(sizeof(Tocken));
    tocken->value = value;
    tocken->type = type;
    return tocken;
}

void print_tocken(Tocken* tocken) {
    printf("tocken:\t%d\t%s\n", tocken->type, tocken->value);
}

static char next(Lexer* lexer) {
    return (lexer->current_char = lexer->text[lexer->counter++]);
}

int match_string(Lexer* lexer, char* b) {
    char* a = &(lexer->text[lexer->counter - 1]);
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0') {
        if(a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    lexer->counter += i - 1;
    return 1;
}

static inline int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static inline int is_operator(char c) {
    return strchr("+-*/%=;,(){}", c) != NULL;
}

static inline int is_character(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

static void parse_number(Lexer* lexer) {
    int i = 0;
    char* value = malloc(16 * sizeof(char));

    do {
        value[i++] = lexer->current_char;
        if(lexer->current_char == '.') {
            if(is_digit(next(lexer))) {
                value[i++] = lexer->current_char;
                continue;
            }
            printf("error parse a number:");
            exit(2);
        }
    } while(is_digit(next(lexer)) || lexer->current_char == '.');
    lexer->counter--;
    value[i] = '\0';

    push(lexer->tockens, (void*)new_tocken(NUMBER, value));
}

static Tocken op[] = {
    {PLUSPLUS, "++"},
    {PLUS, "+"},

    {MINUSMINUS, "--"},
    {MINUS, "-"},

    {STAR, "*"},
    {SLASH, "/"},
    {PROCENT, "%"},

    {EQ, "="},

    {LBRACKET, "("},
    {RBRACKET, ")"},

    {LCURLYBRACES, "{"},
    {RCURLYBRACES, "}"},

    {COMMA, ","},
    {SEMICOLON, ";"}
};

static void parse_operator(Lexer* lexer) {
    for(int i = 0; i < sizeof(op) / sizeof(op[0]); i++) {
        if(match_string(lexer, op[i].value)) {
            push(lexer->tockens, &op[i]);
            return;
        }
    }
    printf("error compilation:\nuknown operator %c\n", lexer->current_char);
    exit(2);
}

static void parse_word(Lexer* lexer) {
    int i = 0;
    char* value = malloc(256 * sizeof(char));

    do {
        value[i++] = lexer->current_char;
    } while(is_character(next(lexer)) || is_digit(lexer->current_char));
    lexer->counter--;
    value[i] = '\0';

    push(lexer->tockens, new_tocken(WORD, value));
}

static void parse_string(Lexer* lexer) {
    int i = 0;
    char* value = malloc(1024 * sizeof(char));

    /* value[i++] = lexer->current_char; */
    next(lexer);
    do {
        if(lexer->current_char == '\"') {
            /* value[i++] = lexer->current_char; */
            /* value[i] = '\0'; */
            push(lexer->tockens, new_tocken(STRING, value));
            return;
        }
        value[i++] = lexer->current_char;
    } while(next(lexer) != '\0');

    printf("error parsing: uncloseble string value\n");
    exit(3);

}

static void parse_multiline_commentary(Lexer* lexer) {
    do {
        if(match_string(lexer, "*/")) {
            return;
        }
    } while(next(lexer) != '\0');
    printf("error parsing: uncloseble comentary\n");
    exit(3);
}

static inline void parse_commentary(Lexer* lexer) {
    while(next(lexer) != '\n');
}

void lexer_analyze(Lexer* lexer) {
    lexer->counter = 0;
    /* lexer->current_char = next(lexer); */
    while(next(lexer) != '\0') {
        if(lexer->current_char == '"') {
            parse_string(lexer);
        }
        if(is_digit(lexer->current_char)) {
            parse_number(lexer);
        } else if(is_operator(lexer->current_char)) {
            parse_operator(lexer);
        } else if(is_character(lexer->current_char)) {
            parse_word(lexer);
        }
    }

    push(lexer->tockens, new_tocken(EOP, NULL));
}

