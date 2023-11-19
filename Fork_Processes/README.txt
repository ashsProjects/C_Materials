README
======

This package includes the following files.

|-- Coordinator.c [This program will take in 5 arguments and is responsible for launching 4 processes using the Checker program]
|-- Checker.c [This program takes in 2 commands and checks whether ot not the divided in divisible by the divisor]
|-- Checker.h [Header file declaring the function exposed from Checker.c]
|-- README.txt [This file]

To compile:
    Use "make all"

To run:
    coordinator <Divisor> <1st Dividend> <2nd> <3rd> <4th>

For example;
    coordinator 3 8 15 21 45