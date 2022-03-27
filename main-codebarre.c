

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "codebarre.c"
#include "pnm.h"

int main(int argc, char const *argv[]) {
  FILE *f = fopen("codebarre.txt", "r");

  int a;
  char* s=malloc(sizeof(char)*200);
  while (!feof(f)){
    fscanf(f, "%d\n", &a);
  }
  int nbits = (int)(log(83)/log(2)) + 1;
  int *binaire = to_binary(83);
  PNM* image = create_PNM(87651234);
  write_pnm(image, "jair.pbm");
  fclose(f);
  return 0;
}
