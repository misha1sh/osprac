#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    // fd1: parent -- writing, child -- reading
    // fd2: parent -- reading, child -- writing
    int     fd1[2], fd2[2], result;

    size_t size;
    char  resstring[14];

    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {

        /* Parent process */
        if (close(fd1[0]) < 0 || close(fd2[1]) < 0) {
            printf("parent: Can\'t close one side of pipe\n"); exit(-1);
        }

        printf("parent: writing 'Hello, world!' to pipe1\n");
        size = write(fd1[1], "Hello, world!", 14);

        if (size != 14) {
            printf("parent: Can\'t write all string to pipe\n");
            exit(-1);
        }

        size = read(fd2[0], resstring, 14);
        if (size < 0) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }
        printf("parent: got string from pipe2: '%s'\n", resstring);



        if (close(fd1[1]) < 0 || close(fd2[0]) < 0) {
            printf("parent: Can\'t close other of pipe\n"); exit(-1);
        }

        printf("Parent exit, resstring: '%s'\n", resstring);

    } else {

        /* Child process */

        if (close(fd1[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n"); exit(-1);
        }

        size = read(fd1[0], resstring, 14);
        if (size < 0) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        printf("child: got string from pipe1: '%s'\n", resstring);

        // reverse string (just for some changes)
        for (int i = 0; i < (size - 1) / 2; i++) {
            char c = resstring[size - i - 2];
            resstring[size - i - 2] = resstring[i];
            resstring[i] = c;
        }


        printf("child: writing '%s' to pipe 2\n", resstring);
        size = write(fd2[1], resstring, size);
        if (size != 14) {
            printf("child: Can\'t write all string to pipe\n");
            exit(-1);
        }

        printf("Child exit, resstring: '%s'\n", resstring);

        if (close(fd1[0]) < 0 || close(fd2[1]) < 0) {
            printf("child: Can\'t close other side of pipe\n"); exit(-1);
        }
    }

    return 0;
}
