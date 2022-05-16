#include <math.h>
#include "Algebra.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

double sq (double v) {return v*v;}; 

int main ()
{
   Vector v1(4, 2.0);
   Vector v2(4);
   Matrix m1(4, 4);
   m1.identity();
   v2.randomize(1, 0, 10);

   Vector v3 = v1;  
   std::cout << v1 << std::endl;
   std::cout << v2 << std::endl;
   std::cout << v3 << std::endl;
   std::cout << v1*v2 << std::endl;   
   std::cout << v1+v2 << std::endl;
   std::cout << (v1*=3) << std::endl;
   v1.function(sq);
   std::cout << v1 << std::endl;
   std::cout << v1*m1 << std::endl;   
   std::cout << m1*v1 << std::endl;   

   FILE* fp1 = fopen("vet.dat", "wb");
   v3.store(fp1);
   fclose(fp1);

   FILE* fp2 = fopen("vet.dat", "rb");
   Vector v4(fp2);
   fclose(fp1);

   std::cout << v4 << std::endl;
   return 1;
}