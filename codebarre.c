
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "codebarre.h"
#include "pnm.h"

int check_is_ulg_code(char* regestrationNumber){
  assert(regestrationNumber != NULL);
  if(strlen(regestrationNumber) != 8)
    return -1;
  for (size_t i = 0; i < strlen(regestrationNumber); i++) {
      if(regestrationNumber[i] =='0' || regestrationNumber[i] =='1' || regestrationNumber[i] =='2' ||
         regestrationNumber[i] =='3' || regestrationNumber[i] =='4' || regestrationNumber[i] == '5'||
         regestrationNumber[i] == '6'|| regestrationNumber[i] == '7' || regestrationNumber[i] == '8'||
         regestrationNumber[i]=='9'){
      return 1;
      }
  }
  return -1;
}

void change_to_base2(int number, int* binary, int nbits){
  assert(number > 0 && binary != NULL && nbits < 36);
  while(number != 0 && nbits >= 0){
    binary[--nbits] = number%2;
    number /= 2;
  }
}

int* to_binary(int number){
  assert(number > 0 );

  int nbits = (int)(log(number)/log(2)) + 1;
  if(nbits-36 > 0 ){
    printf("impossible de chiffrer ce matricule !!\n");
    return NULL;
  }

  int* binary = malloc(sizeof(int)*(int)nbits);
  if(binary == NULL){
    return NULL;
  }
  change_to_base2(number, binary, nbits);
  return binary;
}

char* get_file_name(char* path){
  assert(path != NULL);
  int length = strlen(path);
  int i = length;
  while(i >=0 && path[i] != '/')
        i--;
  if (check_filename(&path[i+1]) == 1) {
    return &path[i+1];
  }
  return NULL;
}

int** fil_matrix_code(int number){
  assert(number > 0);

  // transformer le nombre en code binaire
  int nbits = (int)(log(number)/log(2)) + 1;
  int* binary = to_binary(number);
  if (binary == NULL) // binaire retourne NULL dans le cas d'un number
    return NULL;      // qu'est au besoin de plus de 36 bits

  // Allocation dynamique pour la matrice
  int** Matrix = malloc(sizeof(int*) * DIMESION);
  if(Matrix == NULL){
    free(binary);
    return NULL;
  }
  for (int i = 0; i < DIMESION; i++) {
    Matrix[i] = malloc(sizeof(int)*DIMESION);
    if(Matrix[i] == NULL){
      free(Matrix);
      free(binary);
      return NULL;
    }
  }//fin for i
  //mettre 0 dans tous les colonnes de la matrice
 fil_bloc_matrix(Matrix, 0, 0, 0, DIMESION);

 // remplissage de la matrice sur la base du tableau binaire
 for (int i = 0; i < DIMESION-10; i= i+10) {
   for (int j = 0; j < DIMESION-10; j= j+10){
     if((((DIMESION-10)/10)*(i/10) +(j/10))<nbits)
         fil_bloc_matrix(Matrix, i, j, binary[nbits-(((DIMESION-10)/10)*i/10 +j/10)-1], 10);
     }// fin for j
   }// fin for i
 // return de la matrix
 fil_last_matrix_bloc(Matrix);
 //printMatrix(Matrix, DIMESION, DIMESION);
 return Matrix;
}

void fil_last_matrix_bloc(int **Matrix){
  assert(Matrix != NULL);

  //filling last column
  int sumLine=0, sumColumn=0;
  for (int i = 0; i < DIMESION-10; i+=10) {
    for (int j = 0; j < DIMESION-10; j+=10){
      sumLine += Matrix[i][j];
    }
      for (int k = i; k < DIMESION-10; k++){
        for (int l = DIMESION-10; l < DIMESION; l++){
          Matrix[k][l] = sumLine%2;
          //Matrix[l][k] = sumColumn%2;
        }
    }
    sumLine=0;
  }

  // filling last line
  for (int i = 0; i < DIMESION-10; i+=10) {
    for (int j = 0; j < DIMESION-10; j+=10){
      sumColumn += Matrix[j][i];
    }
      for (int k = i; k < DIMESION-10; k++){
        for (int l = DIMESION-10; l < DIMESION; l++){
          Matrix[l][k] = sumColumn%2;
        }
    }
    sumColumn =0;
  }
}

PNM* create_PNM(int number){
  assert(number > 0);

  PNM* barCode = malloc(sizeof(PNM*));
  if(barCode == NULL)
    return NULL;

  set_nLines(barCode, DIMESION);
  set_nColumns(barCode, DIMESION);
  set_maxPix(barCode, DIMESION);
  set_MagicNumber(barCode, P1);

  set_Matrix(barCode, fil_matrix_code(number));
  return barCode;
}

void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump){
  //assert
  for(int k=i; k<jump+i; k++){
    for(int t= j; t<jump+j; t++){
      Matrix[k][t] = value;
    }
  }
}
