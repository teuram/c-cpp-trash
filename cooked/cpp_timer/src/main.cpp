#include <iostream>

#include "timer.cpp"

int main(int argc, char* argv[]) {

    Timer t(2000);

    while (1) {
        if (t.check()) {
            std::cout << "hello" << std::endl;
        }
    }

    return 0;
}
