#include <iostream>

int encode(char *out, unsigned int utf) {
    if (utf <= 0x7F) {
        // Plain ASCII
        out[0] = (char) utf;
        out[1] = 0;
        return 1;
    } else if (utf <= 0x07FF) {
        // 2-byte unicode
        out[0] = (char) (((utf >> 6) & 0x1F) | 0xC0);
        out[1] = (char) (((utf >> 0) & 0x3F) | 0x80);
        out[2] = 0;
        return 2;
    } else if (utf <= 0xFFFF) {
        // 3-byte unicode
        out[0] = (char) (((utf >> 12) & 0x0F) | 0xE0);
        out[1] = (char) (((utf >>  6) & 0x3F) | 0x80);
        out[2] = (char) (((utf >>  0) & 0x3F) | 0x80);
        out[3] = 0;
        return 3;
    } else if (utf <= 0x10FFFF) {
        // 4-byte unicode
        out[0] = (char) (((utf >> 18) & 0x07) | 0xF0);
        out[1] = (char) (((utf >> 12) & 0x3F) | 0x80);
        out[2] = (char) (((utf >>  6) & 0x3F) | 0x80);
        out[3] = (char) (((utf >>  0) & 0x3F) | 0x80);
        out[4] = 0;
        return 4;
    } else {
        // error - use replacement character
        out[0] = (char) 0xEF;
        out[1] = (char) 0xBF;
        out[2] = (char) 0xBD;
        out[3] = 0;
        return 0;
    }
}

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "");

    unsigned int ch = 256;
    const unsigned int offset = 64 * 32;
    char utf8[5];
    char action;

    while (1) {
        std::cout << "offset: " << ch << std::endl;
        for (unsigned int i = ch; i < ch + offset; ++i) {
            if (i % 64 == 0) {
                std::cout << "\n";
            }
            int s = encode(utf8, i);
            std::cout << utf8 << " ";
        }
        while (1) {
            std::cin >> action;
            if (action == 'q') {
                exit(0);
            }
            if (action == 'n') {
                ch += offset;
                break;
            }
            if (action == 'b') {
                if (ch == 0) {
                    break;
                }
                ch -= offset;
                break;
            }
        }
    }

    return 0;
}
