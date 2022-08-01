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

int check_is_ulg_code(char* regestrationNumber){
  assert(regestrationNumber != NULL);

  unsigned int UlgCodeSize =  8; // la taille par defaut d'un matricule ULG
  unsigned int length = strlen(regestrationNumber); // getting la taille du matricule passé en arg 

  // verification si la taille du code different de 8
  if((length-1) != UlgCodeSize){
    printf("\nle code ne contient pas exactement 8 éléments- fichier mal formé\n");
    return -1;
  }

  // verification si une matricule n'est pas vide ou une tabulation
  if(regestrationNumber[0] == ' '){
    printf("\nla ligne commence par un caractere vide - fichier mal formé\n");
    return -1;
  }

  // verification si une matricule n'est pas vide ou une tabulation
  if(regestrationNumber[0] == '\n'){
    printf("\nla ligne commence par une ligne vide - fichier mal formé\n");
    return -1;
  }

  // verification si une matricule n'est pas vide ou une tabulation
  if(regestrationNumber[0] == '\r'){
    printf("\nla ligne commence par une tabulation - fichier mal formé\n");
    return -1;
  }


  // verf si la UlgCode contient d'autres elements que des digits
  for (unsigned int i = 0; i < length-1; i++) {
    if( !isdigit(regestrationNumber[i]) || regestrationNumber[i] == ' '
        || regestrationNumber[i] == '\r'){
        printf("\nle matricule contient des non digits - fichier mal formé\n");
        return -1;
    }
  }

  return 1;
}// fin verification 

int generate_code_barre(char *input_file, char* output_folder){
  assert(input_file != NULL && output_folder != NULL);

  FILE *file = fopen(input_file, "r"); // ouvrir le fichier en mode lecture

  if(file == NULL){
    return -1;
  } // fin test le resultat d'ouverture

  char code[SIZE];

  while(!feof(file)){

    /* l'utilisation de fgets ou lieu de fscanf car fscanf ignore
      les espaces au debut et a la fin d une ligne ainsi les lignes vide
      ce qui ne nous permet pas de faire un bonne detection d'un fichier mal forme */

    if(fgets(code, SIZE,file )){
      if (check_is_ulg_code(code) != 1){
        printf("\nle fichier est mal formé !!\n");
        return 0;
      }

      //convertir du code lu en int
      int codeNumber = atoi(code);

      // la creation de l'image PNM
      PNM* image = malloc(sizeof(PNM*));
      if(image == NULL){
        fclose(file);
        printf("\nimpossible d'ecrire une image dans la memoire \n");
        return 0;
      }
      image = create_PNM(codeNumber);

      // generer le fichier qui represente le code barre avec son nom
      char *codeName = malloc(sizeof(char)*MAX_SIZE);
      if(codeName == NULL){
        fclose(file);
        free_image(image);
        printf("\nERREUR: dans la generation du nom du fichier\n");
        return 0;
      }

      //genere l endroit ou l'image va etre enregistrer
      char path[SIZE];
      strcpy(path, output_folder);
      codeName = generate_file_name(code);
      
      strcat(strcat(path, "/"), codeName);

      //if(chdir("output_folder") == 0){
        if(write_pnm(image, codeName) != 0){
          printf("\n\nERREUR: dans le Sauvegarde de l'image %d \n", write_pnm(image, output_folder));
          fclose(file);
          free(codeName);
          free(output_folder);
          free_image(image);
          return 0;
        }
        printf("\n\n\t*** le code barre %s est disponible ***\n", codeName);
      }
    }
  fclose(file);
  return 1;
}// fin la generation des codes barres (PBM)

