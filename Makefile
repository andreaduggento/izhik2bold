# Makefile for izhik2bold project

# Variables
CC=gcc
CFLAGS=-O9 -I./include  # Remove -lm from here
LDFLAGS=-lpthread -lm   # Add -lm here along with any other libraries to link against
VER=1.0
TASKID=$(shell echo $$TASK)
BINARY=column_$(VER)_taskID$(TASKID).out
CODEDIR=./src/
OUTPUTFILE=output.txt
IDRAN=12345

INPUTFILE=matrices/matID$(TASKID).txt
OUTPUTFILE=synthBold_output/out$(VER)ID$(TASKID)_r$(IDRAN)

# Default target
all: $(BINARY)

$(BINARY): $(CODEDIR)column.c $(CODEDIR)neurons.c
	@if [ -f $(BINARY) ]; then rm $(BINARY); fi
	$(CC) $(CFLAGS) $(CODEDIR)column.c $(CODEDIR)neurons.c $(LDFLAGS) -o $(BINARY)
	@rm -f constants.lock
	@if [ ! -f $(BINARY) ]; then echo "Error while compiling"; else echo "Compilation successful"; fi

run: $(BINARY)
	./$(BINARY) $(OUTPUTFILE) $(IDRAN) < $(INPUTFILE) > /dev/null
	@rm -f $(BINARY)

clean:
	rm -f $(BINARY) constants.lock

.PHONY: all clean run

