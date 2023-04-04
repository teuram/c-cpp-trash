
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define bool    char
#define true    1
#define false   0

long _filelength(int fd) {
    struct stat st;
    fstat(fd, &st);
    return st.st_size;
}

char* read_file(char* file_name) {
    int fd = open(file_name, O_RDONLY);

    if(!fd) {
        printf("error io\n");
        printf("\tfrom %s at %s\n", __FILE__, __func__);
        exit(1);
    }

    long size = _filelength(fd);
    char* buffer = malloc(size);

    read(fd, buffer, size);

    close(fd);
    return buffer;
}

int atoi(const char* str){
    int num = 0;
    int i = 0;
    bool isNegetive = false;
    if(str[i] == '-'){
        isNegetive = true;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if(isNegetive) num = -1 * num;
    return num;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        exit(0);
    }

    char* buffer = read_file(argv[1]);
    int sum = 0;

    do {
        sum += atoi((const char*)buffer);;
        while (*(buffer++) != '\n');
    } while(*buffer != '\0');

    printf("sum: %d\n", sum);
    free(buffer);

    return 0;
}
