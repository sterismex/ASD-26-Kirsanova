#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>


template <typename T>
class Vector
{
    private:
    T* data_;
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
        if (size_ == 0)
        {
        throw std::invalid_argument("Vector size cannot be = 0");
        }
        data_ = new T[size_];
        for (size_t i = 0; i<size_; ++i)
        {
            data_[i] = value;
        }
    }

    Vector (size_t size, const double& min_v, const double& max_v)
    {
        size_ = size;
        if (size_ == 0)
        {
        throw std::invalid_argument("Vector size cannot be = 0");
        }
        data_ = new T[size_];
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min_v, max_v);

        for (size_t i = 0; i<size_; ++i)
        {
            if constexpr (std::is_same_v<T, std::complex<float>> || 
              std::is_same_v<T, std::complex<double>>)
              {
                data_[i] = T(dis(gen), dis(gen));
              }
              else { data_[i] = static_cast<T>(dis(gen)); }
        }
    }

    ~Vector() 
    {
        delete[] data_;
    }

    Vector (const Vector& other)
    {
        size_ = other.size_;
        data_ = new T[size_];
        for (size_t i = 0; i < size_; ++i)
        {
             data_[i] = other.data_[i];
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (this == &other) 
        {
            return *this;
        }
        delete [] data_;
        size_ = other.size_;
        data_ = new T[size_];
        for (size_t i = 0; i<size_; ++i)
        {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    T& operator [] (size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range ("Index cannot be bigger than vector size");
        }
        return data_[index];
    }

    const T& operator [] (size_t index) const
    {
         if (index >= size_)
        {
            throw std::out_of_range ("Index cannot be bigger than vector size");
        }
        return data_[index];
    }
}; 


int main ()
{
   std::cout << "Охаё-дфттебаё";
    return 0;
}