#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
main (void) {
    key_t key = 15;
    char *data_1, *data_2, *data_3;
    int shmid_1, shmid_2, shmid_3;
    if ((shmid_1 = shmget(key, 1023, 0644|IPC_CREAT)) == -1) {
        perror("shmget shmid_1");
        exit(1);
    }
    if ((shmid_2 = shmget(key + 1, 1023, 0644|IPC_CREAT)) == -1) {
        perror("shmget shmid_2");
        exit(1);
    }
    if ((shmid_3 = shmget(key + 2, 1023, 0644|IPC_CREAT)) == -1) {
        perror("shmget shmid_3");
        exit(1);
    }
    printf("Addresses:\n\n");
    data_1 = (char *) shmat(shmid_1, 0, 0);
    printf("First fragment of shared mem: %10p\n", data_1);
    data_2 = (char *) shmat(shmid_3, 0, 0);
    printf("Second fragment of shared mem: %10p\n", data_2);
    data_3 = (char *) shmat(shmid_3, 0, 0);
    printf("Third fragment of shared mem: %10p\n", data_3);
    return 0;
}
