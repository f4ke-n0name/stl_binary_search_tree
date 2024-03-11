#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

// TODO -- логика для функциональных классов, реализовать методы bst

template <typename T>
struct Node {
  T value;
  Node* left;
  Node* right;
  Node* parent;
  Node(T& data) {
    value = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

template <typename T>
struct InOrder {
  typedef T value_type;
  typedef Node<value_type> node_type;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;

  std::vector<iterator> massive_;
  iterator root_;
  size_t size_;
  size_t i = 0;
  void inorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    inorder(node->left, massive_);
    massive_.push_back(node->data);
    inorder(node->right, massive_);
  }
  InOrder(size_t size, iterator root) : size_{size} { inorder(root_); }
  iterator begin() { return massive_[0]; }
  iterator end() { return massive_[size_]->left; }
  iterator operator++() {
    if (i < size_) {
      return massive_[++i];
    } else {
      return end();
    }
  }
  iterator operator--() {
    if (i >= size_) {
      return massive_[--i];
    } else {
      return begin();
    }
  }
  iterator operator++(int) {
    if (i >= size_) {
      return end();
    }
    iterator copy_iteartor = massive_[i];
    if (i < size_) {
      ++i;
    }
    return copy_iteartor;
  }
  iterator operator--(int) {
    if (i < 0) {
      return nullptr;
    }
    iterator copy_iteartor = massive_[i];
    if (i >= size_) {
      --i;
    }
    return copy_iteartor;
  }
  std::reverse_iterator<iterator> rbegin() {
    return std::reverse_iterator<iterator>(begin());  // ????
  }
  std::reverse_iterator<iterator> rend() {
    return std::reverse_iterator<iterator>(end());  // ????
  }
};
struct PostOrder {};  // скопировать с InOrder и переписать обход
struct PreOrder {};  // скопировать с InOrder и переписать обход
template <class T, class Traversal = InOrder<T>, class Compare = std::less<T>,
          class Allocator = std::allocator<T> >
class bst {
 private:
  typedef T value_type;
  typedef Node<value_type> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef Allocator allocator_type;

  iterator root_;
  size_type size_;
  size_type max_size_;
  Traversal traversal_;
  allocator_type allocator_;

 public:
  bst() : root_{nullptr}, size_{0}, max_size_{15352} {}
  bst(const bst& other)
      : root_{other.root_}, size_{other.size_}, max_size_{other.max_size_} {
    // написать функцию копирования
    // функция копирования реализуется через insert по preorder обходу.
  }
  bst& operator=(const bst& other) {
    // написать функцию копирования
    // функция копирования реализуется через insert по preorder обходу.
  }
  ~bst() {
    root_ = nullptr;
    size_ = 0;
    max_size_ = 15352;
    // написать деструктор
    // еструктор реализуется через erase по post order обходу
  }
  // Container Requirements
  const_iterator begin() { return traversal_(size, root_).begin(); }
  const_iterator end() { return traversal_(size, root_).end(); }
  bool operator==(const bst& other) const {
    return std::equal(this.begin(), this.end(), other.begin(), other.end());
  }
  bool operator!=(const bst& other) const { return !(this == other); }
  void swap(bst& other) { std::swap(this->root_, other->root_); }
  size_type size() const { return size_; }
  size_type max_size() const { return max_size_; }
  bool empty() const { return size_ == 0; }
  // BidirectionalIterator
  reference operator++() const { return traversal_(size, root_)++; }
  reference operator++(int) const { return ++traversal_(size, root_); }
  reference operator--() const { return --traversal_(size, root_); }
  reference operator--(int) const { return traversal_(size, root_)--; }
  // ReversibleContainer
  reverse_iterator rbegin() const {
    return traversal_(size, root_).rbegin();
  }  // ???
  reverse_iterator rend() const {
    return traversal_(size, root_).rend();
  }  // ???
  // AssociativeContainer

  iterator insert(const_iterator node, const value_type& x) {
    if (node == nullptr) {
      ++size_;
      node = allocator_.allocate(1);
      allocator_.construct(node, x);
      return node;
    }
    if (Compare()(x, node->value)) {
      node->left = insert(node->left, x);
      node->left->parent = node;
    } else {
      node->right = insert(node->right, x);
      node->right->parent = node;
    }
    return node;
  }

  void merge(const bst& other) {
    for (auto i = other.begin(); i != other.end(); ++i) {
      value_type x = *i.value;
      this->insert(root_, x);
    }
    other.clear();
  }

  iterator erase(const_iterator node, const value_type& x) {
    if (node == nullptr) {
      return node;
    }
    if (Compare()(x, node->value)) {
      node->left = erase(node->left, x);
    } else if (Compare()(node->value, x)) {
      node->right = erase(node->right, x);
    } else {
      if (node->left == nullptr) {
        iterator current = node->right;
        current->parent = node->parent;
        --size_;
        allocator_.destroy(node);
        node = allocator_.deallocate(1);
        return current;
      } else if (node->right == nullptr) {
        iterator current = node->left;
        current->parent = node->parent;
        allocator_.destroy(node);
        node = allocator_.deallocate(1);
        --size_;
        return current;
      }
      iterator current = minimum(node->right);
      node->value = current->value;
      node->right = erase(node->right, current->value);
    }

    return node;
  }
  void clear() { ~bst(); }
  iterator find(const_iterator node) {} // реализовать сие безобразие
  size_type count(const_iterator node) {
    size_type count = 0;
    for (auto i = this->begin(); i != this->end(); ++i) {
      if (i == node) {
        ++count;
      }
    }
    return count;
  }
  bool contains(const_iterator node) { return this->count(node) != 0; }
  iterator lower_bound(const_iterator node) {}  // реализовать prev
  iterator upper_bound(const_iterator node) {}  // реализовать next

  allocator_type get_allocator() { return allocator_; }
};

template <class T, class Traversal, class Compare = std::less<T>,
          class Allocator = std::allocator<T> >
void swap(bst<T, Traversal>& lhs, bst<T, Traversal>& rhs) {
  lhs.swap(rhs);
}
