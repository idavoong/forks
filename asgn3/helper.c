#define  _GNU_SOURCE
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

void createChild(lineArgs *args){
    pid_t pid;
    pid = fork();

    if (pid < 0){
        perror("could not create a child process\n");
        exit(1);
    } else if(pid == 0){
        char *cmd[] = {"curl", "-o", args->fileName, "-s", args->url, NULL, NULL, NULL};
        if (args->seconds != NULL){
            cmd[5] = "-m";
            cmd[6] = args->seconds;
        }
        execvp("curl", cmd);
    } else {
        printf("process %d process line #%d (parent: %d)\n", pid, args->line, getpid());
    }
}

void copyStr(char *arg, char *word){
    int i = 0;
    while (word[i] != '\0'){
        arg[i] = word[i];
        i += 1;
    }
    arg[i] = '\0';
}

void freeList(lineArgs *args){
    lineArgs *next;

    free(args->fileName);
    free(args->url);
    if (args->seconds != NULL){
        free(args->seconds);
    }
    next = args->next;

    args = next;

    while (args != NULL){
        free(args->fileName);
        free(args->url);
        if (args->seconds != NULL){
            free(args->seconds);
        }

        next = args->next;
        free(args);

        args = next;
    }
}
