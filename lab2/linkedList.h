#include <iostream>
#include <stdexcept>
#include <random>

template < typename T>
class LinkedList 
{
  private:
    struct Node 
    {
      T value;
      Node* next = nullptr;
      Node* prev = nullptr;
      Node() = default;
      Node(const T& v) 
      {
        value = v;
      }
    };
    size_t size;
   
    public:

    Node<T>* head;
    Node<T>* tail;
    
    size_t get_size () const
    {
        return size_;
    }

    LinkedList () {
      head = nullptr;
      tail = nullptr;
      size = 0;
    }



    LinkedList (size_t size_, T min_, T max_, unsigned int seed) {
      size = size_;
      if (size==0){
        throw std::invalid_argument("size cannot be = 0");
      }
      if (min_ > max_) throw std::invalid_argument("min > max");

      std::mt19937 gen(seed);
      std::uniform_int_distribution<T> dist(static_cast<T>(min_), static_cast<T>(max_));


    }

    LinkedList (const LinkedList& other) 
    {
      
    }

    ~LinkedList(){
      clear();
    }

    

};