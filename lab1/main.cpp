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
    
    size_t get_size () const
    {
        return size_;
    }
    
    Vector (size_t size, const T& value = T())
    {
        size_ = size;
        if (size_ <= 0)
        {
        throw std::invalid_argument("Размер вектора должен быть больше нуля.");
        }
        data = new T[size_];
        for (int i = 0; i<size_; ++i)
        {
            data[i] = value;
        }
    }

    Vector (size_t size, const T& min, const T& max)
    {
        size_ = size;
        if (size_ <= 0)
        {
        throw std::invalid_argument("Размер вектора должен быть больше нуля.");
        }
        data = new T[size_];
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);

        for (size_t i = 0; i<size_; ++i)
        {
            if constexpr (std::is_same_v<T, std::complex<float>> || 
              std::is_same_v<T, std::complex<double>>)
              {
                data[i] = T(dis(gen), dis(gen));
              }
              else { data[i] = static_cast<T>(dis(gen)); }
        }
    }

    ~Vector() 
    {
        delete[] data;
    }

    Vector (const Vector& other)
    {
        size_ = other.size_;
        data = new T[size_];
    }



}; 


int main ()
{
   std::cout << "Охаё";
    return 0;
}