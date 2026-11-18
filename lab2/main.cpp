#include "linkedList.h" 

int main ()
{
LinkedList<int> random_list(5, 1, 99, 42);
std::cout << "random(seed=42): " << random_list << std::endl;
return 0;
}