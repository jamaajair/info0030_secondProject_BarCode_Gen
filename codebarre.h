#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "pnm.h"


#ifndef __CODEBARRE__
#define __CODEBARRE__

#define DIMESION 70

int* to_binary(int );

int check_is_ulg_code(char *);

int check_file(char *);

char* get_file_name(char* );

int** fil_matrix_code(int);

void printMatrix(int **M, int m, int n); // a supprimer

void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump);

PNM* create_PNM(int nombre);

//remplir le box
void fil_parity_matrix(int **Matrix, int i, int j, int value);

//remplir tous les box de pariy
void fil_last_matrix_bloc(int **Matrix);
#endif //__CODEBARRE__
