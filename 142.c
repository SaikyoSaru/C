#include <stdio.h>

void swap(int *a,int *b){
  int tmp= *a;
  *a=*b;
  *b=tmp;
  
}

int main(void){

  int a,b;
  printf("enter two values:");
  scanf("%d %d",&a ,&b);
  printf("a = %d b = %d\n",a,b);
  swap(&a, &b);
  printf("a = %d b = %d\n",a,b);
  
}
