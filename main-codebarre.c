

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

int main(int argc, char *argv[]) {

   char *optstring = ":f:i:o:h";
   char* file = (char*)malloc(sizeof(char*)*MAX_SIZE);
   char* folder = (char*)malloc(sizeof(char*)*MAX_SIZE);
   char codeString[MAX_SIZE];
   char* codeName;
   int codeNumber;
   int value, manqueOption=0;

   if(argc != 5){
     printf("commande non valide !!\n");
     return 0;
   }else{
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
       mkdir(folder, 0777);

       strcpy(file,get_file_name(file));
       FILE *f = fopen(file, "r");
       if(f == NULL)
         return 0;

       if(chdir(folder) == 0 ){
         while(!feof(f)){
           if(fscanf(f, "%s", codeString) == 1){
             if (check_is_ulg_code(codeString) != 1){
               printf("le fichier est mal formé !!\n");
               return 0;
             }
             if(strcmp(codeString,"") == 0)
                abort();
             codeNumber = atoi(codeString); // casting vers l'entier
             PNM* image = malloc(sizeof(PNM*));
             image = create_PNM(codeNumber);
             codeName = malloc(sizeof(char)*MAX_SIZE); // check malloc succes
             strcpy(codeName,strcat(codeString,".pbm"));
             if(write_pnm(image, codeName) == 0)
                printf("succes\n");
             free_matrix(image);
             free(image);
             free(codeName);
           }
         }
       }
       else{
         return 0;
       }
     }
   }



  /*if(file == NULL || folder == NULL || codeString == NULL){
    return 0;
  }*/

  return 0;
}
