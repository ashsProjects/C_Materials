# Compiler and loader commands and flags
GCC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = Profiler.c
EXECUTABLE = profiler

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	rm -f *.zip $(EXECUTABLE)
	
# Packages directory files into .zip file
package:
	zip -r Ayush_Adhikari_ExtraCredit.zip Profiler.c Makefile README.txt