
namespace term {

    #include <termios.h>
    #include <fcntl.h>
    #include <unistd.h>

    unsigned int width() {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);

        return w.ws_col;
    }

    unsigned int height() {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);

        return w.ws_row;
    }

    unsigned int lenString(const char *str) {
        unsigned int count = 0;
        while (1) {
            if (str[count] == '\0') return count;
            ++count;
        }
    }

    void print(const char *msg) {
        write(0, msg, lenString(msg) + 1);
    }

}

