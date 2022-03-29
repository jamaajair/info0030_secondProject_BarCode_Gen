/**
 * main.c
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
#include <unistd.h>
#include <getopt.h>
#include "pnm.h"


int main(int argc, char *argv[]){

   char *optstring = ":f:i:o:h";
   PNM *image;
   char input[MAX_SIZE];
   char output[MAX_SIZE];
   char format_demande[MAX_SIZE];
   int value;
   int manqueOption=0;

   if(argc != 7){
     display_help();
     return 0;
   }
   else{
     while((value  = getopt(argc, argv, optstring)) != EOF){
       switch (value) {
         case 'f':
           strcpy(format_demande, optarg);
           break;
         case 'i':
           strcpy(input, optarg);
           break;
         case 'o':
           strcpy(output, optarg);
           break;
         case '?':
           manqueOption =1;
           printf("\toption inconu => %c  !!! \n", optopt);
           break;
         case ':':
           manqueOption =1;
           printf("\targument manquant !!! \n");
           break;
       }
     }// fin while

     if(manqueOption != 1){
       char *extension = malloc(sizeof(char  )* MAX_SIZE);
       char *format = malloc(sizeof(char  )* MAX_SIZE);
       if(format == NULL || extension == NULL ){
         printf("il n'y a pas assez de memoire pour continuer !!! \n");
         return 0;
       }

       format = to_lower_string(format_demande);
       extension = get_file_format(output);
       if(check_input_output_format(input, output, format_demande) == 1){
          if(strcmp(extension, format) == 0 && load_pnm(&image, input) == 0 && write_pnm(image, output) == 0){
            display_succes();
            //int** matrice = get_matrix(image);
            free_matrix(image);
            free(image);
            free(extension);
            free(format);
          }
          else
            printf("Erreur! verifier l'extension des fichiers input et output!!!\n");
          }
       else
          printf("Erreur! verifier l'extension des fichiers input et output!!!\n");
       }
       else{
        display_help();
       return 0;
       }
   }
}
