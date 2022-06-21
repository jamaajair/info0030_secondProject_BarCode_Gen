/**
 * \file main-codebarre.c
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/03/2022
 *
 * Ce fichier contient le main
 *  et les prototypes des fonctions pour coder les matricules des étudiants de l'ULG.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include "codebarre.h"
#include "pnm.h"
#include "pnm.c"

int main(int argc, char *argv[]) {

   char *optstring = ":f:i:o:h";
   char* file = (char*)malloc(sizeof(char*)*MAX_SIZE);
   char* folder = (char*)malloc(sizeof(char*)*MAX_SIZE);
   int value, manqueOption=0;

   if(argc != 5){
     printf("commande non valide !!\n");
     return 0;
   }
   else{
     while((value  = getopt(argc, argv, optstring)) != EOF){
       switch (value) {
         case 'f':
           strcpy(file, optarg);
           break;
         case 'o':
           strcpy(folder, optarg);
           break;
         case '?':
           printf("option inconnu !!");
           manqueOption = 1;
           break;
         case ':':
           printf("option manque !!");
           manqueOption = 1;
           break;
       }
     }

     if(manqueOption != 1){
       //mkdir(folder, 0777);

       strcpy(file,get_file_name(file));

       if(generate_code_barre(file, folder) == 1)
        printf("succes 100%\n");
      else
        printf("something was wrong\n");
   }



  /*if(file == NULL || folder == NULL || codeString == NULL){
    return 0;
  }*/

  return 0;
}
}
