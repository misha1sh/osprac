#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // получаем идентификатор пользователя, запустившего программу
    uid_t uid = getuid();
    // получаем идентификатор группы пользователя, запустившего программу
    gid_t gid = getgid();

    // выводим результаты на экран
    printf("uid: %u, gid: %u\n", uid, gid);

    return 0;
}
