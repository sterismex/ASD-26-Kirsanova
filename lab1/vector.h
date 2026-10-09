#include <iostream>
#include <complex>
#include <stdexcept>
#include <random>
#include <cmath> 


template <typename T>
class Vector
{
    private:
    T* data_;
    size_t size_ = 0;
    
    public:
    static inline double epsilon = 1e-9;
    
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

    Vector operator + (const Vector& other) const
    {
        if (size_ != other.size_)
        {
            throw std::invalid_argument("Vector sizes must match.");
        }
        Vector result (size_);
        for (size_t i = 0; i<size_; ++i)
        {
            result[i] = data_[i] + other.data_[i];
        }
        return result;
    }
    Vector operator - (const Vector& other) const
    {
        if (size_ != other.size_)
        {
            throw std::invalid_argument("Vector sizes must match.");
        }
        Vector result (size_);
        for (size_t i = 0; i<size_; ++i)
        {
            result[i] = data_[i] - other.data_[i];
        }
        return result;
    }

    T operator* (const Vector& other) const
    {
        if (size_ != other.size_)
        {
            throw std::invalid_argument("Vector sizes must match.");
        }
        T result = T();
        for (size_t i = 0; i<size_; ++i)
        {
            result += data_[i] * other.data_[i];
        }
        return result;
    }
    Vector operator* (const T& num) const
    {
        Vector result (size_);
        for (size_t i = 0; i<size_; ++i)
        {
            result[i] = data_[i]*num;
        }
        return result;
    }

    Vector operator/ (const T& num) const
    {
       if (std::abs(num) < epsilon)
       {
        throw std::invalid_argument("Are you insane? Who dares to divide by zero?");
       }
       
        Vector result (size_);
        for (size_t i = 0; i<size_; ++i)
        {
            result[i] = data_[i]/num;
        }
        return result;
    }
    
    bool operator==(const Vector& other) const
     {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i) 
        {
        if (std::abs(data_[i] - other.data_[i]) > epsilon) 
        {
            return false;
        }
        }
    return true;
    }

bool operator!=(const Vector& other) const 
{
    return !(*this == other);
}

friend std::ostream& operator<<(std::ostream& os, const Vector& vec) 
{
    os << "[";
    for (size_t i = 0; i < vec.size_; ++i) {
        os << vec.data_[i];
        if (i < vec.size_ - 1) os << ", ";
    }
    os << "]";
    return os;
}

}; 

template <typename T>
Vector<T> operator*(const T& num, const Vector<T>& vec)
{
    return vec.operator*(num);  
}

template <typename T>
Vector<T> find_bisector(const Vector<T>& a, const Vector<T>& b)
{
    if (a.get_size() != b.get_size())
    {
        throw std::invalid_argument("Vectors must be of the same size.");
    }

    double norm_a = 0.0;
    double norm_b = 0.0;

    for (size_t i = 0; i < a.get_size(); ++i)
    {
        norm_a += std::norm(a[i]); 
        norm_b += std::norm(b[i]);
    }

    norm_a = std::sqrt(norm_a);
    norm_b = std::sqrt(norm_b);

    if (norm_a < Vector<T>::epsilon || norm_b < Vector<T>::epsilon)
    {
        throw std::invalid_argument("Cannot find bisector for a zero vector.");
    }

    Vector<T> unit_a = a / static_cast<T>(norm_a);
    Vector<T> unit_b = b / static_cast<T>(norm_b);

    return unit_a + unit_b;
}