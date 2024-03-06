#include <iostream>

template <typename T>
struct Node {
    T value;
    Node* left;
    Node* right;
};

template <
    class T,
    class Compare = std::less<T>,
    class Allocator = std::allocator<T>
>
class bst {
 private:
    T value_type;
    T& reference;
    const T& const_reference;
    T* iterator;
    const T* const_iterator;
    size_t size_type;
 public:

};
