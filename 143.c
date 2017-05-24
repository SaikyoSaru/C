#include <stdio.h>


void swap(int *a,int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
  
}

void order(int *a, int *b) {

  if(*b<*a){
    swap(a,b);
  }
}

int main(void) {


  int a,b;
  printf("enter two numbers:");
  scanf("%d %d",&a,&b);
  printf("a = %d b = %d\n",a,b);
  order(&a,&b);
  printf("a = %d b = %d\n",a,b);
  



}
