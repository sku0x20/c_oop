#include "process.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void runProcess(const char *filepath) {
    fflush(stdout);

    const pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        printf("child pid: %d\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        printf("from parent pid: %d\n", pid);
        int status;
        wait(&status);
        printf("child status: %d\n", WEXITSTATUS(status));
    }
}
