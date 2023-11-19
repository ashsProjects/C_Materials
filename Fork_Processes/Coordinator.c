#include <stdlib.h>
#include <stdio.h>
#include "Checker.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Incorrect number of arguments.\n");
        return -1;
    }

    for (int i = 2; i < argc; i++) {
        pid_t id = fork();
        if (id == -1) {
            printf("Fork failed.\n");
        }
        else if (id == 0) {
            execlp("checker", argv[1], argv[i], NULL);
        }   
        else {
            printf("Coordinator: forked process with ID %d.\n", id);
            printf("Coordinator: waiting for process [%d].\n", id);

            int status;
            wait(&status);
            int result = WEXITSTATUS(status);

            printf("Coordinator: child process %d returned %d.\n", id, result);
        }
    }


    printf("Coordinator: exiting.\n\n");
}