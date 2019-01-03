#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct frac frac;

struct frac
{
  intmax_t n;
  intmax_t d;
};

void *xmalloc(size_t size)
{
  void *p = malloc(size);
  if (p == NULL)
  {
    printf("not enough memory");
  }
  return p;
}

/*
* Function for finding out which sign the frac have
* –1: negative, 0: zero, 1: positive 
*/
int sign(frac frac)
{
  return (frac.n < 0) ? (-1) : (frac.n == 0 ? 0 : 1);
}

void printer(size_t rows, size_t cols, frac fracs[rows][cols])
{
  fprintf(stderr, "PRINTER\n");
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      printf("%jd/%jd, ", fracs[i][j].n, fracs[i][j].d);
    }
    printf("\n");
  }
  fprintf(stderr, "PRINTER DONE!\n");
}

/*
 * greatest common divider for reducing fracs
 */
intmax_t gcd_func(intmax_t a, intmax_t b)
{
  a = (a > 0) ? a : -a;
  b = (b > 0) ? b : -b;

  while (a != b)
  {
    if (a > b)
    {
      a -= b;
    }
    else
    {
      b -= a;
    }
  }
  return a;
}

frac new_frac(int n, int d)
{
  frac f;
  f.n = n;
  f.d = d;
  return f;
}

/*
* Handles both reducing the size of the frac as well
* as correction the -
*/
frac reduce(frac f)
{
  if (f.n != 0)
  {
    intmax_t gcd = gcd_func(f.n, f.d);
    while ((gcd = gcd_func(imaxabs(f.n), f.d)) != 1)
    {
      f.n /= gcd;
      f.d /= gcd;
    }
  }
  return f;
}

/*
* Function for addition between fracs
*/
frac add_frac(frac a, frac b)
{
  frac f;
  f.d = a.d * b.d;
  f.n = a.n * b.d + b.n * a.d;
  return reduce(f);
}

/*
* Function for multipaction between fracs
*/
frac mul_frac(frac a, frac b)
{
  frac f;
  f.d = a.d * b.d;
  f.n = a.n * b.n;
  return reduce(f);
}

frac div_frac(frac a, frac b)
{
  if (b.n != 0)
  {
    frac f;
    f.d = a.d * b.n;
    f.n = a.n * b.d;
    // Check if both fracs are negative and correct if needed
    if (a.n < 0 && b.n < 0)
    {
      f.n *= -1;
      f.d *= -1;
    }
    // Check if any are negative and correct if needed
    if ((a.n < 0 || b.n < 0) && f.d < 0)
    {
      f.d *= -1;
      if (f.n > 0)
      {
        f.n *= -1;
      }
    }

    return reduce(f);
  }
  return a;
}

/*
* Function for swapping rows
*/
void swap_rows(int from, int to, size_t rows, size_t cols, frac a[rows][cols])
{
  frac temp;
  for (size_t i = 0; i < cols; i++)
  {
    temp = a[from][i];
    a[from][i] = a[to][i];
    a[to][i] = temp;
  }
}

/*
* Function for swapping columns
*/
void swap_cols(int el_var, size_t rows, size_t cols, frac a[rows][cols])
{
  frac temp;
  for (size_t i = 0; i < rows; i++)
  {
    temp = a[i][el_var];
    a[i][el_var] = a[i][0];
    a[i][0] = temp;
  }
}

void row_divide(size_t row, size_t rows, size_t cols, frac a[rows][cols])
{
  for (size_t i = 0; i < cols; i++)
  {
    if (i != cols - 2)
      a[row][i] = div_frac(a[row][i], a[row][cols - 2]);
  }
  // a[row][cols - 2] = (frac){.n = 1, .d = 1};
}

/*
* Method for comparing two fracs
*/
int comp_frac(frac a, frac b)
{
  int tmp = a.n * b.d - b.n * a.d;
  return tmp < 0 ? -1 : tmp == 0 ? 0 : 1;
}

/*
* Sorting function, arranges rows as: pos, neg, zero
*/
void sort_rows(size_t rows, size_t cols, frac a[rows][cols],
               size_t *n_pos, size_t *n_neg)
{
  // fprintf(stderr, "sorting time\n");
  // printer(rows, cols, a);
  int pos = 0;
  size_t z = rows - 1;
  for (size_t i = 0; i <= z; i++)
  {
    int t = sign(a[i][cols - 2]);
    if (t > 0)
    {
      (*n_pos)++;
      swap_rows(i, pos++, rows, cols, a);
      // printer(rows, cols, a);
    }
    else if (t == 0)
    {
      (*n_neg)--;
      swap_rows(i--, z--, rows, cols, a);
      // printer(rows, cols, a);
    }
  }
}

