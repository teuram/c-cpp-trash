#include <iostream>

int main(int argc, char* argv[]) {

    int sum = 0;
    int buffer;

    while (1) {
        std::cin >> buffer;
        if (buffer == 0) break;
        sum += buffer;
    }

    std::cout << "sum of numbers: " << sum << std::endl;

    return 0;
}
