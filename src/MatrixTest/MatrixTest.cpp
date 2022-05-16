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
   Matrix n1(3, 6, 1.0);
   Matrix n2(6, 5, 2.0);

   m1.identity();
   m2.randomize(1, 0, 10);

   Matrix n3 = n1;
   
   std::cout << m1 << std::endl;
   std::cout << m2 << std::endl;
   std::cout << n3 << std::endl;
   std::cout << n1*n2 << std::endl;   
   std::cout << m1*m2 << std::endl;
   std::cout << m1+m2 << std::endl;
   std::cout << (m1*=3) << std::endl;
   std::cout << m1.function(sq) << std::endl;

   FILE* fp1 = fopen("mat.dat", "wb");

   n3.store(fp1);
   fclose(fp1);

   FILE* fp2 = fopen("mat.dat", "rb");
   Matrix n4(fp2);
   fclose(fp1);

   std::cout << n4 << std::endl;
   return 1;
}