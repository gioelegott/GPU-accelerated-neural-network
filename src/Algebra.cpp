#include <math.h>
#include "Algebra.h"
#include <stdio.h>
#include <stdlib.h>

Matrix::Matrix (int r, int c) : rows(r), columns(c)
{
   if ((data = (double*)malloc(r * c * sizeof(double))) == NULL)
   {
      fprintf(stderr, "Memoria non allocata");
      exit(1);
   }
}

Matrix::Matrix (int r, int c, double v) : rows(r), columns(c)
{
   if ((data = (double*)calloc(r * c, sizeof(double))) == NULL)
   {
      fprintf(stderr, "Memoria non allocata");
      exit(1);
   }

   if (v != 0.0)
   {
      int i;
      double* ptr;
      for (i = 0, ptr = data; i < r * c; i++, ptr++)
         *ptr = v;
   }
}

Matrix::Matrix (FILE* fp)
{
   if (fwrite (&(this->rows), sizeof(int), 1, fp) == 0)
   {
      fprintf(stderr, "Error in loading matrix\n");
      exit(1);
   }

   if (fwrite (&(this->columns), sizeof(int), 1, fp) == 0)
   {
      fprintf(stderr, "Error in loading matrix\n");
      exit(1);
   }

   int dim = this->rows * this->columns;
   if (fwrite(this->data, sizeof(double), dim, fp) != dim)
   {
      fprintf(stderr, "Error in loading matrix\n");
      exit(1);
   }
}

Matrix::~Matrix ()
{
   free(data);
}

Matrix& Matrix::operator= (const Matrix& m)
{
   if (this->rows != m.rows || this->columns != m.columns)
   {
      fprintf(stderr, "Assignement not possible\n");
      exit(1);
   }

   memcpy(this->data, m.data, m.rows * m.columns * sizeof(double));

   return *this;
}

Matrix& Matrix::operator+= (const Matrix& m)
{
   if (this->rows != m.rows || this->columns != m.columns)
   {
      fprintf(stderr, "Assignement not possible\n");
      exit(1);
   }

   int i;
   double *ptr1, *ptr2;
   for (i = 0, ptr1 = this->data, ptr2 = m.data; i < m.rows * m.columns; i++, ptr1++, ptr2++)
      *ptr1 += *ptr2;
   return *this;

}

Matrix& Matrix::operator-= (const Matrix& m)
{
   if (this->rows != m.rows || this->columns != m.columns)
   {
      fprintf(stderr, "Assignement not possible\n");
      exit(1);
   }

   int i;
   double *ptr1, *ptr2;
   for (i = 0, ptr1 = this->data, ptr2 = m.data; i < m.rows * m.columns; i++, ptr1++, ptr2++)
      *ptr1 -= *ptr2;

   return *this;
}

Matrix& Matrix::operator*= (double v)
{
   int i;
   double* ptr;
   for (i = 0, ptr = data; i < r * c; i++, ptr++)
      *ptr *= v;
   
   return *this;
}

Matrix& Matrix::function (double (*f)(double))
{
   int i;
   double* ptr;
   for (i = 0, ptr = data; i < r * c; i++, ptr++)
      *ptr = f(*ptr);
   
   return *this;
}

void randomize (unsigned seed, double h, double l)
{
   int i;
   double* ptr;
   double s = h - l;
   srand(seed);
   for (i = 0, ptr = data; i < r * c; i++, ptr++)
      *ptr = ((double)rand()/(double)RAND_MAX) * span + l;

}

int Matrix::store (FILE* fp)
{
   /*Stores the matrix into a binary file.
     Returns 1 if load was successful 0 if not*/

   int r = this->rows;
   int c = this->columns;

   if (fwrite (&(this->rows), sizeof(int), 1, fp) == 0)
   {
      fprintf(stderr, "Error in loading matrix\n");
      return 0;
   }

   if (fwrite (&(this->columns), sizeof(int), 1, fp) == 0)
   {
      fprintf(stderr, "Error in loading matrix\n");
      return 0;
   }

   if (fwrite(this->data, sizeof(double), r * c, fp) != r * c)
   {
      fprintf(stderr, "Error in loading matrix\n");
      return 0;
   }

   return 1;

}


int Matrix::load (FILE* fp)
{
   /*Loads the matrix into a binary file.
     Returns 1 if load was successful 0 if not*/

   int r, c;

   if (fread (&r), sizeof(int), 1, fp) == 0)
   {
      fprintf(stderr, "Error in loading matrix\n");
      return 0;
   }

   if (fread (&c, sizeof(int), 1, fp) == 0)
   {
      fprintf(stderr, "Error in loading matrix\n");
      return 0;
   }

   if (r != this->rows || c != this->columns)
   {
      fprintf(stderr, "Matrix dimension does not correspond\n");
      return 0;
   }

   if (fread(this->data, sizeof(double), r * c, fp) != r * c)
   {
      fprintf(stderr, "Error in loading matrix\n");
      return 0;
   }

   return 1;
}

ostream& operator<< (ostream& os, const Matrix& m)
{
   int i, j;
   for (i = 0, ptr = data; i < r; i++, ptr++)
   {
      for (j = 0; j < c; j++, ptr++)
         os << *ptr << ' ';
      os << endl;
   }
}


Matrix operator+ (const Matrix& m1, const Matrix& m2)
{
   int r = m1.rows;
   int c = m1.columns;
   if (r != m2.rows || c != m2.columns)
   {
      fprintf (stderr, "Sum is not possible between matreces with different dimensions\n");
      exit (1);
   }

   Matrix m(r, c);
   int i;
   double *ptr1, *ptr2, *ptr;
   for (i = 0, ptr1 = m1.data, ptr2 = m2.data, ptr = m.data; i < r * c; i++, ptr1++, ptr2++, ptr++)
      *ptr = *ptr1 + *ptr2;

   return m;
}

Matrix operator- (const Matrix& m1, const Matrix& m2)
{
   int r = m1.rows;
   int c = m1.columns;
   if (r != m2.rows || c != m2.columns)
   {
      fprintf (stderr, "Subtraction is not possible between matreces with different dimensions\n");
      exit (1);
   }

   Matrix m(r, c);
   int i;
   double *ptr1, *ptr2, *ptr;
   for (i = 0, ptr1 = m1.data, ptr2 = m2.data, ptr = m.data; i < r * c; i++, ptr1++, ptr2++, ptr++)
      *ptr = *ptr1 - *ptr2;

   return m; 
}

Matrix operator* (const Matrix& m1, const Matrix& m2)
{

   if (m1.columns != m2.rows)
   {
      fprintf (stderr, "Multiplication is not possible\n");
      exit (1);
   }

   Matrix m(m1.rows, m2.columns);
   int i, j, k;
   double *ptr1, *ptr2, *ptr;
   double val;

   for (i = 0, ptr = m.data; i < r1; i++, ptr++)
   {
      for (j = 0; j < c2; j++, ptr++)
      {
         val = 0.0;
         for (k = 0, ptr1 = m1.data + i * m1.columns, ptr2 = m2.data + j; k < m1.columns; k++, ptr1++, ptr2 += m2.columns)
         {
            val += *ptr1 * *ptr2;
         }
         *ptr = val;
      }
   }

   return m;
}
