/**
 * \file pnm_test_c
 *
 * \brief INFO0030 Projet 2 - Code Barre
 * \author Jamaa JAIR s207171
 * \version 0.1
 * \date 29/07/2022
 *
 * Ce fichier contient les test unitaires du fichier pnm.c
 *  et les prototypes des fonctions pour coder les matricules des étudiants de l'ULG.
 */

#include "pnm.h"
#include "seatest.h"

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

  int o= write_pnm(image1,"scs-cop<<ie.pbm");
  int p= write_pnm(image2,"totem-co>>pie.pgm");
  int q= write_pnm(image3,"anti/lope-c/opie,pgm");

  assert_int_equal(-1,o);
  assert_int_equal(-1,p);
  assert_int_equal(-1,q);

  //free_image(image1);
  //free_image(image2);
  //free_image(image3);
}

static void test_fixture(){
  test_fixture_start();
  run_tests(test_load_write_pnm);
  test_fixture_end();
}

static void all_tests(){
  test_fixture();
}

int main(){
  return run_tests(all_tests);
}
