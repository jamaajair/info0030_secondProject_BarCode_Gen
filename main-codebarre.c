

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "codebarre.c"

int main(int argc, char const *argv[]) {
  FILE *f = fopen("codebarre.txt", "r");

  int a;
  char* s=malloc(sizeof(char)*200);
  //check_is_ulg_code(f);
  //fscanf(f, "%s", s);
  while (!feof(f)){
    fscanf(f, "%d\n", &a);
    //printf("%d\n",a );
  }
  int nbits = (int)(log(83)/log(2)) + 1;
  int *binaire = to_binary(83);
  //printf("%lf -> %d\n", a, (int)nbits);
  fclose(f);
  return 0;
}
