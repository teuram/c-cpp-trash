
#include "stack.h"
#include "lexer.h"

std::string Token::to_string() {
    std::ostringstream s;
    s << text;
    return s.str();
}

Lexer::Lexer(char* raw) {
    this->_raw = raw;
}

void Lexer::analyze() {
    char* raw = _raw;
    while (*raw) {
        if (is_alpha(*raw)) {
            raw = parse_word(raw);
        }
        if (is_digit(*raw)) {
            raw = parse_number(raw);
        }
        if (is_operator(*raw)) {
            raw = parse_operator(raw);
        }
        raw++;
    }

    tokens.reverse();

    Token* t;
    while (tokens >> t) {
        std::cout << t->to_string() << std::endl;
        std::cout << t->type << std::endl;
    }
}

char* Lexer::parse_word(char* raw) {
    char* end = raw;
    while (is_alpha(*end)) end++;
    unsigned int len = end - raw ;

    Token* t = new Token;
    t->text = new char[len + 1] {'\0'};
    t->type = STRING;
    memcpy(t->text, raw, len);

    tokens << t;

    return end;
}

char* Lexer::parse_number(char* raw) {
    char* end = raw;
    while (is_digit(*end)) end++;
    unsigned int len = end - raw ;

    Token* t = new Token;
    t->text = new char[len + 1] {'\0'};
    t->type = NUMBER;
    memcpy(t->text, raw, len);

    tokens << t;

    return end;
}

char* Lexer::parse_operator(char* raw) {
    char* end = raw;
    while (is_operator(*end)) end++;
    unsigned int len = end - raw ;

    Token* t = new Token;
    t->text = new char[len + 1] {'\0'};
    memcpy(t->text, raw, len);

    if (strcmp(t->text, "+")) {
        t->type = PLUS;
    }
    if (strcmp(t->text, "-")) {
        t->type = MINUS;
    }

    tokens << t;

    return end;
}

inline int Lexer::is_alpha(char c) {
    return (c > 'a' && c < 'z');
}

inline int Lexer::is_digit(char c) {
    return (c > '0' && c < '9');
}

inline int Lexer::is_operator(char c) {
    if (c == '+') return 1;
    if (c == '-') return 1;
    return 0;
}

