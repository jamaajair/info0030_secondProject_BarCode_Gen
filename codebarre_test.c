#include <string.h>
#include "codebarre.h"
#include "seatest.h"

static void test_check_is_ulg_code(){
  /*----------------------- test par exemples du matricule -------------------------*/
  assert_int_equal(1,check_is_ulg_code("20207171"));
  assert_int_equal(1,check_is_ulg_code("99999999"));
  assert_int_equal(1,check_is_ulg_code("00000000"));
  assert_int_equal(-1,check_is_ulg_code("blablabl"));
  assert_int_equal(-1,check_is_ulg_code("INFO0030"));
}

static int compare_two_table(int *A, int *B, int size){
  assert(A != NULL && B != NULL && n>0);

  /*--------------------- Comparer les deux tableau valeur par valeur -----------------------*/
  int i = 0;
  while (i != (size-1) && A[i]==B[i]) {
    i++;
  }//fin while

  if(i == size-1)
    return 1;
  return -1;
}

static int compare_two_string(char *A, char *B){
  assert(A != NULL && B != NULL);

  /*--------------------- Comparer les deux String valeur par valeur -----------------------*/
  int i=0, j=0;
  while (i != strlen(A)-1 && j!= strlen(B)-1 && A[i]==B[i]) {
    i++;
    j++;
  }// fin while

  if(i == strlen(A)-1 && j == strlen(B)-1)
    return 1;
  return -1;
}

static int compare_two_Matrix(int **A, int **B, int dimension){
  assert(A != NULL && B != NULL);

  /*--------------------- Comparer les deux Matrices valeur par valeur -----------------------*/
  for (size_t i = 0; i < dimension; i++) {
    for (size_t j = 0; j < dimension; j++) {
      if(A[i][j] != B[i][j])
        return -1;
    }//fin for
  }//fin for

  return 1;
}

void free_matrix_code(int **Matrix){
  assert(Matrix != NULL);

  for (size_t i = 0; i < DIMESION; i++) {
    free(Matrix[i]);
  }//fin for
  free(Matrix);
}

static void test_to_binary(){
  /*--------------------- Comparer les représentation de la meme nombre--------------------*/
  assert_int_equal(1, compare_two_table(to_binary(155),to_binary(155),8));
  assert_int_equal(1, compare_two_table(to_binary(1),to_binary(1),1));
  assert_int_equal(1, compare_two_table(to_binary(9500735), to_binary(9500735), 24));
  assert_int_equal(-1, compare_two_table(to_binary(29), to_binary(27), 5));
  assert_n_array_equal(to_binary(155),to_binary(155),8);
  assert_n_array_equal(to_binary(7877),to_binary(7877),13);
}

static void test_get_file_name(){
  /*--------------------- Comparer les deux tableau valeur par valeur -----------------------*/
  assert_string_equal("","");
  assert_string_equal(get_file_name(""),get_file_name(""));
  assert_string_equal("codebarre.txt",get_file_name("/home/student/Bureau/barre/codebarre.txt"));
  assert_int_equal(-1, compare_two_string("toto.txt", "titi.txt"));
  assert_int_equal(1, compare_two_string(get_file_name("/home/student/Bureau/barre/codebarre.txt"), "code.txt"));
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

static void test_fixture(){
  test_fixture_start();
  run_tests(test_check_is_ulg_code);
  run_tests(test_to_binary);
  run_tests(test_get_file_name);
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
