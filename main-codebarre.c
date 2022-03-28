

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include "codebarre.c"
#include "pnm.h"

int main(int argc, char const *argv[]) {

   char *optstring = ":f:i:o:h";
   char* file=malloc(sizeof(char)*MAX_SIZE);
   char folder[MAX_SIZE];
   char codeString[MAX_SIZE];
   int codeNumber;
   int value, manqueOption=0;

   if(argc != 5)
      return 0;

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
    if(check_file(file) == -1)
      return 0;

    FILE *f = fopen(file, "r");
    if(f == NULL)
      return 0;

      while(!feof(file)){
        if(fscanf(file, "%s", codeString) == 1)
          printf("%s\n",codeString );
      }
    /*while(!feof(file)){
      if(fscanf(file, "%s", codeString) != 1)
        return 0;

      codeNumber = atoi(codeString);

      PNM* image = malloc(sizeof(PNM*));
      image = create_PNM(codeNumber);
      write_pnm(image, strcat(codeString,".pbm"));
      free_matrix(image);
      free(image);

    }*/
  }

  /*FILE *f = fopen("codebarre.txt", "r");

  if(f == NULL){
      return 0;
  }
  if(check_file("codebarre.txt") == -1){
      return 0;
  }

  while(!feof(f)){
    char* s = malloc(sizeof(char)*MAX_SIZE);
    fscanf(f,"%s \n", s);

    int code = atoi(s);

  }
  /*int nbits = (int)(log(83)/log(2)) + 1;
  PNM* image = create_PNM(87651234);
  write_pnm(image, "jair.pbm");*/
  //fclose(f);
  return 0;
}
