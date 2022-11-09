#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    int p[2];
    pid_t pid;
    int fd_in = 0;
    int i;
    for (i = 1; i < argc; i++) {
        pipe(p);
        if ((pid = fork()) == -1) exit(EXIT_FAILURE);
        else if (pid == 0) {
            dup2(fd_in, 0);
            if (argv[i + 1] != nullptr) dup2(p[1], 1);
            close(p[0]);
            char *t = argv[i];
            execlp(t, t, 0);
            exit(EXIT_FAILURE);
        }
        else {
            wait(nullptr);
            close(p[1]);
            fd_in = p[0];
        }
    }
    return 0;
}
