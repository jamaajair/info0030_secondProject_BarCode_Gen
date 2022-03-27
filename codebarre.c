
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "codebarre.h"
#include "pnm.h"

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
  return binaire;
}

int check_ulg_code(int code){
  assert(code > 0);
  return (code/1000000) == 20; // retourner la partie entiere de la div sur 1 milion
}

int** fil_matrix_code(int nombre){
  assert(nombre > 0);

  // transformer le nombre en code binaire
  int nbits = (int)(log(nombre)/log(2)) + 1;
  int* binaire = to_binary(nombre);
  if (binaire == NULL) // binaire retourne NULL dans le cas d'un nombre
    return NULL;      // qu'est au besoin de plus de 36 bits

  // Allocation dynamique pour la matrice
  int** Matrix = malloc(sizeof(int*) * DIMESION);
  if(Matrix == NULL){
    free(binaire);
    return NULL;
  }
  for (int i = 0; i < DIMESION; i++) {
    Matrix[i] = malloc(sizeof(int)*DIMESION);
    if(Matrix[i] == NULL){
      free(Matrix);
      free(binaire);
      return NULL;
    }
  }//fin for i
  //mettre 0 dans tous les colonnes de la matrice
 fil_bloc_matrix(Matrix, 0, 0, 0, DIMESION);

 // remplissage de la matrice sur la base du tableau binaire
 for (int i = 0; i < DIMESION-10; i= i+10) {
   for (int j = 0; j < DIMESION-10; j= j+10){
     if((((DIMESION-10)/10)*(i/10) +(j/10))<nbits)
         fil_bloc_matrix(Matrix, i, j, binaire[nbits-(((DIMESION-10)/10)*i/10 +j/10)-1], 10);
     }// fin for j
   }// fin for i
 // return de la matrix
 return Matrix;
}

void printMatrix(int **M, int m, int n){
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      printf("%d ",M[i][j] );
    }
    printf("\n");
  }
}

PNM* create_PNM(int nombre){
  assert(nombre > 0);

  return NULL;
}
void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump){
  //assert
  for(int k=i; k<jump+i; k++){
    for(int t= j; t<jump+j; t++){
      Matrix[k][t] = value;
    }
  }
}
