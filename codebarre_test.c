#include <string.h>
#include "codebarre.h"
#include "seatest.h"
#include "codebarre.h"

static void test_check_is_ulg_code(){
  assert_int_equal(1,check_is_ulg_code("20207171"));
  assert_int_equal(1,check_is_ulg_code("99999999"));
  assert_int_equal(1,check_is_ulg_code("00000000"));
  assert_int_equal(-1,check_is_ulg_code("blablabl"));
  assert_int_equal(-1,check_is_ulg_code("INFO0030"));
}

static int compare_two_table(int *A, int *B, int n){
  assert(A != NULL && B != NULL && n>0);

  int i=0;
  while (i != (n-1) && A[i]==B[i]) {
    i++;
  }
  if(i == n-1)
    return 1;
  return -1;
}

static int compare_two_string(char *A, char *B){
  assert(A != NULL && B != NULL);

  int i=0, j=0;
  while (i != strlen(A)-1 && j!= strlen(B)-1 && A[i]==B[i]) {
    i++;
    j++;
  }
  if(i == strlen(A)-1 && j == strlen(B)-1)
    return 1;
  return -1;
}

static int compare_two_Matrix(int **A, int **B, int dimension){
  assert(A != NULL && B != NULL);

  for (size_t i = 0; i < dimension; i++) {
    for (size_t j = 0; j < dimension; j++) {
      if(A[i][j] != B[i][j])
        return -1;
    }
  }
  return 1;
}

void free_matrix_code(int **M){
  assert(M != NULL);

  for (size_t i = 0; i < DIMESION; i++) {
    free(M[i]);
  }
  free(M);
}

static void test_to_binary(){
  assert_int_equal(1, compare_two_table(to_binary(155),to_binary(155),8));
  assert_int_equal(1, compare_two_table(to_binary(1),to_binary(1),1));
  assert_int_equal(1, compare_two_table(to_binary(9500735), to_binary(9500735), 24));
  assert_int_equal(-1, compare_two_table(to_binary(29), to_binary(27), 5));
  assert_n_array_equal(to_binary(155),to_binary(155),8);
  assert_n_array_equal(to_binary(7877),to_binary(7877),13);
}

static void test_get_file_name(){
  assert_string_equal("","");
  assert_string_equal(get_file_name(""),get_file_name(""));
  assert_string_equal(get_file_name("/home/student/Bureau/barre/codebarre.txt")
                     ,get_file_name("/home/student/Bureau/barre/codebarre.txt"));
  assert_int_equal(-1, compare_two_string("toto.txt", "titi.txt"));
  assert_int_equal(1, compare_two_string("code.txt", "code.txt"));
}

static void test_fil_matrix_code(){
  assert_int_equal(1, compare_two_Matrix(fil_matrix_code(177), fil_matrix_code(177), 70));
  assert_int_equal(1, compare_two_Matrix(fil_matrix_code(1), fil_matrix_code(1), 70));
  assert_int_equal(-1, compare_two_Matrix(fil_matrix_code(132), fil_matrix_code(133), 70));
  assert_int_equal(-1, compare_two_Matrix(fil_matrix_code(1), fil_matrix_code(2), 70));
}

static void test_fil_last_matrix_bloc(){
  int **A = fil_matrix_code(637); //la fct fil_matrix_code fait appelle a fil last bloc
  int **B = fil_matrix_code(637); //la fct fil_matrix_code fait appelle a fil last bloc
  int **C = fil_matrix_code(515); //la fct fil_matrix_code fait appelle a fil last bloc

  assert_int_equal(1, (compare_two_Matrix(A, B, DIMESION)));
  assert_int_equal(-1, (compare_two_Matrix(A, C, DIMESION)));
  assert_int_equal(-1, (compare_two_Matrix(C, B, DIMESION)));

  free_matrix_code(A);
  free_matrix_code(B);
  free_matrix_code(C);
}

static void test_create_PNM(){
  int number = 320;

  PNM* image1 = NULL;
  char magiqueNumber[4] = "PBM";
  set_nLines(image1, DIMESION);
  set_nColumns(image1, DIMESION);
  set_maxPix(image1, 0);
  set_MagicNumber(image1, magiqueNumber);
  set_Matrix(image1, fil_matrix_code(number));

  PNM* image2 = NULL;
  image2 = create_PNM(number);

  assert_string_equal(get_MagicNumber(image1), get_MagicNumber(image2));


}

static void test_fixture(){
  test_fixture_start();
  run_tests(test_check_is_ulg_code);
  run_tests(test_to_binary);
  run_tests(test_get_file_name);
  run_tests(test_fil_matrix_code);
  run_tests(test_fil_last_matrix_bloc);
  run_tests(test_create_PNM);
  test_fixture_start();
}

static void all_tests(){
  test_fixture();
}

int main(){
  return run_tests(all_tests);
}
