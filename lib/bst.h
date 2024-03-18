#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

struct PreOrder {};
struct InOrder {};
struct PostOrder {};

template <class T, class Traversal>
struct Iterator {};

template <class T>
class Iterator<T, InOrder> {
  typedef T value_type;
  typedef Iterator<T, InOrder> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  value_type value;
  iterator left;
  iterator right;
  iterator parent;
  std::vector<iterator> iterators_order;
  size_t size;
  size_t it;

  void inorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    inorder(node->left, iterators_order);
    iterators_order.push_back(node->value);
    inorder(node->right, iterators_order);
  }

  Iterator() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  Iterator(value_type& data) {
    value = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  Iterator(size_t size, iterator root) : size{size} {
    inorder(root);
    it = 0;
  }

  iterator operator++() {
    if (it < size) {
      return iterators_order[++it];
    } else {
      return iterators_order[size - 1]->left;
    }
  }

  iterator operator--() {
    if (it >= size) {
      return iterators_order[--it];
    } else {
      return iterators_order[0];
    }
  }

  iterator operator++(int) {
    if (it >= size) {
      return iterators_order[size - 1]->left;
    }
    iterator copy_iteartor = iterators_order[it];
    if (it < size) {
      ++it;
    }
    return copy_iteartor;
  }

  iterator operator--(int) {
    if (it < 0) {
      return nullptr;
    }
    iterator copy_iteartor = iterators_order[it];
    if (it >= size) {
      --it;
    }
    return copy_iteartor;
  }

  reference operator*() { return &iterators_order[it]; }

  bool operator==(const_reference other) {
    return (this->value == other.value) && (this->left == other.left) &&
           (this->right == other.right) && (this->parent == other.parent);
  }

  bool operator!=(const_reference other) { return !(this == other); }
};
template <typename T>
struct Iterator<T, PostOrder> {
  typedef T value_type;
  typedef Iterator<T, InOrder> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  value_type value;
  iterator left;
  iterator right;
  iterator parent;
  std::vector<iterator> iterators_order;
  size_t size;
  size_t it;

  void postorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    postorder(node->left, iterators_order);
    postorder(node->right, iterators_order);
    iterators_order.push_back(node->value);
  }

  Iterator() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  Iterator(value_type& data) {
    value = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  Iterator(size_t size, iterator root) : size{size} {
    postorder(root);
    it = 0;
  }

  iterator operator++() {
    if (it < size) {
      return iterators_order[++it];
    } else {
      return iterators_order[size - 1]->left;
    }
  }

  iterator operator--() {
    if (it >= size) {
      return iterators_order[--it];
    } else {
      return iterators_order[0];
    }
  }

  iterator operator++(int) {
    if (it >= size) {
      return iterators_order[size - 1]->left;
    }
    iterator copy_iteartor = iterators_order[it];
    if (it < size) {
      ++it;
    }
    return copy_iteartor;
  }

  iterator operator--(int) {
    if (it < 0) {
      return nullptr;
    }
    iterator copy_iteartor = iterators_order[it];
    if (it >= size) {
      --it;
    }
    return copy_iteartor;
  }

  reference operator*() { return &iterators_order[it]; }

  bool operator==(const_reference other) {
    return (this->value == other.value) && (this->left == other.left) &&
           (this->right == other.right) && (this->parent == other.parent);
  }

  bool operator!=(const_reference other) { return !(this == other); }
};

template <class T>
struct Iterator<T, PreOrder> {
  typedef T value_type;
  typedef Iterator<T, InOrder> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  value_type value;
  iterator left;
  iterator right;
  iterator parent;
  std::vector<iterator> iterators_order;
  size_t size;
  size_t it;

  void preorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    iterators_order.push_back(node->value);
    preorder(node->left, iterators_order);
    preorder(node->right, iterators_order);
  }

  Iterator() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  Iterator(value_type& data) {
    value = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  Iterator(size_t size, iterator root) : size{size} {
    postorder(root);
    it = 0;
  }

  iterator operator++() {
    if (it < size) {
      return iterators_order[++it];
    } else {
      return iterators_order[size - 1]->left;
    }
  }

  iterator operator--() {
    if (it >= size) {
      return iterators_order[--it];
    } else {
      return iterators_order[0];
    }
  }

  iterator operator++(int) {
    if (it >= size) {
      return iterators_order[size - 1]->left;
    }
    iterator copy_iteartor = iterators_order[it];
    if (it < size) {
      ++it;
    }
    return copy_iteartor;
  }

  iterator operator--(int) {
    if (it < 0) {
      return nullptr;
    }
    iterator copy_iteartor = iterators_order[it];
    if (it >= size) {
      --it;
    }
    return copy_iteartor;
  }

  reference operator*() { return &iterators_order[it]; }

  bool operator==(const_reference other) {
    return (this->value == other.value) && (this->left == other.left) &&
           (this->right == other.right) && (this->parent == other.parent);
  }

  bool operator!=(const_reference other) { return !(this == other); }
};
template <class T, class Traversal = InOrder, class Compare = std::less<T>,
          class Allocator = std::allocator<T> >
class bst {
 private:
  typedef T value_type;
  typedef Iterator<value_type, Traversal> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;
  typedef Allocator allocator_type;

  iterator root_;
  size_type size_;
  size_type max_size_;
  iterator it_;
  allocator_type allocator_;
  iterator begin_;
  iterator end_;
  iterator rbegin_;
  iterator rend_;

  void preorder(iterator node, std::vector<iterator>& iterators_order) {
    if (node == nullptr) {
      return;
    }
    iterators_order.push_back(node->data);
    preorder(node->left, iterators_order);
    preorder(node->right, iterators_order);
  }

