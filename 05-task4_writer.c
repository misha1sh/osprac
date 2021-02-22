#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int fd;

    size_t size;
    char name[] = "aaa.fifo";

    (void) umask(0);

    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        if (errno == EEXIST) {
            printf("Writer: %s already exists\n", name);
        } else {
            printf("Can\'t create FIFO\n");
            exit(-1);
        }
    }


    if ((fd = open(name, O_WRONLY)) < 0) {
        printf("Writer: Can\'t open FIFO for writting\n");
        exit(-1);
    }

    size = write(fd, "Hello, world!", 14);

    if (size != 14) {
        printf("Writer: Can\'t write all string to FIFO\n");
        exit(-1);
    }

    if (close(fd) < 0) {
        printf("Writer: Can\'t close FIFO\n");
        exit(-1);
    }

    printf("Writer: operation successful. Exit\n");



    return 0;
}
