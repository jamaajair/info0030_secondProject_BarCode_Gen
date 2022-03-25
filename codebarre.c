
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

void change_to_base2(int nombre, int* binaire, int nbits){
  assert(nombre > 0 && binaire != NULL && nbits < 36);
  while(nombre != 0 && nbits >= 0){
    binaire[--nbits] = nombre%2;
    nombre /= 2;
  }
}

int* to_binary(int nombre){
  assert(nombre > 0 );

  int nbits = (int)(log(nombre)/log(2)) + 1;
  if(nbits-36 > 0 ){
    printf("impossible de chiffrer ce matricule !!\n");
    return NULL;
  }

  int* binaire = malloc(sizeof(int)*(int)nbits);
  if(binaire == NULL){
    return NULL;
  }
  change_to_base2(nombre, binaire, nbits);
  for (size_t i = 0; i < nbits; i++) {
    printf("%d ", binaire[i]);
  }
  return binaire;
}

int check_ulg_code(int code){
  assert(code > 0);
  return (code/1000000) == 20; // retourner la partie entiere de la div sur 1 milion
}

int** fil_matrix_code(int nombre){
  assert(nombre > 0);

  int* binaire = to_binary(nombre);
  // check succes of to_binary
  int** Matrix = malloc(sizeof(int*)*70);
  if(Matrix == NULL)
    free(binaire);
  for (size_t i = 0; i < 70; i++) {
    Matrix[i] = malloc(sizeof(int)*70);
    if(Matrix[i] == NULL){
      free(Matrix);
      free(binaire);
    }
  }
 // fil matrix
  for (int i = 0; i < 70; i+10) {
    for (int j = 0; j < 70; j+10) {

    }
  }

}
