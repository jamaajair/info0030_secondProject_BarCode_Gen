

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
   char file_fixed[MAX_SIZE];
   int value, manqueOption = 0;
   int to_correct = 0, to_generate = 0;

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
        to_generate = 1;
        break;
      case 'c':
        strcpy(file_fixed, optarg);
        to_correct = 1;
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
    if(to_generate){
      strcpy(file,get_file_name(file));
      if(generate_code_barre(file, folder) == 1)
        printf("\n\t***la generation des codes barres a ete bien effectué..........................100%%\n\n");
      else
        printf("\n\t***la generation des codes barres est echoué.................................0%%\n\n");
      to_generate=0;
    }

    if(to_correct){
      strcpy(file,get_file_name(file_fixed));
      int test = fix_bar_code(file, folder);
      if(test == 0)
        printf("\n\t***le fichier à été bien corrigé.................................................100%%\n\n");
      else
        printf("\n\t***la correction du fichier est échoué.....................................................0%%\n\n");
      to_correct=0;
    }
  return 0;
  }
}
