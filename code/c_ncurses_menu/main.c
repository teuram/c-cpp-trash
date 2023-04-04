#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>

#define MAX_LENGTH_LABEL 32

typedef enum {
    CHECKBOX,
    ELEMENT
} TypeElement;

typedef struct element Element;

typedef struct element {
    TypeElement type;
    char text[MAX_LENGTH_LABEL];
    void (*callback)(Element* self);
    void* metadata;
} Element;

void callback_first(Element* self) {
    int fd = open("log.log", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    write(fd, "click\n", 6);
    close(fd);
}

void callback_second(Element* self) {
    // code
    char* state = ((char*)self->metadata);
    switch(*state) {
        case 'y':
            *state = 'n';
            break;
        case 'n':
            *state = 'y';
            break;
        default:
            *state = 'n';
            break;
    }
}

void show_list(Element el[], int elements) {

    WINDOW *w;
    unsigned int count_element = 0;
    char item[MAX_LENGTH_LABEL + 4];
    int ch = 0;

    initscr();
    w = newwin(LINES, COLS, 0, 0);
    box(w, 0, 0);

    noecho();
    raw();
    keypad(w, 1);
    curs_set(0);

    do {
        switch(ch) {
            case KEY_UP:
                count_element--;
                if(count_element >= elements) count_element = elements - 1;
                break;
            case KEY_DOWN:
                count_element++;
                if(count_element >= elements) count_element = 0;
                break;
            case 10: // enter
            case 32: // space
                if(el[count_element].callback != NULL) {
                    el[count_element].callback(&el[count_element]);
                }
                break;
        }
        mvwprintw(w, 0, COLS / 2 - 4 / 2, "menu");
        for(int i = 0; i < elements; i++) {
            if(el[i].type == CHECKBOX) {
                sprintf(item, "[%c] %-7s", *((char*)el[i].metadata), el[i].text);
            } else {
                sprintf(item, "    %-7s", el[i].text);
            }
            if(i == count_element) wattron(w, A_STANDOUT);
            mvwprintw(w, i + 2, COLS / 2 - MAX_LENGTH_LABEL / 2 - 4, "%s", item);
            if(i == count_element) wattroff(w, A_STANDOUT);
        }
    } while((ch = wgetch(w)) != 'q');
    delwin(w);
    endwin();
}

int main() {

    Element el[] = {
        {
            .type = ELEMENT,
            .text = "write to file",
            /* .callback = callback_first */
        },
        {
            .type = CHECKBOX,
            .text = "sshd",
            .callback = callback_second,
            .metadata = malloc(1 * sizeof(char))
        },
        {
            .type = CHECKBOX,
            .text = "alsa",
            .callback = callback_second,
            .metadata = malloc(1 * sizeof(char))
        },
        {
            .type = CHECKBOX,
            .text = "udev",
            .callback = callback_second,
            .metadata = malloc(1 * sizeof(char))
        },
    };

    *((char*)el[1].metadata) = ' ';
    *((char*)el[2].metadata) = ' ';
    *((char*)el[3].metadata) = ' ';

    show_list(el, 4);
    return 0;
}


