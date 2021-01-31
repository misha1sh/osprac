#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;
  int a = 0;

  pid_t fork_ret_value = fork();
  //
  // If the new process is created successfully,
  // two processes start working in pseudo-parallel from this point: the old and the new one.
  //
  // Before the following expression is executed,
  // the value of the variable a in both processes is 0.
  //

  // сделаем так, чтобы ребёнок добавлял к числу 1, а родитель 2
  if (fork_ret_value == -1) {
    printf("Unable to start child process");
  } else if (fork_ret_value == 0) {
    a = a + 1;
  } else {
    a = a + 2;
  }

  pid  = getpid();
  ppid = getppid();

  printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);

  return 0;
}
