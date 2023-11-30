CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
MAIN = program
OBJS = program.o helper.o

all : $(MAIN)

$(MAIN) : $(OBJS) helper.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

program.o : program.c helper.c
	$(CC) $(CFLAGS) -c program.c

helper.o : helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

clean :
	rm *.o $(MAIN) core