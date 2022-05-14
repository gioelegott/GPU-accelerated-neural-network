#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <string.h>

class Vector;

class Matrix
{
   friend std::ostream& operator<< (std::ostream& os, const Matrix& m);
   friend Matrix operator+ (const Matrix& m1, const Matrix& m2);
   friend Matrix operator- (const Matrix& m1, const Matrix& m2);
   friend Matrix operator* (const Matrix& m1, const Matrix& m2);
   friend Vector operator* (const Vector& v1, const Matrix& m2);
   friend Vector operator* (const Matrix& m1, const Vector& v2);
   friend double operator* (const Vector& v1, const Vector& v2);

   public:
   Matrix (int r, int c);
   Matrix (int r, int c, double v);
   Matrix (const Matrix& m);
   Matrix (FILE* fp);
   ~Matrix ();
   int Rows() const { return rows; };
   int Columns() const { return columns; };
   double* operator[] (int r) { return data + r * columns; };
   Matrix& operator= (const Matrix& m);
   Matrix& operator+= (const Matrix& m);
   Matrix& operator-= (const Matrix& m);
   Matrix& operator*= (double v);
   
   Matrix& function (double (*f)(double));
   Matrix& randomize (unsigned seed, double h, double l);
   Matrix& identity ();
   int load (FILE* fp);
   int store (FILE* fp) const;


   protected:
   double *data;
   int rows;
   int columns;
};

class Vector : public Matrix
{
   friend Vector operator* (const Vector& v1, const Matrix& m2);
   friend Vector operator* (const Matrix& m1, const Vector& v2);
   friend double operator* (const Vector& v1, const Vector& v2);

   public:
   Vector (int d);
   Vector (int d, double v);   
   int Length() const {return columns;};
   double& operator[] (int i) { return *(data + i);};
};