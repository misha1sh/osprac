#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// maximum file size
#define buffer_size 4096

int main()
{
    char     *array;    // Pointer to shared memory
    int     shmid;     // IPC descriptor for the shared memory
    char    pathname[] = "07-task1a.c"; // The file name used to generate the key.
    // A file with this name must exist in the current directory.

    key_t   key;       // IPC key
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    int fd;
    if ((fd = open("07-task1a.c", O_RDONLY)) < 0) {
        printf("Can\'t open file '07-task1a.c' for reading\n");
        exit(-1);
    }

    char* fileData = calloc(buffer_size, sizeof(char));
    if (read(fd, fileData, buffer_size) < 0) {
        printf("Unable to read from file\n");
        exit(-1);
    }


    if ((shmid = shmget(key, buffer_size, 0666|IPC_CREAT|IPC_EXCL)) < 0) {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }
    if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }


    memcpy(array, fileData, buffer_size);
    printf("Writen %d bytes into shared memory\n", buffer_size);

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}