  void postorder(iterator node, std::vector<iterator>& iterators_order) {
    if (node == nullptr) {
      return;
    }
    if (node == nullptr) {
      return;
    }
    postorder(node->left, iterators_order);
    postorder(node->right, iterators_order);
    iterators_order.push_back(node->data);
  }

 public:
  bst()
      : root_{nullptr},
        size_{0},
        max_size_{15352},
        it_{nullptr},
        begin_{nullptr},
        end_{nullptr},
        rbegin_{nullptr},
        rend_{nullptr} {}
  bst(const bst& other)
      : root_{nullptr},
        size_{0},
        max_size_{15352},
        it_{nullptr},
        begin_{nullptr},
        end_{nullptr},
        rbegin_{nullptr},
        rend_{nullptr} {
    other = allocator_.allocate(1);
    allocator_.construct(other);
    std::vector<iterator> iterators_order;
    size_t i = 0;
    preorder(this->root_, iterators_order);
    while (i < size_) {
      other.insert(other.root_, iterators_order[++i]);
    }
  }

  bst(iterator i, iterator j) {
    for (iterator current = i; current != j; ++current) {
      this->insert(this->root_, *current);
    }
  }

  bst(iterator i, iterator j, Compare c) {
    for (iterator current = i; current != j; ++current) {
      this->insert(this->root_, *current, c);
    }
  }

  bst(std::initializer_list<value_type>& il) {
    for (value_type* i = il.begin(); i != il.end(); ++i) {
      this->insert(root_, *i);
    }
  }

  bst(std::initializer_list<value_type>& il, Compare c) {
    for (value_type* i = il.begin(); i != il.end(); ++i) {
      this->insert(root_, *i, c);
    }
  }

  bst& operator=(const bst& other) {
    bst new_bst = allocator_.allocate(1);
    allocator_.construct(new_bst);
    new_bst.size_ = this->size_;
    std::vector<iterator> iterators_order;
    size_t i = 0;
    preorder(other->root_, iterators_order);
    while (i < size_) {
      new_bst.insert(new_bst.root_, iterators_order[++i]);
    }
    return &new_bst;
  }

  ~bst() {
    std::vector<iterator> iterators_order;
    postorder(root_, iterators_order);
    for (size_type i = 0; i < size_; ++i) {
      erase(root_, iterators_order[i]);
    }
    root_ = nullptr;
    size_ = 0;
    max_size_ = 15352;
    it_ = nullptr;
    begin_ = nullptr;
    end_ = nullptr;
    rbegin_ = nullptr;
    rend_ = nullptr;
  }

  iterator begin() { return begin_; }

  iterator end() { return end_; }

  const_iterator begin() const { return begin_; }

  const_iterator end() const { return end_; }

  bool operator==(const bst& other) const {
    return std::equal(this.begin(), this.end(), other.begin(), other.end());
  }

  bool operator!=(const bst& other) const { return !(this == other); }

  void swap(bst& other) { std::swap(this->root_, other->root_); }

  size_type size() const { return size_; }

  size_type max_size() const { return max_size_; }

  bool empty() const { return size_ == 0; }

  reference operator++() const { return ++it_; }

  reference operator++(int) const { return it_++; }

  reference operator--() const { return --it_; }

  reference operator--(int) const { return it_--; }

  reference operator*() { return *it_; }

  iterator rbegin() const { return rbegin_; }

  iterator rend() const { return rend_; }

  iterator insert(const_iterator node, const value_type& x,
                  Compare comparator) {
    if (node == nullptr) {
      ++size_;
      node = allocator_.allocate(1);
      allocator_.construct(node, x);
      return node;
    }
    if (comparator(x, node->value)) {
      node->left = insert(node->left, x);
      node->left->parent = node;
    } else {
      node->right = insert(node->right, x);
      node->right->parent = node;
    }
    it_(size_, root_);
    begin_ = it_.iterators_order[0];
    end_ = it_.iterators_order[size_ - 1].left;
    rbegin_ = end_;
    rend_ = begin_;
    return node;
  }

  iterator insert(iterator i, iterator j) {
    iterator result;
    for (iterator current = i; current != j; ++current) {
      result = this->insert(this->root_, *current);
    }
    return result;
  }

  iterator insert(std::initializer_list<value_type>& il) {
    iterator result;
    for (value_type* i = il.begin(); i != il.end(); ++i) {
      result = this->insert(root_, *i);
    }
    return result;
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
      node->right = erase(node.i_->right, current.i_->value);
    }
    it_(size_, root_);
    begin_ = it_.iterators_order[0];
    end_ = it_.iterators_order[size_ - 1].left;
    rbegin_ = end_;
    rend_ = begin_;
    return node;
  }

  void clear() { ~bst(); }

  iterator find(const_iterator node) {
    return std::find(this->begin(), this->end(), node);
  }

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

  iterator lower_bound(const_iterator node) {
    if (node->right != nullptr) {
      return minimum(node->right);
    }
    iterator y = node->parent;
    while (y != nullptr && node == y->right) {
      node = y;
      y = y->parent;
    }
    return y;
  }

  iterator upper_bound(const_iterator node) {
    if (node->left != nullptr) {
      return maximum(node->right);
    }
    iterator y = node->parent;
    while (y != nullptr && node == y.left) {
      node = y;
      y = y.parent;
    }
    return y;
  }

  allocator_type get_allocator() { return allocator_; }
};

template <class T, class Traversal = InOrder, class Compare = std::less<T>,
          class Allocator = std::allocator<T> >
void swap(bst<T, Traversal>& lhs, bst<T, Traversal>& rhs) {
  lhs.swap(rhs);
}
