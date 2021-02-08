#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid, ppid;
    pid_t fork_ret_value = fork();

    pid  = getpid();
    ppid = getppid();

    printf("My pid = %d, my ppid = %d\n", (int)pid, (int)ppid);

    if (fork_ret_value == -1) {
        printf("Unable to start child process\n");
    } else if (fork_ret_value == 0) {
        printf("I am a child process. Starting a new program: ls -l -a\n");
        (void) execle("/bin/ls", "/bin/ls", "-l", "-a", NULL, envp);
        printf("An error occured at starting program.\n");
    } else {
        printf("I am a parent process.\n");
    }

    return 0;
}
