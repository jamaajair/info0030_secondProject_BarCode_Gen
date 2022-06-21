/**
 * \file codebarre.c
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/03/2022
 *
 * Ce fichier contient les implémentations
 *  et les prototypes des fonctions pour coder les matricules des étudiants de l'ULG.
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "codebarre.h"
#include "pnm.h"


#define SIZE 1024

int generate_code_barre(char *input_file, char* output_folder){
  assert(input_file != NULL && output_folder != NULL);

  FILE *file = fopen(input_file, "r");


  if(file == NULL){
    printf("le fichier input non trouvé ");
    return -1;
  }

  char code[SIZE];

  while(!feof(file)){

    /* l'utilisation de fgets ou lieu de fscanf car fscanf ignore
      les espaces au debut et a la fin d une ligne ainsi les lignes vide
      ce qui ne nous permet pas de faire un bonne detection d'un fichier mal forme */

    if(fgets(code, SIZE,file )){
      if (check_is_ulg_code(code) != 1){
        printf("le fichier est mal formé !!\n");
        return 0;
      }

      //convertir du code lu en int
      int codeNumber = atoi(code);

      // la creation de l'image PNM
      PNM* image = malloc(sizeof(PNM*));
      if(image == NULL){
        fclose(file);
        printf("impossible d'ecrire une image dans la memoire \n");
        return 0;
      }
      image = create_PNM(codeNumber);

      // generer le fichier qui represente le code barre avec son nom
      char *codeName = malloc(sizeof(char)*MAX_SIZE);
      if(codeName == NULL){
        fclose(file);
        free_image(image);
        printf("ERREUR: dans la generation du nom du fichier\n");
        return 0;
      }

      //genere l endroit ou l'image va etre enregistrer
      char path[SIZE];
      strcpy(path, output_folder);
      codeName = generate_file_name(code);
      strcat(output_folder, "/");
      strcat(output_folder, codeName);

      // enregistrer le codebarre dans chemin fournit par l'utilisateur
      DIR *dp = opendir(path);

      // le dossier output existe deja
      if(dp){
        printf("dossier existe \n");
        if(write_pnm(image, output_folder) != 0){
          printf("ERREUR: dans le Sauvegarde de l'image \n");
          fclose(file);
          free(codeName);
          free_image(image);
          return 0;
        }
      }else if(ENOENT == errno){ // le dossier n'existe pas
        printf("dossier n existe pas on le creer\n");
        mkdir(path, 0700); // mkdir pour creer le dossier avec droits d acces RWX=700
        if(write_pnm(image, output_folder) != 0){
          printf("ERREUR: dans le Sauvegarde de l'image \n");
          fclose(file);
          free(codeName);
          free_image(image);
          return 0;
        }
      }

      // free la memoire
      free_matrix(image);
      free(image);
      free(codeName);
    }
  }
  fclose(file);
  return 1;
}

int check_is_ulg_code(char* regestrationNumber){
  assert(regestrationNumber != NULL);

  unsigned int UlgCodeSize =  8;
  unsigned int length = strlen(regestrationNumber);

  // verification si la taille du code different de 8
  if((length-1) != UlgCodeSize){
    printf("le code ne contient pas exactement 8 éléments- fichier mal formé\n");
    return -1;
  }

  // verification si une matricule n'est pas vide ou une tabulation
  if(regestrationNumber[0] == ' '){
    printf("la ligne commence par un caractere vide - fichier mal formé");
    return -1;
  }

  // verification si une matricule n'est pas vide ou une tabulation
  if(regestrationNumber[0] == '\n'){
    printf("la ligne commence par une ligne vide - fichier mal formé\n");
    return -1;
  }

  // verification si une matricule n'est pas vide ou une tabulation
  if(regestrationNumber[0] == '\r'){
    printf("la ligne commence par une tabulation - fichier mal formé\n");
    return -1;
  }


  // verf si la UlgCode contient d'autres elements que des digits
  for (unsigned int i = 0; i < length-1; i++) {
    if( !isdigit(regestrationNumber[i]) || regestrationNumber[i] == ' '
        || regestrationNumber[i] == '\r'){
        printf("le matricule contient des non digits - fichier mal formé\n");
        return -1;
    }

  }

  return 1;
}

char* generate_file_name(char *code){
  assert(code != NULL);

  int length = strlen(code);
  char *name = malloc(sizeof(char)*length+4);
  if(name == NULL){
    return NULL;
  }
  strcpy(name, code);

  name[length-1] = '.';
  name[length] = 'p';
  name[length+1] = 'b';
  name[length+2] = 'm';
  name[length+3] = '\0';

  return name;
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
  set_maxPix(barCode, 0);
  set_MagicNumber(barCode, P1);

  set_Matrix(barCode, fil_matrix_code(number));
  return barCode;
}

void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump){
  assert(Matrix != NULL && i>= 0 && j>= 0 && jump >=0);

  for(int k=i; k<jump+i; k++){
    for(int t= j; t<jump+j; t++){
      Matrix[k][t] = value;
    }
  }
}
