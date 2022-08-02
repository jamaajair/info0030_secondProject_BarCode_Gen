/**
 * \file codebarre.h
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/07/2022
 *
 * Ce fichier contient les declarations de types
 *  et les prototypes des fonctions pour coder les matricules des etudiants de l'ULG.
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
 * Declaration des macros
 *
 */
#define DIMESION 70 //!<Macro DIMENSION pour les demensions de la matrice
#define SIZE 10000

//------------------------------------------------------------------------------
/**
 * \fn void fil_bloc_down_right(int **Matrix)
 * \brief permet de remplir le blox 10*10 en bas de la matrice selon la parite de
 *        la derniere ligne et la derniere colonne
 * \param Matrix: une matrice 2D
 *
 * \return -
 */
//------------------------------------------------------------------------------
void fil_bloc_down_right(int **Matrix);
//------------------------------------------------------------------------------
/**
 * \fn int fix_bar_code(char* barcode_to_fixe,char* barcode_fixed)
 * \brief permet de corriger un code barre 
 * \param barcode_to_fixe: une chaine de caractere contient le nom du fichier a corriger
 * \param  barcode_fixed: une chaine de caractere contient le nom du fichier apres la correction
 *
 * \return un entier indique la reussite ou pas de la fonction de correction
 */
//------------------------------------------------------------------------------
int fix_bar_code(char* barcode_to_fixe,char* barcode_fixed);
//------------------------------------------------------------------------------
/**
 * \fn int check_column_parity(int **matrix, int column_index, int matrix_dimension)
 * \brief permet de verifier si une colonne d une matrice contient un bloc des 1 pair ou pas 
 * \param matrix: une matrice dont la verification sera effectuer
 * \param  column_index: un entier indique sur quel colonne dans la matrice on va aller voir sa parite
 * \param matrix_dimension: un entier indique les dimensions de la matrice
 * 
 * \return un entier qui permet a savoir si nombre des bloc des 1 dans la colonne est pair ou pas 
 */
//------------------------------------------------------------------------------
int check_column_parity(int **matrix, int column_index, int matrix_dimension);
//------------------------------------------------------------------------------
/**
 * \fn int check_line_parity(int **matrix, int line_index, int matrix_dimension)
 * \brief permet de verifier si une ligne d une matrice contient un bloc des 1 pair ou pas 
 * \param matrix: une matrice dont la verification sera effectuer
 * \param  line_index: un entier indique sur quel ligne dans la matrice on va aller voir sa parite
 * \param matrix_dimension: un entier indique les dimensions de la matrice
 * 
 * \return un entier qui permet a savoir si nombre des bloc des 1 dans la ligne est pair ou pas 
 */
//------------------------------------------------------------------------------
int check_line_parity(int **matrix, int line_index, int matrix_dimension);
//------------------------------------------------------------------------------
/**
 * \fn char *generate_file_name(char *code)
 * \brief permet de generer le nom du fichier dont on va stocker le code barre
 * \param code: une chaine de caractere, on va l'ajouter l'extension PBM
 * 
 * \return le nom du fichier avec l extension PBM
 */
//------------------------------------------------------------------------------
char *generate_file_name(char *code);
//------------------------------------------------------------------------------
/**
 * \fn int generate_code_barre(char *input_file, char* output_folder)
 * \brief permet de generer les codes barres de chaque matricule lu a partir du fichier
 * \param input_file: une chaine de caractere contient le chemin abs ou rela vers les matricules
 * \param output_folder: le dossier ou on va stocker les codes barres
 * 
 * \return un entier pour teste la reussite de la fonction ou pas 
 */
//------------------------------------------------------------------------------
int generate_code_barre(char *input_file, char* output_folder);

//------------------------------------------------------------------------------
/**
 * \fn int* to_binary(int number)
 * \brief changer la base de number de decimale a binaire, seulment si le "number"
 *        a besoin de moins de 36 bits pour l'encodage sinon impossible de faire
 *        le changement de base car la matrice qui represente le matricule est de 6*6
 *
 * \param number: nombre a convertir en binaire. (>0)
 *
 * \return un tableau des 0 et 1 contient la representation du "number" en binaire
 *
 */
//------------------------------------------------------------------------------
int* to_binary(int number);

//------------------------------------------------------------------------------
/**
 * \fn int check_is_ulg_code(char *code)
 * \brief verification si la chaine de caractere est un code ulg ou pas.
 *
 * \param regestrationNumber: une chaine de caractere a tester s'elle s'agit d'un code ulg. (>0)
 *
 * \return
 *        1 en cas de "code" est bien un matricule de la ULG
 *       -1 en cas de "code" n'est pas un matricule de la ULG
 *
 */
 //------------------------------------------------------------------------------
int check_is_ulg_code(char *regestrationNumber);

//------------------------------------------------------------------------------
/**
 * \fn void change_to_base2(int number, int* binary, int nbits)
 * \brief caclculer la representation de number en base 2 et la stocker dans binary
 *
 * \param number: le nombre a representer en base 2. (>0)
 * \param binary: le tableau qui va contient la representation de number en binaire
 * \param nbits: le nombre de bits pour representer number en base 2 
 *
 */
 //------------------------------------------------------------------------------
void change_to_base2(int number, int* binary, int nbits);
//------------------------------------------------------------------------------
/**
 * \fn char* get_file_name(char* filename)
 * \brief extraire le nom de fichier ou cas ou l'utilisateur fourni un chemin absolu
 *        ou relatif, on vas faire un test sur le nom de fichier pour tester s'il contient
 *        des caracteres speciaux.
 *
 * \param path: le chemin saisi par l'utilisateur pour indique l'endroit ou il se trouve
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
 * \param number: le nombre a representer en binaire (>0), a fin de remplir la matrice
 *
 *\return la matrice qui represente le code barre du number
 *
 */
//------------------------------------------------------------------------------
int** fil_matrix_code(int number);
//------------------------------------------------------------------------------
/**
 * \fn void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump);
 * \brief  la matrice qui represente le matricule est de base une matrice de 7*7
 *         mais vu que on dois representer chaque bit 10*10 a fin d'obtenir
 *         une matrice de 70*70.
 *
 * \param Matrix: la matrice qui represente le code barre d'un matre ulg
 * \param i: l'indice ligne
 * \param j: l'indice colonne
 * \param value: la value a mettre dans dans le bloc de la matrice commence dans (i,j)
 * \param jump: la valeur represente la taille du bloc
 *
 */
 //------------------------------------------------------------------------------
void fil_bloc_matrix(int **Matrix, int i, int j, int value, int jump);
//------------------------------------------------------------------------------
/**
 * \fn PNM* create_PNM(int nombre)
 * \brief  la creation d'une image de type PBM avec PBM comme nombre magique
 *         et 70*70 dans nombre ligne et colonne, et la matrice a genere en
 *         basent sur la representation binaire de number
 *
 * \param number: le nombre a representer en binaire (>0), a fin de remplir la matrice
 *
 *\return l'image PNM qui montre le code barre en image concrete
 */
 //------------------------------------------------------------------------------
 PNM* create_PNM(int number);
 //------------------------------------------------------------------------------
 /**
  * \fn  void fil_last_matrix_bloc(int **Matrix)
  * \brief  le remplissage du bit de parite, depend du nombre de bit dans chaque
  *         ligne (resp colonne), le bit de par est dans la dernière ligne (rep colonne)
  *
  *
  * \param Matrix: la matrice qui represente le code barre d'un matre ulg
  *
  */
  //------------------------------------------------------------------------------
 void fil_last_matrix_bloc(int **Matrix);
#endif
