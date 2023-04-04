#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
	
int main(int argc, char *argv[]) {

    if(argc < 2) exit(1);

    int fd = open(argv[1], O_RDWR | O_NOCTTY);

    if(fd < 0) {
        exit(1);
    }

    struct termios termio;

    tcgetattr(fd, &termio);

    cfsetispeed(&termio, B9600);
    cfsetospeed(&termio, B9600);

    termio.c_cflag &= ~PARENB;
    termio.c_cflag &= ~CSTOPB;
    termio.c_cflag &= ~CSIZE;
    termio.c_cflag |=  CS8;

    termio.c_cflag &= ~CRTSCTS;
    termio.c_cflag |= CREAD | CLOCAL;

    termio.c_iflag &= ~(IXON | IXOFF | IXANY);
    termio.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    termio.c_oflag &= ~OPOST;

    termio.c_cc[VMIN] = 40;
    termio.c_cc[VTIME] = 10;


    if((tcsetattr(fd, TCSANOW, &termio)) != 0) {
        puts("\n  ERROR ! in Setting attributes");
        exit(1);
    }

    char read_buffer[64];
    int  bytes_read = 0;

    int i;
    char c;

    while(1) {
        tcflush(fd, TCIFLUSH);
        bytes_read = read(fd, &read_buffer, 64);

        for(i = 0; i < bytes_read; i++) {
            c = read_buffer[i];
            putchar(c);
        }
    }
    close(fd);
}

