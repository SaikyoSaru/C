#include <stdio.h>
#include <limits.h>
#include <math.h>


int intBits (int tmp) {
  int count=0;
  
  while(tmp) {
    tmp >>=1;
    count++;
  }
  return count;
}


int main(){

  
  int bits = intBits(sizeof(unsigned int));

  printf("Number of bits:%d\n",bits);

}
