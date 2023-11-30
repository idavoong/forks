#ifndef HELPER_H
#define HELPER_H
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

//linked list storing curl arguments
struct lineArgs{
    char *fileName;
    char *url;
    char *seconds;
    int line;
    //stores arguments for the next line
    struct lineArgs *next; 
};

typedef struct lineArgs lineArgs;

void createChild(lineArgs *args);

void copyStr(char *arg, char *word);

void freeList(lineArgs *args);

#endif