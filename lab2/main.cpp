#include "linkedList.h" 

int main ()
{
LinkedList<int> random_list(5, 1, 99, 67);
LinkedList <int> copy = random_list;

std::cout << "random(seed=67): " << random_list << std::endl;
std::cout << copy << std::endl;



return 0;
}