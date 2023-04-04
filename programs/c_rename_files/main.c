#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char* get_filename_ext(const char* filename) {
    const char *dot = strchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot;
}

int main(int argc, char *argv[]) {

    printf("continue operation (y/n): ");

    char c = getchar();

    if(c != 'y') {
        exit(EXIT_SUCCESS);
    }

    struct dirent *de;
    char new_name[256];

    DIR *dr = opendir(".");

    if (dr == NULL)  {
        printf("Could not open current directory");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (stat("./.tmp/", &st) == -1) {
        mkdir("./.tmp/", 0700);
    }

    int count = 0;

    while((de = readdir(dr)) != NULL) {

        if(de->d_name[0] == '.') continue;
        stat(de->d_name, &st);
        if(de->d_type == DT_REG) {
            sprintf(new_name, "./.tmp/%08d%s", count, get_filename_ext(de->d_name));
            rename(de->d_name, new_name);

            count++;
        }
    }

    closedir(dr);


    dr = opendir("./.tmp/");

    if (stat("./.tmp/", &st) == -1) {
        exit(2);
    }

    chdir("./.tmp/");

    while((de = readdir(dr)) != NULL) {

        if(de->d_name[0] == '.') continue;

        sprintf(new_name, "../%s", de->d_name);
        rename(de->d_name, new_name);
    }

    closedir(dr);

    chdir("..");

    remove("./.tmp/");


    return 0;
}
