/**
 * pnm.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author: Jair Jamaa
 * @date: 08/03/2022
 * @projet: INFO0030 Projet 1
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <string.h>
 #include <ctype.h>
 #include <regex.h>

 /*
   * Include guard (pour éviter les problèmes d'inclusions multiplies
   *
   */
#ifndef __PNM__
#define __PNM__

/**
 *Declaration des MACRO
 */
 #define MAX_SIZE 1024
 #define P1 "P1"
 #define P2 "P2"
 #define P3 "P3"

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**-----------------------------------------------------------------------------
 * \fn char* get_MagicNumber(PNM* )
 * \brief retourne la chaine de caractere stocké dans la variable magicNumber
 * \param image: une image PNM
 *
 * \return magicNumber
 -----------------------------------------------------------------------------*/
 char* get_MagicNumber(PNM* image);
 /**----------------------------------------------------------------------------
  * \fn get_nLines(PNM* )
  * \brief retourne le nombre de ligne de l'image passe en argument
  * \param image: une image PNM
  *
  * \return nLines
 -----------------------------------------------------------------------------*/
 int get_nLines(PNM* image);
 /**----------------------------------------------------------------------------
  * \fn get_nColumns(PNM* )
  * \brief retourne le nombre de colonne de l'image passe en argument
  * \param image: une image PNM
  *
  * \return nColumns
 -----------------------------------------------------------------------------*/
 int get_nColumns(PNM* image);
 /**----------------------------------------------------------------------------
  * \fn get_maxPix(PNM* )
  * \brief retourne le nombre maximal de pixel de l'image passe en argument
  * \param image: une image PNM
  *
  * \return nombre maximal des pixel
 -----------------------------------------------------------------------------*/
 int get_maxPix(PNM* image);
 /**----------------------------------------------------------------------------
  * \fn set_MagicNumber(PNM* , char* )
  * \brief sert à stocker la chaine de caractere passé en arg dans la variable
  *        magicNumber de l'image PNM passé en agr
  * \param image: une image PNM
  *        magicNumber: une chaine de caractere represente le magic number
  *
  ---------------------------------------------------------------------------*/
 void set_MagicNumber(PNM* image, char* magicNumber);
 /**----------------------------------------------------------------------------
  * \fn set_nLines(PNM *image,int nLines)
  * \brief sert à stocker l'entier passé en arg dans la variable
  *        nLines de l'image PNM passé en agr
  * \param image: une image PNM et un entier represente le nombre de lignes
  *
  -----------------------------------------------------------------------------*/
 void set_nLines(PNM *image,int nLines);
 /**----------------------------------------------------------------------------
  * \fn set_nColumns(PNM *image,int nColumns)
  * \brief sert à stocker l'entier passé en arg dans la variable
  *        nColumns de l'image PNM passé en agr
  * \param image: une image PNM
  *        nColumns: un entier represente le nombre de colonnes
  ----------------------------------------------------------------------------*/
 void set_nColumns(PNM *image,int nColumns);
 /**----------------------------------------------------------------------------
  * \fn set_Matrix(PNM *image,int nColumns)
  * \brief sert à stocker l'entier passé en arg dans la variable
  *        nColumns de l'image PNM passé en agr
  * \param une image PNM et un entier represente le nombre de colonnes
  *
  -----------------------------------------------------------------------------*/
 void set_Matrix(PNM* image, int** Matrix);
 /**----------------------------------------------------------------------------
  * \fn set_maxPix(PNM* image, int maxPix)
  * \brief sert à stocker l'entier passé en arg dans la variable
  *        maxPix de l'image PNM passé en agr
  * \param une image PNM et un entier represente le nombre maximal des pixel
  *
  -----------------------------------------------------------------------------*/
 void set_maxPix(PNM* image, int maxPix);
