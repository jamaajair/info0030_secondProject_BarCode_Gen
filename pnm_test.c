#include "pnm.h"
#include "seatest.h"

static void test_load_write_pnm(){
  PNM* image1= NULL;
  PNM* image2= NULL;
  PNM* image3= NULL;

  int i = load_pnm(&image1, "scs.pbm");
  int j = load_pnm(&image2,"monalisa.pgm");
  int k = load_pnm(&image3,"antilope.ppm");

  /*------------------le bon fonctionnement du load_pnm----------------------*/
  assert_int_equal(0,i);
  assert_int_equal(0,j);
  assert_int_equal(0,k);

  /*-------------------le bon fonctionnement du write_pnm-----------------------*/
  int l= write_pnm(image1,"scs-copie.pbm");
  int m= write_pnm(image2,"monalisa-copie.pgm");
  int n= 
}

static void test_fixture(){
  test_fixture_start();
  run_tests(test_load_pnm);
  test_fixture_end();
}

static void all_tests(){
  test_fixture();
}

int main(){
  return run_tests(all_tests);
}
