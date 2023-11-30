#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int num = atoi(argv[1]);

  for (int i = 0; i <= num; i++){
    if (i%2 == 1){
      printf("%d\n", i);
    }
  }

  return 0;
}