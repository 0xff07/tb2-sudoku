#include<iostream>
#include<cstdio>
#include"sudoku.h"
using namespace std;



int main()
{
  int data[81];
    for(int i = 0; i < 81; i++)scanf("%d", &data[i]);
  Sudoku test(data);
  test.solve();
  printf("\n");
  test.giveQuestion();
 

/*
  printf("\nchange_single_row\n\n");
  test.change_single_row(0, 8);
  test.print_out();
  printf("\n");

  printf("change_single_col\n\n");
  test.change_single_col(0, 8);
  test.print_out();
  printf("\n");

  printf("changeRow\n\n");
  test.changeRow(0, 2);
  test.print_out();
  printf("\n");

  printf("ChangeCol\n\n");
  test.changeCol(0, 2);
  test.print_out();
  printf("\n");

  printf("Transpose\n\n");
  test.transpose();
  test.print_out();
  printf("\n");

  for(int i = 0; i < 5; i++)
  {
    printf("rotate(%d)\n\n", i);
    test.rotate(i);
    test.print_out();
    printf("\n");
  }
 
  for(int i = 0; i < 2; i++)
  {
    printf("flip(%d)\n\n", i);
    test.flip(i);
    test.print_out();
    printf("\n");
  }
  printf("giveQuestion\n\n");
  test.giveQuestion();


  test.change_function();
  test.function_state();
  test.solve();
  printf("\n");
*/

  return 0;
}
