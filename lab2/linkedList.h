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
    Node* head;
    Node* tail;
    void clear ()
    {
      if (!head) return;
      if (!head -> next)
      {
        delete head;
        head = nullptr;
        return;
      }
      tail -> next = nullptr;
      Node* p = head;
      while (p != nullptr) 
      {
         Node* next = p->next;
         delete p;
         p = next;
      }
      head = nullptr;
      tail = nullptr;
      size = 0;
    }
    public:

    size_t get_size () const
    {
        return size;
    }

    LinkedList () {
      head = nullptr;
      tail = nullptr;
      size = 0;
    }
    
    ~LinkedList()
    {
      clear();
    }
    
    void push_tail (const T& value) {
      Node* node = new Node<T>(value);
      if (size == 0)
      {
        node -> next = node;
        node -> prev = node;
        head = node;
        tail = node;
      } else {
        node -> next = head;
        node -> prev = tail;
        tail -> next = node;
        head -> prev = node;
        tail = node;
      }
      size++;
    }

    void push_tail (const LinkedList& other){
      Node* p = other.head;
      if (p == nullptr) return this;
      do {
        push_tail(p -> value);
        p = p->next;
      } while (p != other.head);
    }

    void push_head (const T& value)
    {
      push_tail(value);
      head = tail;
      tail = tail -> prev;
    }

    void push_head (const LinkedList& other)
    {
      Node* p = other.tail;
      if (!p) return;
      do 
      {
        push_head(p->val);
        p = p->prev;
      } while (p != other.tail);
  }

  
    }



    LinkedList (size_t size_, T min_, T max_, unsigned int seed) {
      size = size_;
      if (size==0){
        throw std::invalid_argument("size cannot be = 0");
      }
      if (min_ > max_) throw std::invalid_argument("min > max");

      std::mt19937 gen(seed);
      std::uniform_int_distribution<T> dist(static_cast<T>(min_), static_cast<T>(max_));
      for (int i = 0; i<size; ++i)
      {
        push_tail(static_cast<T> (dist(gen)));
      }
    } 
    
   

//копирование
    LinkedList (const LinkedList& other) 
    {
      
    }

   

    

};