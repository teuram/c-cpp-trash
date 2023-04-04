
/* #include <stdio.h> */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "stack.h"
#include "lexer.h"
#include "parser.h"

#define MAX_READ 0xfffe

char* read_file(char* file_name) {
    char* buffer = malloc(MAX_READ + 1);
    int fd = open(file_name, O_RDONLY);

    if(!fd) {
        printf("error io");
        exit(1);
    }

    int res = read(fd, buffer, MAX_READ);
    buffer[res] = '\0';

    close(fd);
    return buffer;
}

int main(int argc, char* argv[]) {

    int print_tockens = 0;
    char* file_name = NULL;

    if(argc == 2) {
        file_name = argv[1];
    }
    if(argc == 3) {
        if(argv[1][0] == 't') {
            print_tockens = 1;
        }
        file_name = argv[2];
    }

    char* buffer = read_file(file_name);

    Stack stack;
    init_stack(&stack);
    Stack variables;
    init_stack(&variables);

    Lexer lexer;
    lexer.counter = 0;
    lexer.text = buffer;
    lexer.tockens = &stack;

    lexer_analyze(&lexer);

    if(print_tockens) {
        puts("\n");
        for(int i = 0; i < lexer.tockens->pointer - 1; i++) {
            print_tocken((Tocken*)lexer.tockens->stack[i]);
        }
        puts("\n");
    }

    Parser parser;
    parser.count_tocken = 0;
    parser.tockens = &stack;
    parser.variables = &variables;

    parser_analyze(&parser);

    return 0;
}
