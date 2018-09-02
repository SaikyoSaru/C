#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double b, B;

typedef struct fraction fraction;

struct fraction {
  intmax_t n;
  intmax_t d;
};

void *xmalloc(size_t size) {
  void *p = malloc(size);
  if (p == NULL) {
    printf("not enough memory");
  }
  return p;
}

void printer(size_t rows, size_t cols, fraction **fracs) {
  fprintf(stderr, "PRINTER\n");
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      printf("%jd/%jd, ", fracs[i][j].n, fracs[i][j].d);
    }
    printf("\n");
  }
  fprintf(stderr, "PRINTER DONE!\n");
}

/*
 * greatest common divider for reducing fractions
 */
intmax_t gcd_func(int a, int b) {
  a = (a > 0) ? a : -a;
  b = (b > 0) ? b : -b;

  while (a != b) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
  }
  return a;
}

fraction new_frac(intmax_t n, intmax_t d) {
  fraction f;
  f.n = n;
  f.d = d;
  return f;
}

fraction reduce(fraction f) {
  if (f.n != 0) {
    intmax_t gcd = gcd_func(f.n, f.d);
    f.n /= gcd;
    f.d /= gcd;
  }
  return f;
}

fraction add_frac(fraction a, fraction b) {
  fraction f;
  f.d = a.d * b.d;
  f.n = a.n * b.d + b.n * a.d;
  return reduce(f);
}

fraction mul_frac(fraction a, fraction b) {
  fraction f;
  f.d = a.d * b.d;
  f.n = a.n * b.n;
  return reduce(f);
}

fraction div_frac(fraction a, fraction b) {
  fraction f;
  f.d = a.d * b.n;
  f.n = a.n * b.d;
  return reduce(f);
}

bool fm(size_t rows, size_t cols, signed char a[rows][cols],
        signed char c[rows]) {

  int n_pos, n_neg;

  fraction **A = calloc(rows, sizeof(fraction));
  for (size_t i = 0; i < rows; i++) {
    A[i] = calloc(cols + 1, sizeof(fraction));
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(stderr, "value: %d, ", a[i][j]);
      A[i][j] = new_frac(a[i][j], 1);
    }
    A[i][cols] = new_frac(c[i], 1);
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "A + C :\n");
  printer(rows, cols + 1, A);
  // final part checking if there is a solution


  if (n_neg > n_pos) {
    // b = max of all elements that are smaller than x1
  } else {
    b = -INFINITY;
  }

  if (n_pos > 0) {
    // B = min of all elements thatr are bigger than x1
  } else {
    B = INFINITY;
  }
  free(A);
  if (B < b || (b < 0 && B > 0)) {
    return 1;
  }

  return 0;
}

int sort_value(double value) {
  if (value > 0) {
    return -2;
  } else if (value < 0) {
    return -1;
  } else {
    return 0;
  }
}

void rearrange_matrix(signed char **a, int el_var, size_t rows, size_t cols) {
  signed char temp = 0;
  for (size_t i = 0; i < rows; i++) {
    temp = a[i][el_var];
    a[i][el_var] = a[i][0];
    a[i][0] = temp;
  }
}

/*
 *  For testing.. remove when done
 */
int main() {
  int cols = 2;
  int rows = 7;
  char A[7][2] = {{2, -11}, {-3, 2}, {1, 2}, {-2, 1}, {-4, 3}, {0, 1}, {0, 2}};
  char C[7] = {1, 1, 1, 1, 1, 1, 1};

  fm(rows, cols, A, C);
}
