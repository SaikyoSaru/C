#include <stdio.h>


void input(double a[], size_t size) {
  size_t i;

  for(i = 0; i < size; i++ ) {
    printf("enter number:");
    scanf("%lf",&a[i]);
  }
}

void print(double a[], size_t size) {
  size_t i;

  for(i = 0; i < size; i++ ) {
    printf(" [%zu]: %lf\n",i,a[i]);

  }
}
double sum(double *a, size_t len) {
  double sum = 0;
  size_t i;
  while (len--)
    sum += *a++;
  return sum;
}


int main(void) {

  int SIZE;
  char answer;
  printf("How many numbers do you want to store?");
  scanf("%d", &SIZE);

  
  double a[SIZE];
  input(a, SIZE);
  print(a, SIZE);

  printf("want to calculate the total?\n y/n\n");
  scanf(" %c",&answer);
  //printf("answer %c\n",answer);

  if(answer =='y') {
    double res = sum(a,SIZE);
    printf("Sum: %lf\n",res);
  
  }
  


  


}
