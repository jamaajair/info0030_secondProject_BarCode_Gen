

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
//#include "codebarre.c"

int main(int argc, char const *argv[]) {
  FILE *f = fopen("codebarre.txt", "r");

  double a;
  //check_is_ulg_code(f);
  fscanf(f, "%lf", &a);
  double nbits = (log(a)/log(2)) + 1;
  printf("%lf -> %d\n", a, (int)nbits);
  fclose(f);
  return 0;
}
