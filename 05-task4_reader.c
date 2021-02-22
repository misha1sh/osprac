#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;

    size_t size;
    char resstring[14];
    char name[] = "aaa.fifo";

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Reader: Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = read(fd, resstring, 14);

    if (size < 0) {
        printf("CReader: can\'t read string from FIFO\n");
        exit(-1);
    }

    printf("Reader: exit, resstring: %s\n", resstring);

    if (close(fd) < 0) {
        printf("Reader: Can\'t close FIFO\n");
        exit(-1);
    }
    return 0;
}
