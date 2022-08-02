/**************************************************************************************************
 *                                                                                                *
 *          LES TESTS UNITAIRES UTILISE LES IMAGES FOURNIT DANS LE PROJET 1                       * 
 *                                                                                                *
 * ************************************************************************************************/


/**
 * \file codebarre_test.c
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/07/2022
 * 
 * Ce fichier contient les tests unitaires du fichier codebarre.c
 *  et les prototypes des fonctions pour coder les matricules des étudiants de l'ULG.
 */

#include <string.h>
#include "codebarre.h"
#include "seatest.h"

static void test_check_is_ulg_code(){
  /*----------------------- test par exemples du matricule -------------------------*/
  assert_int_equal(1,check_is_ulg_code("202071711"));
  assert_int_equal(1,check_is_ulg_code("999999919"));
  assert_int_equal(-1,check_is_ulg_code("00000000"));
  assert_int_equal(-1,check_is_ulg_code("ULG FACSA"));
  assert_int_equal(-1,check_is_ulg_code("INFO0030"));
}

static int compare_two_Matrix(int **A, int **B, int dimension){
  assert(A != NULL && B != NULL);

  /*--------------------- Comparer les deux Matrices valeur par valeur -----------------------*/
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      if(A[i][j] != B[i][j])
        return -1;
    }//fin for
  }//fin for

  return 1;
}

static void free_matrix_code(int **Matrix){
  assert(Matrix != NULL);

  for (size_t i = 0; i < DIMESION; i++) {
    free(Matrix[i]);
  }//fin for
  free(Matrix);
}

static void test_get_file_name(){
  /*--------------------- Comparer les deux tableau valeur par valeur -----------------------*/
  assert_string_equal("","");
  assert_string_equal(get_file_name(""),get_file_name(""));
  assert_string_equal("codebarre.txt",get_file_name("/home/student/Bureau/barre/codebarre.txt"));
  assert_int_equal(-52, strcmp("code.txt",get_file_name("/home/student/Bureau/barre/codebarre.txt")));
}

static void test_fil_matrix_code(){
  /*------- Comparer deux tableau valeur par valeur  creer par fil_matrix_code--------*/
  assert_int_equal(1, compare_two_Matrix(fil_matrix_code(177), fil_matrix_code(177), 70));
  assert_int_equal(1, compare_two_Matrix(fil_matrix_code(1), fil_matrix_code(1), 70));
  assert_int_equal(-1, compare_two_Matrix(fil_matrix_code(132), fil_matrix_code(133), 70));
  assert_int_equal(-1, compare_two_Matrix(fil_matrix_code(1), fil_matrix_code(2), 70));
}

static void test_fil_last_matrix_bloc(){
  int **A = fil_matrix_code(637); //la fct fil_matrix_code fait appelle a fil last bloc
  int **B = fil_matrix_code(637); //la fct fil_matrix_code fait appelle a fil last bloc
  int **C = fil_matrix_code(515); //la fct fil_matrix_code fait appelle a fil last bloc

  /*------- Comparer les deux matrices avec le bit de parité remplis --------------*/
  assert_int_equal(1, (compare_two_Matrix(A, B, DIMESION)));
  assert_int_equal(-1, (compare_two_Matrix(A, C, DIMESION)));
  assert_int_equal(-1, (compare_two_Matrix(C, B, DIMESION)));

  free_matrix_code(A);
  free_matrix_code(B);
  free_matrix_code(C);
}

static void test_create_PNM(){
  /*----La création de 2 images; une par des setters et l'autre par create_PNM------*/
  int number = 320;

  //création de l'image1 par les setters
  PNM* image1=malloc(sizeof(PNM*));
  if(image1 == NULL)
    abort();
  
  char magiqueNumber[4] = P1;
  set_nLines(image1, DIMESION);
  set_nColumns(image1, DIMESION);
  set_maxPix(image1, 0);
  set_MagicNumber(image1, magiqueNumber);
  set_Matrix(image1, fil_matrix_code(number));

  //création de l'image1 par la fonction create_PNM
  PNM* image2 = NULL;
  image2 = create_PNM(number);

  /*------Effectuer des comparaisons entre les deux images crées -----*/
  assert_string_equal(get_MagicNumber(image1), get_MagicNumber(image2));
  assert_int_equal(get_nLines(image1), get_nLines(image2));
  assert_int_equal(get_nColumns(image1), get_nColumns(image2));
  assert_int_equal(get_maxPix(image1), get_maxPix(image2));
  assert_int_equal(1, compare_two_Matrix(get_matrix(image1), get_matrix(image2), DIMESION));

  free_matrix(image1);
  free_matrix(image2);
  free(image1);
  free(image2);
}

static void test_load_write_pnm(){
  PNM* image1= NULL;
  PNM* image2= NULL;
  PNM* image3= NULL;

  int i = load_pnm(&image1, "scs.pbm");
  int j = load_pnm(&image2,"totem.pgm");
  int k = load_pnm(&image3,"antilope.ppm");

  /*------------------le bon fonctionnement du load_pnm----------------------*/
  assert_int_equal(0,i);
  assert_int_equal(0,j);
  assert_int_equal(0,k);

  /*-------------------le bon fonctionnement du write_pnm-----------------------*/
  int l= write_pnm(image1,"scs-copie.pbm");
  int m= write_pnm(image2,"totem-copie.pgm");
  int n= write_pnm(image3,"antilope-copie,pgm");

  assert_int_equal(0,l);
  assert_int_equal(0,m);
  assert_int_equal(0,n);

  /*---teste write_pnm avec un nom fichier contient des caracteres spéciaux----*/
  int r= write_pnm(image1,"scs-cop<<ie.pbm");
  int s= write_pnm(image2,"totem-co>>pie.pgm");
  int t= write_pnm(image3,"an**tilope-copie.pgm");

  assert_int_equal(-1,r);
  assert_int_equal(-1,s);
  assert_int_equal(-1,t);

  free(image1);
  free(image2);
  free(image3);

}

static void test_generate_correcte_code_barre(){
  int a = generate_code_barre("MyUlgCode.txt",".");
  int b = fix_bar_code("20207171.pbm","20207171correct.pbm");

  assert_int_equal(1, a);
  assert_int_equal(0, b);

  PNM* code = NULL;
  PNM* correctedCode = NULL;

  load_pnm(&code,"20207171.pbm");
  load_pnm(&correctedCode, "20207171correct.pbm");

  assert_int_equal(get_nLines(code), get_nLines(correctedCode));
  assert_int_equal(get_nColumns(code), get_nColumns(correctedCode));
  assert_string_equal(get_MagicNumber(code), get_MagicNumber(correctedCode));
  assert_int_equal(1, compare_two_Matrix(get_matrix(code), get_matrix(correctedCode), get_nLines(code)));

  free(code);
  free(correctedCode);
}

static void test_fixture(){
  test_fixture_start();

  run_tests(test_check_is_ulg_code);
  run_tests(test_load_write_pnm);
  run_tests(test_get_file_name);
  run_tests(test_generate_correcte_code_barre);
  run_tests(test_fil_matrix_code);
  run_tests(test_fil_last_matrix_bloc);
  run_tests(test_create_PNM);

  test_fixture_end();
}

static void all_tests(){
  test_fixture();
}

int main(){
  return run_tests(all_tests);
}
