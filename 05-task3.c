#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // создаём pipe
    int fd[2];
    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    int flags = fcntl(fd[1], F_GETFL, 0);
    if (flags < 0) {
        printf("Unable to get flags\n");
        exit(-1);
    }

    // нам нужно, чтобы вызовы write были не блокирующие
    if (fcntl(fd[1], F_SETFL, flags | O_NONBLOCK) < 0) {
        printf("Can\'t set pipe to non blocking mode\n");
        exit(-1);
    }

    int size = 0;
    char tmp;
    // будем добавлять байты в pipe до тех пор, пока она не заполнится
    while (write(fd[1], &tmp, 1) == 1) {
        size++;
    }

    // выводим результат
    printf("Pipe size in your system: %d\n", size);

    // не забываем закрыть pipe
    if (close(fd[0]) < 0 || close(fd[1]) < 0) {
        printf("Cannot close  pipe");
        return 0;
    }

    return 0;
}
