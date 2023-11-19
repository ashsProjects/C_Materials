#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int divide(int divisor, int dividend) {
    int p_id = getpid();
    
    if (dividend % divisor != 0) {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", p_id, dividend, divisor);
        printf("Checker process [%d]: wrote result (%d) to shared memory.\n", p_id, 0);
        return 0;
        
    }
    else {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", p_id, dividend, divisor);
        printf("Checker process [%d]: wrote result (%d) to shared memory.\n", p_id, 1);
        return 1;
        
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Incorrect number of arguments.\n");
        return -1;
    }

    int p_id = getpid();
    int fd = atoi(argv[2]);
    int shm_ID;
    int size = sizeof(int);

    read(fd, &shm_ID, size);  

    printf("Checker process [%d]: starting.\n", p_id);
    printf("Checker process [%d]: read %d bytes containing shm ID %d\n", p_id, size, shm_ID);

    int exit_code = divide(atoi(argv[0]), atoi(argv[1]));
    int *shared_memory_pointer = (int*)shmat(shm_ID, NULL, 0);
    
    *shared_memory_pointer = exit_code;

    if (shmdt(shared_memory_pointer) == -1) perror("shmdt");
    if (close(fd) == -1) perror("close");
    
}


