#include <stdio.h>


double sum(double a[], size_t len) {
  double result = 0;
  size_t i;
  for (int i = 0; i < len; i++)
    result += a[i];
  return result;
}

double sum2(double *a, size_t len){
  double sum = 0;
  size_t i;
  while (len--)
    sum += *a++;
  return sum;
}


int main(void) {
  double test[] = {0.0, 1.2, 2.8};
  double res1 = sum2(test,sizeof test / sizeof *test);
  double res2 = sum(test,sizeof test / sizeof *test); 
  printf("test:%lu\n",sizeof test / sizeof *test);
  printf("result 1: %f\n",res2);
  printf("result 2: %f\n",res1);
  return 0;
}