int fix_bar_code(char* barcode_to_fixe,char* barcode_fixed){
  assert(barcode_to_fixe != NULL && barcode_fixed != NULL);

  //chargé en mémoire l'image a corriger
  PNM* barcode;
  if(load_pnm(&barcode, barcode_to_fixe) != 0){
    printf("\n\nerreur dans le téléchargement de l'image à corriger\n");
    free(barcode);
    return -1;
  }// fin if

  // verifier si le barecode a fixé a une matrice carré
  if(get_nColumns(barcode) != get_nLines(barcode)){
    printf("\n\nerreur la matrice de l'image fournit n'est pas carre\n");
    free(barcode);
    return -2;
  }// fin if 

  //  chargé en memoire la matrice de l'image a corriger
  int **matrix = malloc(sizeof(int*)*(get_nLines(barcode)/10));
  if(matrix == NULL){
    printf("\n\nerreur dans l'alocation d'espace memoire\n");
    free(barcode);
    return -3;
  } // fin if (test du malloc)

  for(int i = 0; i < get_nLines(barcode)/10; i++){
    matrix[i] = malloc(sizeof(int)*(get_nLines(barcode)/10));
    if(matrix[i] == NULL){
      printf("\n\nerreur dans l'alocation d'espace memoire\n");
      free(barcode);
      free(matrix);
      return -3;
    }// fin if (test du malloc)
  }// fin for
  
  // Mets a coté la matrice de l'image
  int **InputFileMatrix = get_matrix(barcode);
  if(InputFileMatrix == NULL){
    printf("\n\nerreur dans l'image fournit\n");
    free(barcode);
    free(matrix);
    return -4;
  }// fin if 

  //remplissage de la matrice du codebarre
  for (int i = 0; i < get_nLines(barcode); i+=10)
  {
    for (int j = 0; j < get_nLines(barcode); j+=10)
    {
      matrix[i/10][j/10] = InputFileMatrix[i][j]; 
    }// fin for j
  }// fin for i
  
  // la correction de la matrice 
  int good_line, bad_line;
  int good_column, bad_column;

  for (int i = 0; i < (get_nLines(barcode)/10); i++)
  {
    if(check_line_parity(matrix, i, get_nLines(barcode)/10) != 1){
      good_line = 0;
      bad_line = i;
    }else{
      good_line = 1;
      bad_line = 0;
    } // fin test la parite de la ligne i

    // testing la partie inf droite
    for (int j = 0; j < (get_nLines(barcode)/10); j++)
    {
      if(check_column_parity(matrix, j, (get_nLines(barcode)/10)) != 1){
        good_column = 0;
        bad_column = j;
      }else{
        good_column = 1;
        bad_column = 0;
      }// fin test de parite de la colonne j

      //correction, j inverse dans le cas ou la ligne i et la colonne j ont une mauvise parité
      if(check_line_parity(matrix, i, get_nLines(barcode)/10) != 1 && check_column_parity(matrix, j, (get_nLines(barcode)/10)) != 1){
        matrix[i][j] = 1-matrix[i][j];
      }// fin correction
    }
      
  }

  //colonne est bonne mais la ligne est mauvaise 
    if(good_column == 1 && good_line == 0){
      matrix[bad_line][(get_nLines(barcode)/10)-1] = 1 - matrix[bad_line][(get_nLines(barcode)/10)-1];
    }// fin if

    //ligne est bonne mais la colonne non
    if(good_line == 1 && good_column == 0){
      matrix[(get_nLines(barcode)/10)-1][bad_column] = 1 - matrix[(get_nLines(barcode)/10)-1][bad_column];
    }// fin if 
    
    //regardons la partie en bas droite
    int line_sum = 0;
    int column_sum = 0;

    for (int i = 0; i < get_nLines(barcode)/10; i++)
    {
      line_sum += matrix[i][(get_nLines(barcode)/10)-1]; // somme de la ligne en bas
      column_sum += matrix[(get_nLines(barcode)/10)-1][i]; // somme de la colonne a droite
    }
  
    /* le pixel en bas a droite le cas ou la ligne est bonne ainsi la colonne mais la parité en 
     bas a droite est mauvais */
    if(good_line == 1 && good_column == 1 && (line_sum % 2) != 0 && (column_sum % 2) != 0)
      matrix[get_nLines(barcode)-1][get_nColumns(barcode)-1] = 1 -  matrix[get_nLines(barcode)-1][get_nColumns(barcode)-1];
    
    // testing que la matrice est bien corrigee 
    /*for (int i = 0; i < get_nLines(barcode)/10; i++)
    {
      for (int j = 0; j < get_nLines(barcode)/10; j++)
    {
      //printf("\n%d ", matrix[i][j]);
    }
    //printf("\n\n");
    }*/

    // corriger la matrice Input a partir de la matrice intermediere matrix
    for (int i = 0; i < get_nLines(barcode)/10; i++)
    {
      for (int j = 0; j < get_nColumns(barcode)/10; j++)
      {
        fil_bloc_matrix(InputFileMatrix, i*10, j*10, matrix[i][j], 10);
      }// fin for
    } // fin for
    
    //testing si la matrice est bien corrigee
    /*for (int i = 0; i < get_nLines(barcode); i++)
    {
      for (int j = 0; j < get_nLines(barcode); j++)
    {
      //printf("\n%d ", InputFileMatrix[i][j]);
    }
    //printf("\n\n");
    }*/

    set_Matrix(barcode, InputFileMatrix); // affecter la matrice corrige au fichier PNM a corriger
    
    // libere la matrice intermediaire utilise pour la correction
    for(int i=0; i<get_nColumns(barcode)/10; i++){
      free(matrix[i]);
    }
    free(matrix); // fin 

    // libere la matrice InputfileMatrix
    for(int i=0; i<get_nColumns(barcode); i++){
      free(InputFileMatrix[i]);
    }
    free(InputFileMatrix); // fin
     
    int result = write_pnm(barcode, barcode_fixed); // generer le fichier corrigé 
    //free_image(barcode); // libere le codebarre
  return result;
} // fin de la fonction de la correction

