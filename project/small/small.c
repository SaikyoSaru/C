#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct frac
{
	intmax_t n;
	intmax_t d;
} frac;

/**
 * Printer function for debugging purposes
*/
// void printer(size_t rows, size_t cols, frac fracs[rows][cols])
// {
//   fprintf(stderr, "PRINTER\n");
//   for (size_t i = 0; i < rows; i++)
//   {
//     for (size_t j = 0; j < cols; j++)
//     {
//       printf("%jd/%jd, ", fracs[i][j].n, fracs[i][j].d);
//     }
//     printf("\n");
//   }
//   fprintf(stderr, "PRINTER DONE!\n");
// }

/*
* Function for finding out which sign the frac have
* –1: negative, 0: zero, 1: positive 
*/
int sign(frac frac)
{
	return (frac.n > 0) ? 1 : (frac.n == 0 ? 0 : -1);
}

/*
 * greatest common divider for reducing fracs
 */
intmax_t gcd(intmax_t a, intmax_t b)
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
	return (frac){.n = n, .d = d};
}

/*
* Function for reducing the size of the fraction
*/
frac reduce(frac f)
{
	if (f.n != 0 && f.d != 0)
	{
		intmax_t gcd_v = gcd(f.n, f.d);
		f.n /= gcd_v;
		f.d /= gcd_v;
	}
	return f;
}

/*
* Function for addition between fracs
*/
frac add_frac(frac a, frac b)
{
	return reduce(new_frac(a.n * b.d + b.n * a.d, a.d * b.d));
}

/*
* Function for multipaction between fracs
*/
frac mul_frac(frac a, frac b)
{
	return reduce(new_frac(a.n * b.n, a.d * b.d));
}

frac div_frac(frac a, frac b)
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
			f.n *= -1;
	}
	return reduce(f);
}
/*
* Function for swapping rows
*/
void swap_rows(size_t from, size_t to, size_t rows, size_t cols, frac a[rows][cols])
{
	frac temp;
	for (size_t i = 0; i < cols; i++)
	{
		temp = a[from][i];
		a[from][i] = a[to][i];
		a[to][i] = temp;
	}
}

void row_divide(size_t row, size_t rows, size_t cols, frac a[rows][cols])
{
	if (a[row][cols - 2].n != 0)
		for (size_t i = 0; i < cols; i++)
			if (i != cols - 2)
				a[row][i] = div_frac(a[row][i], a[row][cols - 2]);
}

/*
* Method for comparing two fracs
*/
int comp_frac(frac a, frac b)
{
	intmax_t tmp = a.n * b.d - b.n * a.d;
	return tmp < 0 ? -1 : tmp == 0 ? 0 : 1;
}

/*
* Sorting function, arranges rows as: pos, neg, zero
*/
void sort_rows(size_t rows, size_t cols, frac a[rows][cols],
			   size_t *n_pos, size_t *n_neg)
{
	int t;
	size_t v = cols - 2;
	size_t p = 0;
	for (size_t i = 0; i < rows; i++)
	{
		t = sign(a[i][v]);
		if (t > 0)
			swap_rows(i, p++, rows, cols, a);
	}
	(*n_pos) = p;
	for (size_t i = p; i < rows; i++)
	{
		t = sign(a[i][v]);
		if (t < 0)
			swap_rows(i, p++, rows, cols, a);
	}
	(*n_neg) = p;
}

/*
 * Recursive Fourier Motzkin function 
*/
bool fm_frac(size_t rows, size_t cols, frac A[rows][cols])
{
	//Variables for the different steps in the algorithm
	// variables
	size_t i, j, k, n_pos, n_neg;
	// The real amount of variables in matrix
	size_t v = cols - 1;
	// sort rows according to + - 0
	sort_rows(rows, cols, A, &n_pos, &n_neg);
	// divide all elements by the current element
	for (i = 0; i < rows; i++)
		row_divide(i, rows, cols, A);
	// printer(rows, cols, A);
	// check how many rows needed for new matrix
	size_t r_new = rows - n_neg + n_pos * (n_neg - n_pos);

	// all either pos or neg == solvable!
	if (r_new == 0)
		return true;

	// check if there are more variables to remove
	if (v > 1)
	{
		// create new array for exclusion of the current variable
		frac N[r_new][v];
		// keep track of current row
		size_t r = 0;
		// for the creation of the new matrix
		frac frac = {.n = -1, .d = 1};
		for (i = 0; i < n_pos; i++)
			for (j = n_pos; j < n_neg; j++)
			{
				for (k = 0; k < v; k++)
					N[r][k] = add_frac(mul_frac(A[j][k], frac), A[i][k]);
				// since we remove the current variable, we skip it in iteration and handle it after
				N[r][v - 1] = add_frac(mul_frac(A[j][v], frac), A[i][v]);
				r++;
			}
		// Handle the ones without any of the current variable
		for (i = n_neg; i < rows; i++)
		{
			for (j = 0; j < v; j++)
				N[r][j] = A[i][j];
			r++;
		}
		return fm_frac(r_new, v, N);
	}
	else
	{
		// // no more variable to remove take final steps for finding out if the system is solvable
		// starting values for min max check
		frac max = A[n_pos][v];
		frac min = A[0][v];
		// search through the values to find new max and min
		// find the smallest value of the positive ones
		for (i = 1; i < n_pos; i++)
			min = comp_frac(A[i][v], min) < 0 ? A[i][v] : min;

		// find the largest value of the negative ones
		for (i = n_pos + 1; i < n_neg; i++)
			max = comp_frac(A[i][v], max) > 0 ? A[i][v] : max;

		// check the remaining values, they can't be negative!
		for (i = n_neg; i < rows; i++)
			if (sign(A[i][v]) < 0)
				return false;
		// if the smallest of the pos is larger than the largest of the negative
		// return true!
		return (comp_frac(min, max) > 0);
	}
}

bool fm(size_t rows, size_t cols, signed char a[rows][cols],
		signed char c[rows])
{
	size_t i, j;
	frac A[rows][cols + 1];

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			A[i][j] = new_frac(a[i][j], 1);
		A[i][cols] = new_frac(c[i], 1);
	}
	// return the result of recursive function
	return fm_frac(rows, cols + 1, A);
}
