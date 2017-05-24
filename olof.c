#include <stdio.h>

int main(int argc, char** argv) {
  int a;
  float b;
  double c;

  scanf("%d %f %lf\n", &a, &b, &c);
  printf("%lf\n", a+ b+ c);
}


