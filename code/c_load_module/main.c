#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void load_module(char* file) {

    void *handle;
    char* (*func)();
    char *error;

    // Dynamically load shared library that contains funcvec()
    handle = dlopen(file, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    // Get a pointer to the funcvec() function we just loaded
    func = dlsym(handle, "get_info");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    printf("%s\n", func());

    // unload the shared library
    if (dlclose(handle) < 0) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
}

int main(void) {
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(".");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL) {

        if(de->d_type == DT_REG) {
            const char *dot = strrchr(de->d_name, '.');
            if(dot == NULL || dot == de->d_name) {
            } else {
                if(!strcmp(dot + 1, "so")) {
                    char lib_name[256];
                    sprintf(lib_name, "./%s", de->d_name);
                    printf("load module: %s\n", de->d_name);
                    load_module(lib_name);
                }
            }
        }

    }

    closedir(dr);

    return 0;
}

