/**
 * pnm.c
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author   : Jair Jamaa s207171
 * @date    : 08/03/2022
 * @projet  : INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "pnm.h"

struct PNM_t {
 char magicNumber[3];   // Le nombre magique peut prendre P1 ou P2 ou P3
 int nLines;            // Le nombre de lignes de la matrice
 int nColumns;          // Le nombre de colonnes de la matrice
 int maxPix;           //  Le nombre maximal d'un pixel dans l'image
 int **Matrice;        //  La matrice represente l'image
};

char* get_MagicNumber(PNM* image){
  assert(image != NULL);

  return image->magicNumber;
}

int get_nLines(PNM* image){
  assert(image != NULL);

  return image->nLines;
}

int get_nColumns(PNM* image){
  assert(image != NULL);

  return image->nColumns;
}

int get_maxPix(PNM* image){
  assert(image != NULL);

  return image->maxPix;
}

void set_MagicNumber(PNM* image, char* magicNumber){
  assert((strcmp(magicNumber, P1) == 0) || (strcmp(magicNumber, P2) == 0)
        || (strcmp(magicNumber, P3) == 0));

  strcpy(image->magicNumber, magicNumber);
}

void set_nLines(PNM* image,int nLines){
  assert( nLines > 0);

  image->nLines = nLines;
}

void set_nColumns(PNM* image,int nColumns){
  assert( nColumns > 0);

  image->nColumns = nColumns;
}

void set_maxPix(PNM* image, int maxPix){
    assert( maxPix >= 0);

    image->maxPix = maxPix;
}

int** get_matrix(PNM* image){
  return image->Matrice;
}

void set_Matrix(PNM* image, int** Matrix){
  image->Matrice = Matrix;
}

void free_matrix(PNM* image){
  assert(image != NULL);
  for (int j = 0; j < image->nLines; j++) {
    free(image->Matrice[j]);
  }
  free(image->Matrice);
}

int check_extension(char *extension){
 assert (extension != NULL);
 if(strcmp(extension, "PGM") == 0 || strcmp(extension, "PBM") == 0 || strcmp(extension, "PPM") == 0)
  return -1;
 else
  return 1;
}

char* get_file_format(char *filename){
 assert(filename != NULL);

 unsigned int size = strlen(filename);
 char *extension = malloc(sizeof(char)*3);
 if(extension == NULL)
  return NULL;

 extension = &filename[size - 3];
 //l'objectif est de retourner les 3 dernier lettres
 return extension;
}

char *to_lower_string(char *string){
 assert(string != NULL);
 /*
  * l'objectif est de convertir le format convertir le format passer avec l'option -f en minuscule
  * à fin de comparer avec les extensions des fichiers input et output
  */
 for (unsigned int i = 0; i < strlen(string); i++)
  string[i] = tolower(string[i]);
 return string;
}

int check_input_output_format(char *input, char *output, char *format){
  assert(input != NULL && output != NULL && format != NULL);

  if(check_extension(format) == 1){ // vérification si le format est PBM ou PPM ou PGM
   int lengthInputName = strlen(input);
   int lengthOutputName = strlen(output);
   int i = lengthInputName -4;
   int j = lengthOutputName-4;

   while (i < lengthInputName && j< lengthOutputName && input[i] == output[j]) {
    i++;
    j++;
   }// fin while

   if( i == lengthInputName && j == lengthOutputName)
    return 1;
   else
    return -1;
  }
  else
   return -1;
}

void check_comments(FILE *filename){
 assert(filename != NULL);

 char string[MAX_SIZE];
 fgets(string, MAX_SIZE, filename);

 if(string[0] == '#'){
  while (string[0] == '#'){
      fgets(string, MAX_SIZE, filename);
  }// fin while
 }

 if(string[0] != '#')
  fseek(filename, -(strlen(string) * sizeof(char)), SEEK_CUR);
}

int check_magic_number(char *magicNumber){
 assert( magicNumber != NULL);

 if(strcmp(magicNumber,P1)==0 || strcmp(magicNumber, P2)==0 || strcmp(magicNumber, P3)==0)
  return 1;
 return -3;
}

int check_nb_columns(int nColumns, char *nMagic){
  assert(nMagic != NULL && nColumns > 0);

  if(strcmp(nMagic, P3) == 0)
    return nColumns *=3;
  return nColumns;
}

int allocate_memory_image(PNM **image){
 assert(image != NULL);

 if((*image = malloc(sizeof(PNM)))!= NULL)
   return 1;
 return -1;
}

int check_filename(char *filename){
 assert(filename != NULL);

 int size= strlen(filename);
 int i=0;
 char temp;
 while( i<size ){
   temp = filename[i];
   if(temp == ':' || temp == '/' || temp == '\\' || temp == '*' \
      || temp == '?' || temp == '"'|| temp == '>' || temp == '<' \
      || temp == '|' \
      )
      return -1;
    i++;
 }// fin while
return 1;
}

