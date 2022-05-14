#include <math.h>
#include "Algebra.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

double sq (double v) {return v*v;};

int main ()
{
   Matrix m1(4, 4);
   Matrix m2(4, 4);

   m1.identity();
   m2.randomize(1, 0, 10);

   Matrix m3 = m1;

   std::cout << m1 << std::endl;
   std::cout << m2 << std::endl;
   std::cout << m3 << std::endl;
   std::cout << m1*m2 << std::endl;
   std::cout << m1+m2 << std::endl;
   std::cout << (m1*=3) << std::endl;
   std::cout << m1.function(sq) << std::endl;

   FILE* fp1 = fopen("mat.dat", "wb");

   m3.store(fp1);
   fclose(fp1);

   FILE* fp2 = fopen("mat.dat", "rb");
   Matrix m4(fp2);
   fclose(fp1);

   std::cout << m4 << std::endl;
   return 1;
}