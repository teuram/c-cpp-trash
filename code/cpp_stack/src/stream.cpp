
namespace io {

    enum iostream {
        STDIN = 0,
        STDOUT = 1,
        STDERR = 2
    };

};

#include <fcntl.h>

class Stream {
    public:
        int fd;

        Stream(io::iostream iostream) {
            switch (iostream) {
                case io::STDIN:
                    fd = 0;
                    break;
                default:
                    throw 8;
            }
        }

        char* read(unsigned int l) {
            
        }


            /* close(fd); */

};
