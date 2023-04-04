
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#include "stacknode/stacknode.h"

char* read_file(char* file_name) {
    int fd = open(file_name, O_RDONLY);
    struct stat st;

    if(!fd) {
        printf("error io\n");
        printf("\tfrom %s at %s\n", __FILE__, __func__);
        exit(1);
    }

    fstat(fd, &st);

    long size = st.st_size;
    char* buffer = malloc(size);

    if (buffer == NULL) {
        printf("error: memory allocation error");
        exit(1);
    }

    read(fd, buffer, size);

    close(fd);
    return buffer;
}

int main(int argc, char* argv[]) {

    char* str = read_file("LICENSE");

    puts(str);

    StackNode* stack = NULL;
    pushStackNode(stack);
    setStackNodeData(stack, str, strlen(str));
    freeStack(stack);

    free(str);

    return 0;
}
