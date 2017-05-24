#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // creates a pointer which will point to the memory location which
  // the string is saved, aka the location of c
 
char *copy(const char *src)
{
  char *c = malloc(strlen(src)+1);
  strcpy(c,src);
  return c;
}
// does the same thing, but a smoother version
char *cpy(const char *src) { 
  return strcpy(malloc(strlen(src)+1),src);
}

int main(void){
  char challe[] = "challe balle"; // the original string
  char *res = cpy(challe); // the result of the copy
  printf("%s\n",res); 
}
