#define  _GNU_SOURCE
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

//global var for linked list
lineArgs *processArg;

int main(int argc, char *argv[]) {
    //check if command arguments exist
    if (argv[1] == NULL){
        perror("no file entered");
        exit(1);
    }
    if (argv[2] == NULL) {
        perror("no number entered");
        exit(1);
    }

    //check if file opened successfully
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        perror("file couldn't be opened");
        exit(1);
    }

    //check if max number of processes entered is valid
    //store max number of processes to run
    int processes; 
    processes = strtol(argv[2], NULL, 10); 
    if (processes == 0){
        perror("enter a valid number of processes to run\n");
        exit(1);
    }
    if (processes < 0){
        perror("enter a positive integer\n");
        exit(1);
    }

    //initializing pointer to 
    lineArgs *head;
    lineArgs arguments;
    head = &arguments;

    //variables for getline and strtok
    size_t bufsize = 0;
	char *buffer = NULL;
    ssize_t characters = 0;
    char *word;
    int line = 1; //keep track of what line the program is reading

    
    lineArgs *curArg = head;
    characters = getline(&buffer, &bufsize, fp); //read line
    while (characters != -1){
        //store file name
        word = strtok(buffer, " ");
        curArg->fileName = malloc((strlen(word) + 1) * sizeof(char));
        copyStr(curArg->fileName, word);

        //store url
        word = strtok(NULL, " \n");
        curArg->url = malloc((strlen(word) + 1) * sizeof(char));
        copyStr(curArg->url, word);

        //store seconds (optional)
        word = strtok(NULL, " \n");
        if (word != NULL) {
            curArg->seconds = malloc((strlen(word) + 1) * sizeof(char));
            copyStr(curArg->seconds, word);
        } else {
            curArg->seconds = NULL;
        }

        //store current line number
        curArg->line = line;
        line += 1;
        
        characters = getline(&buffer, &bufsize, fp);
        if (characters == -1){  //set curArg->next to NULL if there are no more lines to read
            curArg->next = NULL;
        } else { //create struct and set its address to curArg->next
            lineArgs *temp = malloc(sizeof(lineArgs));
            curArg->next = temp;
        }
        curArg = curArg->next;
    }

    //first line for processing
    processArg = head;

    //creating child processes up to max allowed
    for (int j = 0; j < processes; j++){
        createChild(processArg);
        processArg = processArg->next;
    }

    //wait for a child process to end before starting the next one
    while (processArg != NULL){
        wait(NULL);
        printf("finish download\n");
        createChild(processArg);
        processArg = processArg->next;
    }

    //
    for (int k = 0; k < processes; k++){
        wait(NULL);
        printf("finish download\n");
    }

    //free linked list
    lineArgs *freeArg = head;
    freeList(freeArg);

    free(buffer);

    fclose(fp);
    return 0;
}