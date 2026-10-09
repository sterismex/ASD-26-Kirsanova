
#include <iostream>
#include "vector.h"

int main ()
{
  std::cout << "1 лабораторная работа Кирсановой Ирины 6212" << '\n' << "8 вариант, задача 2" << std::endl;
  
  Vector<int> v(5, 0.0, 10.0); 
   
   Vector<int> o(5, 0.0, 10.0);
   std::cout << "first: " << v << '\n' << "second: " << o << '\n' << std::endl;
   
   std::cout << "scalar multiplication: "<< v*o << '\n'<< "additive scalar multiplication: " << v*5 << '\n' << 5*v << '\n' << "dividing a vector by a scalar: " << v/2 << '\n' << std::endl;
   Vector<int> filled(5, 7);
   std::cout << "filled with 7: " << filled << std::endl;
   

   Vector<int> assigned(5, 0);
   assigned = o;
   std::cout << "assigned o to assigned: " << assigned << std::endl;

   std::cout << "v[0] = " << v[0] << std::endl;
   v[0] = 100;
   std::cout << "v after v[0] = 100: " << v << std::endl;

   std::cout << "v + o: " << (v + o) << std::endl;
   std::cout << "v - o: " << (v - o) << std::endl;

   Vector<int> copy = v;
   std::cout << "copy of v: " << copy << std::endl;

   std::cout << "v == o: " << (v == o) << std::endl;
   std::cout << "v != o: " << (v != o) << std::endl;
   std::cout << "v == copy: " << (v == copy) << std::endl;

   std::cout << "Size of v: " << v.get_size() << std::endl;

   Vector<double> a(3, 1.0, 5.0);
   Vector<double> b(3, 1.0, 5.0);
   std::cout << "a = " << a << std::endl;
   std::cout << "b = " << b << std::endl;
   Vector<double> bis = find_bisector(a, b);
   std::cout << "Bisector = " << bis << std::endl;

   return 0;
}