#include "process.h"
#include "sds/sds.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static sds read_data(int readFd);

void runProcess(const char *filepath) {
    fflush(stdout);

    int fds[2] = {0};
    if (pipe(fds) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    const pid_t pid = fork();
    if (pid < 0) {
        close(fds[0]);
        close(fds[1]);
        perror("fork");
        exit(EXIT_FAILURE);
    }

    const int readFd = fds[0];
    const int writeFd = fds[1];

    if (pid == 0) {
        close(readFd);
        printf("child pid: %d\n", getpid());
        fflush(stdout);
        ssize_t n = 0;
        if ((n = write(writeFd, "from child 1\n", 12)) < 0) {
            perror("write");
            close(writeFd);
            exit(EXIT_FAILURE);
        }
        printf("wrote %ld bytes\n", n);
        close(writeFd);
        // execl(filepath, nullptr);
        // perror("execl");
        exit(EXIT_FAILURE);
    } else {
        close(writeFd);
        printf("from parent pid: %d\n", pid);

        sds data = read_data(readFd);
        printf("data '%s' of len %lu\n", data, sdslen(data));

        int status;
        wait(&status);
        printf("child status: %d\n", WEXITSTATUS(status));
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
