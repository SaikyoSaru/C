#include <stdio.h>
#include <math.h>
#include <limits.h>

int divide(int a, int b)
{

  int q;
  q = a >> b;

  if(a < 0 && (a & ((1 << b) -1 )) != 0){
    q += 1;

  }
  return q;
}

int main()
{
  int a;
  
  a = divide(16,2);
  
  printf("q = %d \n", a);

}



