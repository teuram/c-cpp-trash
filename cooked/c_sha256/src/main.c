#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "sha256.h"

void print_sha256(unsigned char* sha) {
    for(int i = 0; i < 32; i++){
        printf("%x", sha[i]);
    }
}

int main(void) {

    char str[64];
    memset(&str, 0, 64);

    read(0, &str, 64);

    unsigned char* tt = sha256((const unsigned char*)str, strlen(str) - 1, NULL);

    print_sha256(tt);

    return 0;
}
