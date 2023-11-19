#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //Checking if the correct nums of args given
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return -1;
    }
    //checking if argv[1] is a proper pid
    char *input = argv[1];
    char *endptr;
    strtol(input, &endptr, 10);
    if (*endptr != '\0' || endptr == input) {
        fprintf(stderr, "Error: %s is not a valid Process ID.\n", input);
        return 1;
    }
    //creating the filepath with the process id
    char file_path_stat[20] = "/proc/";
    char file_path_statm[20] = "/proc/";
    char stat[] = "/stat";
    char statm[] = "/statm";

    strcat(file_path_stat, argv[1]);
    strcat(file_path_stat, stat);
    strcat(file_path_statm, argv[1]);
    strcat(file_path_statm, statm);

    //reading from stat
    FILE *stat_file = fopen(file_path_stat, "r");
    if (stat_file == NULL) {
        fprintf(stderr, "Error: Process is not currently active\n");
        return 1;
    }
    char executable[128], state;
    int ppid, pgrp;
    unsigned long min_fault, max_fault, user_mode, kernel_mode, total_fault;
    fscanf(stat_file, "%*d %s %c %d %d %*d %*d %*d %*u %lu %*lu %lu %*lu %lu %lu", 
            &executable, &state, &ppid, &pgrp, &min_fault, &max_fault, &user_mode, &kernel_mode);
    total_fault = min_fault + max_fault;
    double user_mode_secs = (double) user_mode / (sysconf(_SC_CLK_TCK));
    double kernel_mode_secs = (double) kernel_mode / (sysconf(_SC_CLK_TCK));

    //reading from statm
    FILE *statm_file = fopen(file_path_statm, "r");
    if (statm_file == NULL) {
        fprintf(stderr, "Error: Process is not currently active\n");
    }
    int resident_pages, shared_pages, virtual_memory;
    fscanf(statm_file, "%d %d %d", &virtual_memory, &resident_pages, &shared_pages);
    
    //printing to console
    printf("[./profiler] checking pid %s\n", argv[1]);
    printf("Executable: \t%s\n", executable);
    printf("ppid: \t\t%d\n", ppid);
    printf("pgrp: \t\t%d\n", pgrp);
    printf("State: \t\t%c\n", state);
    printf("User mode: \t%.3f sec\n", user_mode_secs);
    printf("Kernel mode: \t%.3f sec\n", kernel_mode_secs);
    printf("Virtual memory: %d bytes\n", virtual_memory);
    printf("Resident pages: %d\n", resident_pages);
    printf("Shared pages: \t%d\n", shared_pages);
    printf("Page faults: \t%lu\n", total_fault);
    
    return 0;
}