/**-----------------------------------------------------------------------------
 * \fn int check_extension(char *s)
 * \brief sert à verifier si le format demandé est bien : soit PPM ou PBM ou PGM
 * \param une chaine de caractère
 *
 * \return 1 si la chaine de caractere passé en agrument est soit PPM ou PBM
 *         ou PGM et -1 dans le contraire
 *
 -----------------------------------------------------------------------------*/
 int check_extension(char *);
 /**----------------------------------------------------------------------------
  * \fn   char* get_file_format(char *filename)
  * \brief permet d'obtenir le format du fichier du fichier ou son nom
  *        (le nom du fichier) est passé en argument
  * \param une chaine de caractère pour décrire le nom du fichier
  *
  * \return return le format du fichier
  ----------------------------------------------------------------------------*/
 char* get_file_format(char *filename);
 /**----------------------------------------------------------------------------
  * \fn    char *to_lower_string(char *string)
  * \brief permet de transformer une chaine de caractere contient des majuscules
  *        à une chaine de caractère contient juste des miniscules
  *\param une chaine de caractère
  * \return return un chaine sous format miniscules
  ----------------------------------------------------------------------------*/
 char *to_lower_string(char *string);
 /**----------------------------------------------------------------------------
  * \fn    int check_input_output_extension(char *input,
  *                                          char *output, char *format_demande)
  * \brief permet de savoir est ce que le fichier input et output ont la meme
  *          format ou pas
  *\param input une chaine de caractère input
  *\param out: put une chaine de caractère output
  *\param input une chaine de caractère format demande
  *\return return 1 si les deux noms des fichiers ont la meme format
  *         (exemple : PPM et PPM) et -1 sinon (exemple : PPM et PGM)
  ----------------------------------------------------------------------------*/
 int check_input_output_format(char *input, char *output, char *format_demande);
 /**----------------------------------------------------------------------------
  * \fn     void check_comments(FILE *fp)
  * \brief permet d'éviter de lire les lignes ou il y des commentaires dans le
  *        fichier source
  *\param teois chaine de caractère
   ---------------------------------------------------------------------------*/
 void check_comments(FILE *fp);
 /**----------------------------------------------------------------------------
  * \fn    int check_magic_number(char *val)
  * \brief permet de savoir est ce que la chaine de caractere passé en argument
  *        est bien un nombre magique ou pas
  *\param un FILE
  * \return return 1 si les deux noms des fichiers ont la meme format (exemple :
  *         PPM et PPM) et -1 sinon (exemple : PPM et PGM)
  ----------------------------------------------------------------------------*/
 int check_magic_number(char *val);
 /**----------------------------------------------------------------------------
  * \fn    int check_nb_columns(int nb_colonne, char *nb_magique)
  * \brief permet de modier le nombre de nb_colonnes si le nombre magique est P3
  *\param une chaine de caractère
  * \return return nb_colonne modifie (ou pas)
  *
  ----------------------------------------------------------------------------*/
 int check_nb_columns(int nb_colonne, char *nb_magique);
  /**---------------------------------------------------------------------------
   * \fn    int allocate_memory_image(PNM **image)
   * \brief permet d'allouer un espace memoire pour une structure PNM
   *\param une chaine de caractère et un entier
   * \return return 1 si malloc réussi et -1 sinon
   --------------------------------------------------------------------------*/
 int allocate_memory_image(PNM **image);
 /**----------------------------------------------------------------------------
  * \fn    int **fil_matrix(PNM **image, FILE *f)
  * \brief permet remplis la Matrice à partier dans un fichier donné
  *\param une PNM
  * \return return une Matrice remplis
  *
  ----------------------------------------------------------------------------*/
 int **fil_matrix(PNM **image, FILE *f);
 /**----------------------------------------------------------------------------
  * \fn    int check_filename(char* filename);
  * \brief permet de verifier le nom du fichier source s'il contient [:  /  \  *
  *       ?  "  >  < |]
  *\param un PNM et un FILE
  * \return return -1 si le nom du fichier confier un caractère spéciaux et 1
  *         dans le cas inverse
  ----------------------------------------------------------------------------*/
 int check_filename(char* filename);
 /**----------------------------------------------------------------------------
  * load_pnm
  *
  * Charge une image PNM depuis un fichier.
  *
  * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
  *              de l'image chargée.
  * @param filename le chemin vers le fichier contenant l'image.
  *
  * @pre: image != NULL, filename != NULL
  * @post: image pointe vers l'image chargée depuis le fichier.
  *
  * @return:
  *     0 Succès
  *    -1 Erreur à l'allocation de mémoire
  *    -2 Nom du fichier malformé
  *    -3 Contenu du fichier malformé
  *
  ----------------------------------------------------------------------------*/
 int load_pnm(PNM **image, char* filename);
/**-----------------------------------------------------------------------------
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 -----------------------------------------------------------------------------*/
int write_pnm(PNM *image, char* filename);
/**----------------------------------------------------------------------------
 * \fn  display_help();
 * \brief permet d'afficher un message d'aide à l'utilisateur
 *\param le procedure prends void pour indiquer que "pas d'args"
 * \return -
  ----------------------------------------------------------------------------*/
void display_help(void);
/**----------------------------------------------------------------------------
 * \fn  display_help();
 * \brief permet d'afficher un message de fin d'aide
 *\param le procedure prends void pour indiquer que "pas d'args"
 ----------------------------------------------------------------------------*/
void display_succes(void);
/**----------------------------------------------------------------------------
 * \fn  display_succes(void);
 * \brief permet d'afficher un message de fin de traitement avec succes l'utilisateur
 *\param le procedure prends void pour indiquer que "pas d'args"
 ----------------------------------------------------------------------------*/
 void free_matrix(PNM* image);
 /**----------------------------------------------------------------------------
  * \fn free_matrix(PNM* image);
  * \brief permet de libérer l'éspace ocuupé par la matrice de l'image PNM image
  *\param image: le procedure prends void pour indiquer que "pas d'args"
  ----------------------------------------------------------------------------*/
int** get_matrix(PNM* image);
/**----------------------------------------------------------------------------
 * \fn get_matrix(PNM* image);
 * \brief permet de de retourner la matrice de l'image PNM image
 *\param image: le procedure prends void pour indiquer que "pas d'args"
 * \return la matrice de l'image PNM
 ----------------------------------------------------------------------------*/
void free_image(PNM* image);
/**----------------------------------------------------------------------------
 * \fn free_image(PNM* image);
 * \brief permet de libérer l'éspace ocuupé par l'image PNM image
 *\param image: le procedure prends void pour indiquer que "pas d'args"
 */

#endif // __PNM__
