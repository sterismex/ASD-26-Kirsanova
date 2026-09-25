#include <iostream>
#include <complex>


template <typename T>
class vector
{
    private:
    T* vector;
    int size = 0;
    int capacity=0;
    
    public:
    int get_size () const
    {
        return size;
    }
    int get_capasity () const
    {
        return capacity;
    }



}; 


int main ()
{
    return 0;
}