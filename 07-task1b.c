#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define buffer_size 4096

int main()
{
    char     *array;
    int     shmid;
    char    pathname[] = "07-task1a.c";
    key_t   key;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, buffer_size, 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
    }

    if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }


    printf("Got text from shared memory:\n%s \n", array);

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Can't remove shared memory\n");
        exit(-1);
    }
    printf("Shared memory removed");

    return 0;
}
