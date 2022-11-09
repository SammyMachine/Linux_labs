#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define MAX_RETRIES 10
union semun {
    int val;
    struct semid_ds* buf;
    ushort* array;
};
int main() {
    char u_char = 'J';
    key_t key;
    int sem_id;
    if ((key = ftok(".", u_char)) == -1) {
        perror("ftok");
        exit(1);
    }
    sem_id = semget(key, 1, IPC_EXCL | 0666);
    fprintf(stderr, "Semaphore id: %d\n", sem_id);
    int prcCnt = semctl(sem_id, 0, GETNCNT);
    fprintf(stderr, "Processes waiting: %d\n", prcCnt);
}