int check_line_parity(int **matrix, int line_index, int matrix_dimension){
  assert(matrix != NULL && line_index >= 0 && matrix_dimension > 0);
  
  int sum = 0;
  for(int i=0; i<matrix_dimension-1; i++){
    sum += matrix[line_index][i];
  }// fin for i

  return ((sum%2) == 0);
}// fin check_line_parity

int check_column_parity(int **matrix, int column_index, int matrix_dimension){
  assert(matrix != NULL && column_index >= 0 && matrix_dimension > 0);
  
  int sum = 0;
  for(int i=0; i<matrix_dimension-1; i++){
    sum += matrix[i][column_index];
  }// fin for i

  return ((sum%2) == 0);
}// fin check_column_parity

char *generate_file_name(char *code){
  assert(code != NULL);

  int length = strlen(code); // getting la taille du code 
  char *name = malloc(sizeof(char) * length + 4);
  if (name == NULL)
  {
    return NULL;
  } // fin verification le resultat du malloc

  strcpy(name, code);

  // ajout de l'extension PBM au nom du fichier a genere
  name[length - 1] = '.';
  name[length] = 'p';
  name[length + 1] = 'b';
  name[length + 2] = 'm';
  name[length + 3] = '\0';

  return name;
}// fin generate_file_name

void change_to_base2(int number, int* binary, int nbits){
  assert(number > 0 && binary != NULL && nbits < 36);

  while(number != 0 && nbits >= 0){
    binary[--nbits] = number%2;
    number /= 2;
  }// fin while
}// fin change_to_base2

int* to_binary(int number){
  assert(number > 0 );

  int nbits = (int)(log(number)/log(2)) + 1;
  if(nbits-36 > 0 ){
    printf("\nimpossible de chiffrer ce matricule !!\n");
    return NULL;
  } // fin if

  int* binary = malloc(sizeof(int)*(int)nbits);
  if(binary == NULL){
    return NULL;
  } // fin if

  // appel pour generer le codage binaire
  change_to_base2(number, binary, nbits);
  return binary;
}//fin to_binary

char* get_file_name(char* path){
  assert(path != NULL);

  int i = strlen(path); // getting la taille du path
  while(i >=0 && path[i] != '/')
        i--;
  // fin while
  if (check_filename(&path[i+1]) == 1) {
    return &path[i+1];
  }// fin if

  return NULL;
}// fin get_file_name

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
} // fin fil_matrix

void fil_last_matrix_bloc(int **Matrix){
  assert(Matrix != NULL);

  //filling last column
  int sumLine=0, sumColumn=0;
  for (int i = 0; i < DIMESION-10; i+=10) {
    for (int j = 0; j < DIMESION-10; j+=10){
      sumLine += Matrix[i][j];
    }// fin for j
      for (int k = i; k < DIMESION-10; k++){
        for (int l = DIMESION-10; l < DIMESION; l++){
          Matrix[k][l] = sumLine%2;
        }// fin for l
      }// fin for k
    sumLine=0;
  } // fin for i

  // filling last line
  for (int i = 0; i < DIMESION-10; i+=10) {
    for (int j = 0; j < DIMESION-10; j+=10){
      sumColumn += Matrix[j][i];
    } // fin for j
      for (int k = i; k < DIMESION-10; k++){
        for (int l = DIMESION-10; l < DIMESION; l++){
          Matrix[l][k] = sumColumn%2;
        } // fin for l
      }// fin for k
    sumColumn =0;
  }// fin for i

  // appel a la procedure pour remplir le bloc en bas a droite
  fil_bloc_down_right(Matrix);
  
}// fin fil_last_bloc_matrix

void fil_bloc_down_right(int **Matrix){
  assert(Matrix != NULL);

  //getting parity of last column and last line
  int sum_column = 0;
  int sum_line = 0;
  for (int i = 0; i < DIMESION-10; i+=10)
  {
    sum_column += Matrix[i][DIMESION-10];
    sum_line += Matrix[DIMESION-10][i];
  }// fin for i

  /* Remplissage bu bloc en bas a droite pas besoin de remplir le 
   cas de 0 cas la matrice est deja contient des 0 de bas */
  if(sum_column%2 != 0 && sum_line != 0){
    for (int i = DIMESION-10; i < DIMESION; i++)
    {
      for (int j = DIMESION-10; j < DIMESION; j++)
      {
        Matrix[i][j] = 1;
      }//fin for i
      
    }//fin for j
    
  }// fin if
  
} // fin fil_bloc_down_right

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
} // fin create_PNM

void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump){
  assert(Matrix != NULL && i>= 0 && j>= 0 && jump >=0);

  for(int k=i; k<jump+i; k++){
    for(int t= j; t<jump+j; t++){
      Matrix[k][t] = value;
    } // fin for t
  }// fin for t
} // fin fil_bloc_matrix
