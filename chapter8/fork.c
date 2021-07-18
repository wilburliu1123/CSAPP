#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
int main () {

    pid_t pid;
    int x = 1;

    if ((pid = fork()) < 0) {
        printf("error");
    }
    if (pid == 0) {
        printf("child: x=%d\n", ++x);
    }

    printf("parent: x=%d\n", --x);
    exit(0);
}
