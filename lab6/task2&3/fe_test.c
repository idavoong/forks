#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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

int main(){
  //limit_fork(300);

  //create child process 1
  pid_t pid;
  int status;
  pid = fork();

  if (pid < 0){
    perror("could not create child process 1\n");
  } 
  
  if (pid == 0) {
    //child process 1 executes evens program
    char *args[] = {"./evens", "10", NULL};
    execvp("./evens", args);
    exit(0);
  } else {
    //create child process 2
    pid_t pid2 = fork();

    if (pid2 < 0){
      perror("could not create child process 2\n");
    } 
    
    if (pid2 == 0){
      //child process 2 executes odds program
      char *args[] = {"./odds", "10", NULL};
      execvp("./odds", args);
      exit(0);
    } else {
      //parent process waits for both children
      pid_t child1 = waitpid(pid, &status, 0);
      pid_t child2 = waitpid(pid2, &status, 0);
    }
  }

  return 0;
}