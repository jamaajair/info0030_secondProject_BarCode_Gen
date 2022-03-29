/**
 * \file codebarre.h
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/03/2022
 *
 * Ce fichier contient les déclarations de types
 *  et les prototypes des fonctions pour coder les matricules des étudiants de l'ULG.
 */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "pnm.h"

/*
 * Include guard
 *
 */
#ifndef __CODEBARRE__
#define __CODEBARRE__

/*
 * Déclaration des macros
 *
 */
#define DIMESION 70

//------------------------------------------------------------------------------
/**
 * \fn int* to_binary(int number)
 * \brief changer la base de number de decimale à binaire, seulment si le "number"
 *        à besoin de moins de 36 bits pour l'encodage sinon impossible de faire
 *        le changement de base car la matrice qui represente le matricule est de 6*6
 *
 * \param number, nombre à convertir en binaire. (>0)
 *
 * \return un tableau des 0 et 1 contient la représentation du "number" en binaire
 *
 */
//------------------------------------------------------------------------------
int* to_binary(int number);

//------------------------------------------------------------------------------
/**
 * \fn int check_is_ulg_code(char *code)
 * \brief verification si la chaine de caractere est un code ulg ou pas.
 *
 * \param code, une chaine de caractere à tester s'elle s'agit d'un code ulg. (>0)
 *
 * \return
 *        1 en cas de "code" est bien un matricule de la ULG
 *       -1 en cas de "code" n'est pas un matricule de la ULG
 *
 */
 //------------------------------------------------------------------------------
int check_is_ulg_code(char *code);

//------------------------------------------------------------------------------
/**
 * \fn void change_to_base2(int number, int* binary, int nbits)
 * \brief caclculer la representation de number en base 2 et la stocker dans binary
 *
 * \param number, le nombre à représenter en base 2. (>0)
 * \param binary, le tableau qui va contient la représentation de number en binaire
 * \param nbits, le nombre de bits pour représenter number en base 2
 *
 *
 */
 //------------------------------------------------------------------------------
void change_to_base2(int number, int* binary, int nbits);
//------------------------------------------------------------------------------
/**
 * \fn char* get_file_name(char* filename)
 * \brief extraire le nom de fichier ou cas ou l'utilisateur fourni un chemin absolu
 *        ou relatif, on vas faire un test sur le nom de fichier pour tester s'il contient
 *        des caracteres spéciaux.
 *
 * \param path, le chemin saisi par l'utilisateur pour indique l'endroit ou il se trouve
 *        le fichier qui contient le matricules des etudiants de la ULG
 *
 *\return le nom du fichier
 *
 */
 //------------------------------------------------------------------------------
char* get_file_name(char* path);
//------------------------------------------------------------------------------
/**
 * \fn int** fil_matrix_code(int number);
 * \brief l'encodage de la matrice en basent sur la representation en base 2 du
 *        number.
 *
 * \param number, le nombre a représenter en binaire (>0), a fin de remplir la matrice
 *
 *\return la matrice qui représente le code barre du number
 *
 */
//------------------------------------------------------------------------------
int** fil_matrix_code(int number);
//------------------------------------------------------------------------------
/**
 * \fn void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump);
 * \brief  la matrice qui represente le matricule est de base une matrice de 7*7
 *         mais vu que on dois représenter chaque bit 10*10 à fin d'obtenir
 *         une matrice de 70*70.
 *
 * \param Matrix, la matrice qui représente le code barre d'un matre ulg
 *        i, l'indice ligne
 *        j, l'indice colonne
 *        value, la value a mettre dans dans le bloc de la matrice commence dans (i,j)
 *        jump, la valeur represente la taille du bloc
 *
 *
 */
 //------------------------------------------------------------------------------
void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump);
//------------------------------------------------------------------------------
/**
 * \fn PNM* create_PNM(int nombre)
 * \brief  la création d'une image de type PBM avec PBM comme nombre magique
 *         et 70*70 dans nombre ligne et colonne, et la matrice à génere en
 *         basent sur la représentation binaire de number
 *
 * \param number, le nombre a représenter en binaire (>0), a fin de remplir la matrice
 *
 *\return l'image PNM qui montre le code barre en image concrete
 */
 //------------------------------------------------------------------------------
 PNM* create_PNM(int number);
 //------------------------------------------------------------------------------
 /**
  * \fn  void fil_last_matrix_bloc(int **Matrix)
  * \brief  le remplissage du bit de parité, dépend du nombre de bit dans chaque
  *         ligne (resp colonne), le bit de par est dans la dérnière ligne (rep colonne)
  *
  *
  * \param Matrix, la matrice qui représente le code barre d'un matre ulg
  *
  */
  //------------------------------------------------------------------------------
 void fil_last_matrix_bloc(int **Matrix);
#endif
