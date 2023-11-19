#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Incorrect number of arguments.\n");
        return -1;
    }

    int shm_ID;
    int shm_array[4];
    pid_t id;
    int fd[2];
    pid_t process_ids[4];
    int *shared_memory_pointer;
    
    for (int i = 2; i < argc; i++) {
        pipe(fd);
        id = fork();

        if (id == -1) printf("Fork failed.\n");
        else if (id == 0) {
            char buffer[8];
            sprintf(buffer, "%d", fd[0]);
            execlp("checker", argv[1], argv[i], buffer, NULL);
            exit(0);
        }
        else {
            process_ids[i - 2] = id;
            shm_ID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
            shm_array[i - 2] = shm_ID;
            if (close(fd[0]) == -1) perror("close");
            if (write(fd[1], &shm_ID, sizeof(shm_ID)) == -1) perror("write");
            if (close(fd[1]) == -1) perror("close");
            printf("Coordinator: forked process with ID %d.\n", id);
            printf("Coordinator: wrote shm ID %d to pipe (%d bytes)\n", shm_ID, (int)sizeof(shm_ID));
        }
    }

    for (int i = 0; i < 4; i++) {
        printf("Coordinator: waiting on child process ID [%d]...\n", process_ids[i]);
        waitpid(process_ids[i], NULL, 0);
        
        shared_memory_pointer = (int*)shmat(shm_array[i], NULL, 0);

        if (*shared_memory_pointer == 1) {
            printf("Coordinator: result 1 read from shared memory: %d is divisible by %d.\n", atoi(argv[i + 2]), atoi(argv[1]));
        } 
        else {
            printf("Coordinator: result 0 read from shared memory: %d is not divisible by %d.\n", atoi(argv[i + 2]), atoi(argv[1]));
        }

        shmctl(shm_array[i], IPC_RMID, NULL);
    }
    
    printf("Coordinator: exiting.\n\n");
    return 0;
}
