#include <iostream>
#include <ostream>
#include <sstream>

#include "lexer.h"

int main(int argc, char* argv[]) {

    Lexer l(new char[] {"goo 567 + -  goh"});
    l.analyze();

    return 0;
}

