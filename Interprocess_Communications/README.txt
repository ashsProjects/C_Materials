README
======

This package includes the following files.

|-- Coordinator.c [This program will take in 5 arguments and is responsible for launching 4 processes using the Checker program that run concurrently. It uses a pipe to write the shmID to checker, to which it will write the result of the division.]
|-- Checker.c [This program takes in 3 commands and checks whether ot not the divided in divisible by the divisor. It then writes the result to the shared memory using the shmID obtained from the pipe in the buffer.]
|-- README.txt [This file]

To compile:
    Use "make all"

To run:
    ./coordinator <Divisor> <1st Dividend> <2nd> <3rd> <4th>

For example;
    ./coordinator 3 8 15 21 45