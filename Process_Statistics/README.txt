README
======

This package includes the following files.

|-- Profiler.c []
|-- README.txt [This file]

To compile:
    make all

To run:
    ./profiler $<process>

For example:
    ./profiler $(pgrep -n chrome)