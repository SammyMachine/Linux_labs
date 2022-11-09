#include<stdio.h>
#include<limits.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

main() {
    pid_t pid;
    char * path = "folder";
    char pathName[PATH_MAX];
    getwd(pathName);
    printf("First fork: %s\n", pathName);
    if ((pid = fork()) == 0) {
        chdir(path);
        getwd(pathName);
        printf("Second fork: %s\n", pathName);
        exit(0);
    } else {
        getwd(pathName);
        printf("Result fork: %s\n", pathName);
        exit(0);
    }
}
