#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

void limit_fork(rlim_t max_procs){
  struct rlimit rl;

  if (getrlimit(RLIMIT_NPROC, &rl)){
    perror("getrlimit");
    exit(-1);
  }

  rl.rlim_cur = max_procs;

  if (setrlimit(RLIMIT_NPROC, &rl)){
    perror("setrlimit");
    exit(-1);
  }
}

int main(int argc, char *argv[]){
  // limit_fork(300);
  if (argv[1] == NULL){
    perror("no argument provided");
  }

  //convert string to int
  int num = atoi(argv[1]);
  //strtol

  pid_t pid;
  pid = fork();

  if (pid < 0){
    perror("could not create a child process\n");
  } else if (pid == 0){
    for (int i = 0; i <= num; i++){
      if (i%2 == 1){
        printf("%d\n", i);
      }
    }
  } else {
    for (int j = 0; j <= num; j++){
      if (j%2 == 0){
        printf("\t%d\n", j);
      }
    }
    wait(NULL);
  }

  return 0;
}
