#include "ProgramResult.h"
#include "sds/sds.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static sds read_data(int readFd);

ProgramResult runProgram(const char *filepath) {
    fflush(stdout);

    int fds[2] = {0};
    if (pipe(fds) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    const int readFd = fds[0];
    const int writeFd = fds[1];

    const pid_t pid = fork();
    if (pid < 0) {
        close(readFd);
        close(writeFd);
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(readFd);
        dup2(writeFd, STDOUT_FILENO);
        close(writeFd);
        execl(filepath, nullptr);
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        close(writeFd);
        printf("from parent pid: %d\n", pid);

        sds data = read_data(readFd);
        printf("data '%s' of len %lu\n", data, sdslen(data));

        int status;
        wait(&status);
        return (ProgramResult){
            .exitStatus = WEXITSTATUS(status),
            .output = data
        };
    }
}

static sds read_data(const int readFd) {
    sds data = sdsempty(); {
        ssize_t n = 0;
        char buffer[1024];
        while ((n = read(readFd, buffer, 12))) {
            if (n < 0) {
                perror("read");
                close(readFd);
                exit(EXIT_FAILURE);
            }
            if (n == 0) {
                break;
            }
            data = sdscatlen(data, buffer, n);
        }
    }
    return data;
}
