#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
double b,B
bool fm(size_t rows, size_t cols, signed char a[rows][cols], signed char c[rows])
{
char **A = calloc(rows,sizeof(signed char));
 for (int i = 0; i < rows; i++) {
   A[i] = calloc(cols+1,sizeof(signed char));
 }

 for (int i = 0; i < rows; i++) {
   for (int j = 0; j < cols; j++){
     A[i][j] = a[i][j];
   }
 }
 
 for(int i = 0; i < rows; i++){
   A[rows][i] = c[i];
 }


  printf(%d,a);


  // final part checking if there is a solution
  if  (n_neg > n_pos) {
    // b = max of all elements that are smaller than x1 
  } else {
    b = -INFINITY;
  }

  if (n_pos > 0){
    //B = min of all elements thatr are bigger than x1
  } else {
    B = INFINITY;
  }
  free(A);
  if (B < b || (b < 0 && B > 0)) {
    return 1;
  }

  return 0;
}


int sort_value(double value){
  if (value > 0){
    return -2;
  }
  else if (value < 0) {
    return -1;
  }
  else {
    return 0;
  }
}


void rearrange_matrix(signed char a[rows][cols], int el_var, size_t rows, size_t cols){
  signed char temp = 0;
  for (int i = 0; i < rows;i++){
    temp = a[i][el_var];
    a[i][el_var] = a[i][0];
    a[i][0] = temp;

  }
  
}

