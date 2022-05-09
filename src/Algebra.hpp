#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

class Matrix
{
   friend ostream& operator<< (ostream& os, const Matrix& m);
   friend Matrix operator+ (const Matrix& m1, const Matrix& m2);
   friend Matrix operator- (const Matrix& m1, const Matrix& m2);
   virtual friend Matrix operator* (const Matrix& m1, const Matrix& m2);

   public:
   Matrix (int r, int c);
   Matrix (int r, int c, double v);
   Matrix (FILE* fp);
   ~Matrix ();
   virtual double* operator[] (int r) { return data + r * columns};
   Matrix& operator= (const Matrix& m);
   Matrix& operator+= (const Matrix& m);
   Matrix& operator-= (const Matrix& m);
   Matrix& operator*= (double v);
   
   Matrix& function (double (*f)(double));
   Matrix& randomize();
   int load (FILE* fp);
   int store (FILE* fp);


   private:
   double *data;
   int rows;
   int columns;
}

class Vector : public Matrix
{
   friend double operator* (const Vector& v1, const Vector& v2);

   public:
   Vector (int d);
   Vector (int d, double v);   
   double& operator[] (int i) { return *(data + i);};
}