
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>

#include "terminal.h"

class Cat {
public:

    Cat() {
    }

    void print(int state) {

        term::print("\e[2J\e[5A\r");

        switch (state) {
            case 0:
                std::cout <<
                    "/㇔_㇒\\\n"
                    "(●ㅅ●, )\n"
                    "|      | |\n"
                    "| |  | | |\n"
                    "し'__'_/ノ\n";
                break;
            case 1:
                std::cout <<
                    "/㇔_㇒\\\n"
                    "(,●ㅅ●,)\n"
                    "|      | |\n"
                    "| |  | | |\n"
                    "し'__'_/ノ\n";
                break;
            case 2:
                std::cout <<
                    "/㇔_㇒\\\n"
                    "( ,●ㅅ●)\n"
                    "|      | |\n"
                    "| |  | | |\n"
                    "し'__'_/ノ\n";
                break;
        }
    }

};


