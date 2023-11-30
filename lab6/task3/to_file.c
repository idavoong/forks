#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    //check for arguments
    if (argv[1] == NULL){
        perror("argument 1 not provided");
    }
    if (argv[2] == NULL){
        perror("argument 2 not provided");
    }

    //opening file
    int fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (fd == -1){
        perror("file could not be opened");
        exit(1);
    }

    int newfd = dup2(fd, STDOUT_FILENO);
    if (newfd == -1){
        perror("dup2 failed");
        exit(1);
    }
    close(fd);

    //execute program
    char *args[] = {argv[1], NULL};
    execvp(argv[1], args);

    return 0;
}
