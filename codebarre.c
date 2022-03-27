
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "codebarre.h"
#include "pnm.h"
#include "pnm.c"

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
 fil_last_matrix_bloc(Matrix);
 printMatrix(Matrix, DIMESION, DIMESION);
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

void fil_last_matrix_bloc(int **Matrix){
  // assert

  //filling last column
  int sumLine=0, sumColumn=0;
  for (int i = 0; i < DIMESION-10; i+=10) {
    for (int j = 0; j < DIMESION-10; j+=10){
      sumLine += Matrix[i][j];
    }
      printf("sumLine = %d a %d, %d \n", sumLine,i, DIMESION);
      for (int k = i; k < DIMESION-10; k++){
        for (int l = DIMESION-10; l < DIMESION; l++){
          Matrix[k][l] = sumLine%2;
          //Matrix[l][k] = sumColumn%2;
        }
    }
    sumLine=0;
    sumColumn =0;
  }

  // filling last line
  for (int i = 0; i < DIMESION-10; i+=10) {
    for (int j = 0; j < DIMESION-10; j+=10){
      sumColumn += Matrix[j][i];
    }
      printf("sumLine = %d a %d, %d \n", sumLine,i, DIMESION);
      for (int k = i; k < DIMESION-10; k++){
        for (int l = DIMESION-10; l < DIMESION; l++){
          Matrix[l][k] = sumColumn%2;
        }
    }
    sumColumn =0;
  }
}

PNM* create_PNM(int nombre){
  assert(nombre > 0);

  PNM* codebarre = malloc(sizeof(PNM*));
  if(codebarre == NULL)
    return NULL;

  set_nLines(codebarre, DIMESION);
  set_nColumns(codebarre, DIMESION);
  set_maxPix(codebarre, DIMESION);
  set_MagicNumber(codebarre, P1);

  set_Matrix(codebarre, fil_matrix_code(nombre));
  return codebarre;
}

void fil_parity_matrix(int **Matrix, int i, int j, int value){
  //assert
  for(int k=i; k<i; k++){
    for(int t= j; t<j; t++){
      Matrix[k][t] = value;
    }
  }
}

void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump){
  //assert
  for(int k=i; k<jump+i; k++){
    for(int t= j; t<jump+j; t++){
      Matrix[k][t] = value;
    }
  }
}
