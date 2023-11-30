#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int num = atoi(argv[1]);

  for (int j = 0; j <= num; j++){
    if (j%2 == 0){
      printf("\t%d\n", j);
    }
  }

  return 0;
}