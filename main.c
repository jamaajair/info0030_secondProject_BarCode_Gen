/**
 * \file main.c
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/07/2022
 *
 * Ce fichier est le main
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <getopt.h>
#include "codebarre.h"
#include "pnm.h"
#include "pnm.c"

int main(int argc, char *argv[]) {

   char *optstring = ":f:i:o:c:h";
   char file[MAX_SIZE];
   char folder[MAX_SIZE];
   char fileFixed[MAX_SIZE];
   int value, manqueOption = 0;
   int toCorrect = 0, toGenerate = 0;

   if(argc != 5){
     printf("commande non valide !!\n");
     return 0;
   }
    
  while((value  = getopt(argc, argv, optstring)) != EOF){
    switch (value){
      case 'f':
        strcpy(file, optarg);
        break;
      case 'o':
        strcpy(folder, optarg);
        toGenerate = 1;
        break;
      case 'c':
        strcpy(fileFixed, optarg);
        toCorrect = 1;
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
    if(toGenerate && !toCorrect){
      // le file contient un chemin soit abs ou rela vers le fichier des matricules
      if(generate_code_barre(file, folder))
        printf("\n\t*** la generation des codes barres a ete bien effectue..........................100%%\n\n");
      else
        printf("\n\t*** la generation des codes barres est echoue.................................0%%\n\n");
      toGenerate=0;
    }

    if(toCorrect){
      //Pour la correction il faut que le code a corrige se trouve dans le meme endroit que les fichier du code C
      strcpy(file,get_file_name(fileFixed));
      int test = fix_bar_code(file, folder);
      if(!test)
        printf("\n\t*** le fichier a ete bien corrige.................................................100%%\n\n");
      else
        printf("\n\t*** la correction du fichier est echoue.....................................................0%%\n\n");
      toCorrect=0;
    }
  return 0;
  }
}
