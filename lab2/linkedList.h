#include <iostream>
#include <stdexcept>
#include <random>
#include <cstddef>

template <typename T>
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
    
    size_t size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    void clear() 
    {
      if (!head) return;
      if (!head->next) {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
      }
      tail->next = nullptr; 
      Node* p = head;
      while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
      }
      head = nullptr;
      tail = nullptr;
      size = 0;
    }

  public:
    size_t get_size() const 
    {
      return size;
    }
    //bool empty() const { return size == 0; }

    LinkedList() = default;
    
    ~LinkedList()
     { 
      clear(); 
    }

    LinkedList(size_t size_, T min_, T max_, unsigned int seed) 
    {
      if (size_ == 0) throw std::invalid_argument("size cannot be = 0");
      if (min_ > max_) throw std::invalid_argument("min > max");

      std::mt19937 gen(seed);
      std::uniform_int_distribution<long long> dist(static_cast<long long>(min_), static_cast<long long>(max_));
      
      for (size_t i = 0; i < size_; ++i) {
        push_tail(static_cast<T>(dist(gen)));
      }
    } 

    // Копирование
    LinkedList(const LinkedList& other) 
    {
      Node* p = other.head;
      if (!p) return;
      do {
        push_tail(p->value);
        p = p->next;
      } while (p != other.head);
    }

    LinkedList& operator=(const LinkedList& other)
    {
      if (this == &other) return *this;
      clear();
      Node* p = other.head;
      if (!p) return *this;
      do {
        push_tail(p->value);
        p = p->next;
      } while (p != other.head);
      return *this;
    }
    
    void push_tail(const T& value) {
      Node* node = new Node(value);
      if (size == 0) {
        node->next = node;
        node->prev = node;
        head = node;
        tail = node;
      } else {
        node->next = head;
        node->prev = tail;
        tail->next = node;
        head->prev = node;
        tail = node;
      }
      size++;
    }

    void push_tail(const LinkedList& other) {
      Node* p = other.head;
      if (p == nullptr) return; 
      do {
        push_tail(p->value);
        p = p->next;
      } while (p != other.head);
    }

    void push_head(const T& value) {
      push_tail(value);
      head = tail;
      tail = tail->prev;
    }

    void push_head(const LinkedList& other) {
      Node* p = other.tail;
      if (!p) return;
      do {
        push_head(p->value); 
        p = p->prev;
      } while (p != other.tail);
    }
  
    void pop_head() {
      if (size == 0) throw std::out_of_range("pop_head: empty");
      Node* deleted = head;
      if (size == 1) {
        head = nullptr;
        tail = nullptr;
      } else {
        head = head->next;
        head->prev = tail;
        tail->next = head;
      }
      delete deleted;
      size--;
    }

    void pop_tail() {
      if (size == 0) throw std::out_of_range("pop_tail: empty");
      Node* deleted = tail;
      if (size == 1) {
        head = nullptr;
        tail = nullptr;
      } else {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
      }
      delete deleted;
      size--;
    }

    void delete_node(const T& val) {
      if (size == 0) return;
      Node* p = head; 
      do {
        Node* next_node = p->next;
        if (p->value == val) {
          if (size == 1) {
            head = nullptr;
            tail = nullptr;
          } else {
            p->next->prev = p->prev;
            p->prev->next = p->next;
            if (p == head) head = p->next;
            if (p == tail) tail = p->prev;
          }
          delete p;
          size--;
        }
        p = next_node;
      } while (p != head && size > 0); 
    }
    
    
    T& operator[](long long index) {
      if (size == 0) throw std::out_of_range("[]: list is empty");
      long long real_i = index % static_cast<long long>(size);
      if (real_i < 0) real_i += size;
      
      Node* p = head;
      for (long long i = 0; i < real_i; ++i) {
        p = p->next;
      }
      return p->value;
    }

  
    const T& operator[](long long index) const {
      if (size == 0) throw std::out_of_range("[]: list is empty");
      long long real_i = index % static_cast<long long>(size);
      if (real_i < 0) real_i += size;
      
      Node* p = head;
      for (long long i = 0; i < real_i; ++i) {
        p = p->next;
      }
      return p->value;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
      os << "[";
      for (size_t i = 0; i < list.get_size(); ++i) {
        if (i > 0) os << ", ";
        os << list[i];
      }
      os << "]";
      return os;
    } ////ало   т тири
}; 

template <typename T>
void reverse_list(LinkedList<T>& list) {
  if (list.get_size() < 2) return; 

  LinkedList<T> temp;
  while (list.get_size() > 0)
  {
    temp.push_head(list[0]);
    list.pop_head();
  } 
  list = temp;
}