int **fil_matrix(PNM **image, FILE *f){
 assert(image!=NULL && f != NULL);

 int **Matrix;
 int nColumns = check_nb_columns(get_nColumns(*image), get_MagicNumber(*image));

  //allocation de la matrice
 if((Matrix = (int **)malloc(get_nLines(*image) * sizeof(int *))) != NULL){
  for(int i=0; i< get_nLines(*image); i++){
    if((Matrix[i] = (int*)malloc(nColumns * sizeof(int*))) == NULL)
     return NULL;
    }
  }// fin d'allocation de la matrice

  /*lire la matrice à partir du fichier avec un test si fscanf à réussi ou pas
  * à fin de vérifier que le nombre des lignes et colonnes est sont les memes que celles au debut du fichier
  */
 int j, k;
 for(j=0; j < get_nLines(*image); j++){
  for(k=0; k < nColumns; k++){
    if(fscanf(f, "%d ", &Matrix[j][k]) != 1){
      printf("le fichier contient MOINS le nombre des lignes/colonnes indiques au debut du fichier !\n");
      return NULL;
      }
    }
  }// fin remplissage de la matrice

  // verification qu nous avons bien lu (*image)->nLines et (*image)->nColumns exacte
 int chek_eof = fscanf(f, "%d ", &Matrix[j][k]);
 if(fscanf(f, "%d ", &chek_eof) != EOF){
    printf("le fichier contient PLUS le nombre des lignes/colonnes indiques au debut du fichier !\n");
    return NULL;
 }

  //Vérification si la matrice ne contient pas une valeur supérieur à (*image)->maxPix
  for(j=0; j < get_nLines(*image); j++){
    for(k=0; k < nColumns; k++){
      if(Matrix[j][k] > get_maxPix(*image) || Matrix[j][k] < 0){
        printf("la matrice contient des valeur superieur a la valeur maximal !!!\n");
        return NULL;
      }
    }
  }// fin vérification que les elemens de la matrice < maxPix

  return Matrix;
}

int load_pnm(PNM **image, char* filename){
assert(image != NULL && filename !=NULL);

if(allocate_memory_image(image) != 1)
  return -1;

FILE *f;
f = fopen(filename, "r");
if(f == NULL){
  return -2;
}else{
  char magicNumber[3];
  check_comments(f);
  if(fscanf(f, "%s ", (char *) &magicNumber) != 1)
    return -3;
  set_MagicNumber(*image, magicNumber);

  check_comments(f);
  if(check_magic_number(get_MagicNumber(*image)) != 1)
    return -3;

  int nLines, nColumns;
  check_comments(f);
  if(fscanf(f, "%d %d ", (int*) &nColumns,(int*) &nLines) != 2)
    return -3;
  set_nLines(*image, nLines);
  set_nColumns(*image, nColumns);

  int maxPix;
  if (strcmp(get_MagicNumber(*image), P2) == 0 || strcmp((get_MagicNumber(*image)), P3) == 0){
    check_comments(f);
    if(fscanf(f, "%d", (int *)&maxPix) != 1)
      return -3;
  }
  set_maxPix(*image, maxPix);

  if(((strcmp(get_MagicNumber(*image), P2) == 0) && get_maxPix(*image) > 255) ||
     ((strcmp(get_MagicNumber(*image), P3) == 0) && get_maxPix(*image) > 65536)){
      return -3;
  }

  if(((*image)->Matrice = fil_matrix(image, f)) == NULL){
    printf("\nle fichier est corrompus\n");
    return -3;
  }
  fclose(f);
  return 0;
  }
}

int write_pnm(PNM *image, char* filename) {

   assert(image != NULL && filename != NULL);

   if(check_filename(filename) != 1)
     return -1;

   FILE *f = fopen(filename, "w");
   if(f == NULL){
     return -2;
   }

   fprintf(f, "%s\n",get_MagicNumber(image));

   fprintf(f, "%u %u\n",get_nColumns(image), get_nLines(image));

   if(strcmp(get_MagicNumber(image), P2) == 0 || strcmp(get_MagicNumber(image), P3) == 0){
        fprintf(f, "%u\n",get_maxPix(image));
   }

   if(strcmp(get_MagicNumber(image), P3) == 0){
     set_nColumns(image, get_nColumns(image)* 3);
   }
   for(int i=0; i< get_nLines(image); i++){
     for(int j=0; j< get_nColumns(image); j++){
       fprintf(f, "%d ",image->Matrice[i][j]);
     }
     fprintf(f, "\n");
   }
   fclose(f);
   return 0;
}

void display_help(void){
   printf("\n\t-------------------------------------------------------------------------------\n\n");
   printf("\t                         * HELP * \n" );
   printf("\tCe programme permet de traiter et enregistrer des fichiers PNM en memoire\n");
   printf("\tVeuillez utiliser les options suivantes: \n");
   printf("\t -f : pour indiquer le format du fichier de base (PBM ou PPM ou PGM)\n");
   printf("\t -i : pour indiquer le fichier input \n");
   printf("\t -o : pour indiquer le fichier output \n\n");
   printf("\t---------------------------------------------------------------------------------\n");
 }

void display_succes(void){
  printf("\n\t--------------------------------------------------------------------------\n\n");
  printf("\t                         * SUCCES * \n" );
  printf("\tles fichiers input et output ont le meme extension....................SUCCES \n");
  printf("\tle fichier input est bien lu..........................................SUCCES \n");
  printf("\tle traitement est terminer............................................SUCCES \n\n");
  printf("\t------------------VOTRE FICHIER EST DISPONIBLE-------------------------------\n");
}

void free_image(PNM* image){
  assert(image != NULL);
  free_matrix(image);
  free(image);
}