/*
 * Recursive Fourier Motzkin function 
*/
bool fm_frac(size_t rows, size_t cols, frac A[rows][cols])
{
  //Variables for the different steps in the algorithm
  // looping variables
  size_t i, j, l;
  // step 1
  size_t v = cols - 1; // The real amount of variables
  size_t row_p = v - 1;
  // size_t s = rows;
  // step 2
  size_t n_pos = 0;
  size_t n_neg = rows;
  //Convert int array to frac array
  sort_rows(rows, cols, A, &n_pos, &n_neg);
  // fprintf(stderr, "After sorting:\n");

  // printer(rows, cols, A);

  // fprintf(stderr, "Divide all rows!!\n");
  for (i = 0; i < rows; i++)
  {
    row_divide(i, rows, cols, A);
  }
  // printer(rows, cols, A);

  // final part checking if there is a solution

  // check if there is more variables
  if (v > 1)
  {
    // step 4
    // if all pos or all negative == solvable!
    size_t r_new = rows - n_neg + n_pos * (n_neg - n_pos);
    // not sure if ok here, should be ok?
    // if (s_prim == 0)
    // {
    //   fprintf(stderr, "hepp\n");
    //   return true;
    // }

    // create new array excluding the current variable
    frac N[r_new][v];
    // fprintf(stderr, "s_prim:%d, v:%d\n", s_prim, v);
    size_t r = 0;
    // for the creation of the new matrix
    frac frac = {.n = -1, .d = 1};
    // fprintf(stderr, "n_neg: %d\n", n_neg);
    for (i = 0; i < n_pos; i++)
      for (j = n_pos; j < n_neg; j++)
      {
        for (l = 0; l < row_p; l++)
        {
          N[r][l] = add_frac(mul_frac(A[j][l], frac), A[i][l]);
        }
        N[r][row_p] = add_frac(A[i][v], mul_frac(frac, A[j][v]));
        r++;
      }
    // Handle the ones without any of the current variable
    for (i = n_neg; i < rows; i++)
    {
      for (j = 0; j < row_p; j++)
      {
        N[r][j] = A[i][j];
      }
      N[r][row_p] = A[i][v];
      r++;
    }

    fprintf(stderr, "next iteration or done\n");
    printer(r_new, v, N);
    return fm_frac(r_new, v, N);
  }
  else
  {
    // no more variable to remove take final steps for finding out if the system is solvable
    // a quick check if the system is solvable (All pos or all Negative)
    if ((rows - n_neg + n_pos * (n_neg - n_pos)) == 0)
    {
      return true;
    }
    // get starting values (start from each side)
    frac max = A[n_pos][v];
    frac min = A[0][v];
    // search through the values to find new max and min
    for (i = 1; i < n_pos; i++)
    {
      if (comp_frac(A[i][v], min) == -1)
      {
        min = A[i][v];
      }
    }

    for (i = n_pos + 1; i < n_neg; i++)
    {
      if (comp_frac(A[i][v], max) == 1)
      {
        max = A[i][v];
      }
    }

    for (i = n_neg; i < rows; i++)
    {
      if (sign(A[i][v]) == -1)
      {
        return false;
      }
    }

    // final comparison!
    return (comp_frac(min, max) == 1);
  }
}

bool fm(size_t rows, size_t cols, int a[rows][cols],
        int c[rows])
{
  //Variables
  size_t i, j;

  frac A[rows][cols + 1];

  // convert matrix to fracs
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      A[i][j] = new_frac(a[i][j], 1);
    }
    A[i][cols] = new_frac(c[i], 1);
  }
  // return the result of recursive function
  return fm_frac(rows, cols + 1, A);
}

/*
 *  For testing.. remove when done
 */
int main()
{
  // True
  // int cols = 2;
  // int rows = 3;
  // signed char A[3][2] = {{91, -111}, {123, -107}, {-105, -20}};
  // signed char C[3] = {-68, -69, -45};
  // False
  int cols = 2;
  int rows = 4;
  int A[4][2] = {{-115, 104}, {-72, 59}, {113, 21}, {-17, -110}};
  int C[4] = {113, 46, -51, -71};

  // int cols = 2;
  // int rows = 7;
  // int A[7][2] = {{2, -11}, {-3, 2}, {1, 2}, {-2, 1}, {-4, 3}, {0, 1}, {0, 2}};
  // int C[7] = {1, 1, 1, 1, 1, 1, 1};

  int res = fm(rows, cols, A, C);
  fprintf(stderr, "result: %d\n", res);
}
