#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

main() {
    int txt = open("test.txt", O_RDONLY);
    if (fork()) {
        char c[1];
        while (read(txt, c, sizeof(c)) > 0) {
            printf("Parent: %c\n", c[0]);
            sleep(1);
        }
        printf("Parent completed\n");
        close(txt);
    } else {
        char c[1];
        while (read(txt, c, sizeof(c)) > 0) {
            printf("Child: %c\n", c[0]);
            sleep(1);
        }
        printf("Child completed\n");
        close(txt);

    }
}
