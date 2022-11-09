#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
pid_t pid_main, pid_child;
void child_sig(int the_sig) {
    sleep(2);
    signal(the_sig, child_sig);
    if (the_sig == SIGQUIT) exit(1);
    printf("Child: SIGUSR1 received.\n");
    kill(pid_main, SIGUSR2);
    printf("Child: SIGUSR1 sent to parent.\n");
}
void parent_sig(int the_sig) {
    sleep(2);
    signal(the_sig, parent_sig);
    if (the_sig == SIGQUIT) exit(1);
    printf("Parent: SIGUSR2 received.\n");
    kill(pid_child, SIGUSR1);
    printf("Parent: SIGUSR1 sent to child.\n");
}
int main(void) {
    int i;
    void child_sig(int the_sig);
    void parent_sig(int the_sig);
    pid_main = getpid();
    pid_child = fork();
    if (pid_child == 0) {
        struct sigaction sa;
        sa.sa_handler = child_sig;
        sa.sa_flags = 0; //SA_RESTART
        sigemptyset(&sa.sa_mask);
        sigaction(SIGUSR1, &sa, NULL);
        for (i = 0;;++i) {
            sleep(2);
        }
    } else {
        struct sigaction sa;
        sa.sa_handler = parent_sig;
        sa.sa_flags = 0; //SA_RESTART
        sigemptyset(&sa.sa_mask);
        sigaction(SIGUSR2, &sa, NULL);
        sleep(2);
        kill(pid_child, SIGUSR1);
        for (i = 0;;++i) {
            sleep(2);
        }
    }
}


