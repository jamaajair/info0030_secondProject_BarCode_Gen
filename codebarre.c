
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "codebarre.h"

void check_is_ulg_code(FILE *filename){
  assert(filename != NULL);

  char c ;
  fscanf(filename, "%c", &c);
  if(isdigit(c) != 1){
    fscanf(filename, "%*[^\n]\n");
  }
}

int* to_binary(int nombre){
  assert(nombre > 0 && check_ulg_code(nombre) == 1);

  double nbits = (log(nombre)/log(2)) + 1;
  int* binaire = malloc(sizeof(int)*(int)nbits);

  
  return (int)nbits;
}

int check_ulg_code(int code){
  assert(code > 0);
  return (code/1000000) == 20; // retourner la partie entiere de la div sur 1 milion
}

int** fil_matrix_code(int *);
