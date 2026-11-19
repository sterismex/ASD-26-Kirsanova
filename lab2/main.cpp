#include "linkedList.h" 

int main ()
{
    //генерация рандом списка
LinkedList<int> random_list(5, 1, 99, 67);
//присваивание
LinkedList <int> copy = random_list;
//вывод
std::cout << "random(seed=67): " << random_list << '\n' << std::endl;
std::cout << copy << std::endl;

//пуш тейл и хэд
LinkedList<int> l1(5,1,99,42);
LinkedList<int> l2(5,1,99,69);
std::cout <<'\n' << "before push  " << l1 << '\n' << l2 << '\n' << std::endl;
l1.push_head(15);
l1.push_tail(6);
std::cout << "after push  " << l1 << '\n' << std::endl;
l1.push_head(copy);
l2.push_tail(copy);
std::cout << "after push" << l1 << '\n' << l2 << '\n' << std::endl;

//поп хэд и хвост
l1.pop_head();
l1.pop_tail();
std::cout << '\n' << "after pop  " << l1 << '\n' << std::endl;

//удаление узла
l2.delete_node(59);
std::cout << '\n' << "l2 after delete_node  " << l2 << '\n' << std::endl;

//индекс

std::cout << "\nl2[0] = " << l2[0] << std::endl;
    std::cout << "l2[9] = " << l2[9] << " (9 % 9 = 0)" << std::endl;
    std::cout << "l2[-9] = " << l2[-9] << " (-9 + 9 = 0)" << std::endl;
    
    l2[1] = 666;
    std::cout << "l2 with 666:  " << l2 << std::endl;

return 0;
}