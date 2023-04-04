#include <stdio.h>
#include <dlfcn.h>

/* #include */

int add(int a, int b);

int main(int argc, char *argv[]) {

    printf("%d", add(6, 4));

    return 0;
}

