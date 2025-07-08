#include "Program.h"
#include "sds/sds.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static sds read_data(int readFd);

ProgramResult runProgram(const char *filepath, const char *arg) {
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
        dup2(writeFd, STDERR_FILENO);
        close(writeFd);
        execl(filepath, arg, nullptr);
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        close(writeFd);
        sds data = read_data(readFd);
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
        while ((n = read(readFd, buffer, 1024))) {
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
