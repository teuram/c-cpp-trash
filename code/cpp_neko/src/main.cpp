#include <iostream>

#include "cat.h"
#include "timer.h"

int main(int argc, char* argv[]) {

    Cat cat;

    int state = 0;
    Timer t(500);

    while (1) {
        if (t.check()) {
            std::cout << "\e[?25l";
            cat.print((++state) % 3);
            std::cout << "\e[?25h";
        }
    }

    setlocale(LC_ALL, "");

    return 0;
}
