#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>


template <typename T>
class Vector
{
    private:
    T* data;
    size_t size_ = 0;
    
    public:
    static double epsilon;
    
    int get_size () const
    {
        return size_;
    }
    
    Vector (size_t size, const T& value = T())
    {
        size_ = size;
        if (size_ == 0)
        {
        throw std::invalid_argument("Vector size cannot be zero.");
        }
        data = new T[size_];
        for (int i = 0; i<size_; ++i)
        {
            data[i] = value;
        }
    }



}; 


int main ()
{
   std::cout << "Охаё";
    return 0;
}