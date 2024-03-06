#include <iostream>
#include <memory>

// TODO: функциональный объект для 3-ех обходов дерева (inorder, preorder,
// postorder) с помощью tag dispatching , реализовать остальные методы bst для
// stl совместимости и реализовать остальные типы контейнеров

template <typename T>
struct Node {
  T value;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
};
template <class T, class Tresval, class Compare = std::less<T>,
          class Allocator = std::allocator<T> >
class bst {
 private:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef size_t size_type;

  std::unique_ptr<value_type> root;

 public:
  bst();
  bst(const bst& other);
  reference operator=(const bst& other) {
    if (this != &other) {
      root = other.root;
    }
    return *this;
  }
  ~bst();
  const_iterator begin() const;
  const_iterator end() const;
  bool operator==(const bst& other) const;
  bool operator!=(const bst& other) const;
  void swap(bst& other);
  size_type size() const;
  size_type max_size() const;
  bool empty() const;
};

template <class T,class Tresval, class Compare = std::less<T>,
          class Allocator = std::allocator<T> >
void swap(bst<T, Tresval>& lhs, bst<T, Tresval>& rhs);
