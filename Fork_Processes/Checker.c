#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int divide(int divisor, int dividend) {
    int p_id = getpid();
    
    printf("Checker process [%d]: Starting.\n", p_id);

    if (dividend % divisor != 0) {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", p_id, dividend, divisor);
        printf("Checker process [%d]: Returning %d.\n", p_id, 0);
        exit(0);
    }
    else {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", p_id, dividend, divisor);
        printf("Checker process [%d]: Returning %d.\n", p_id, 1);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return -1;
    }

    divide(atoi(argv[0]), atoi(argv[1]));
}


