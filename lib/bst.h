#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

struct PreOrder {};
struct InOrder {};
struct PostOrder {};


template <typename T>
struct Node {
  T value;
  Node* left;
  Node* right;
  Node* parent;
  Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  Node(T& data) {
    value = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  bool operator==(const Node& other) {
    return (this->value == other.value) && (this->left == other.left) &&
           (this->right == other.right) && (this->parent == other.parent);
  }
  bool operator!=(const Node& other){
    return !(this == other);
  }
};

template <class T, class Traversal>
struct Iterator {};
template <class T>
class Iterator<T, InOrder> {
  typedef T value_type;
  typedef Node<value_type> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  std::vector<iterator> massive_;
  iterator begin_;
  iterator end_;
  iterator rbegin_;
  iterator rend_;
  iterator node_;
  size_t size_;
  size_t i_;

  void inorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    inorder(node->left, massive_);
    massive_.push_back(node->value);
    inorder(node->right, massive_);
  }

  Iterator(size_t size, iterator root) : size_{size} {
    inorder(root);
    i_ = 0;
    begin_ = massive_[0];
    end_ = massive_[size_ - 1];
  }
  iterator operator++() {
    if (i_ < size_) {
      return massive_[++i_];
    } else {
      return end_->left;
    }
  }
  iterator operator--() {
    if (i_ >= size_) {
      return massive_[--i_];
    } else {
      return begin_;
    }
  }
  iterator operator++(int) {
    if (i_ >= size_) {
      return end_->left;
    }
    iterator copy_iteartor = massive_[i_];
    if (i_ < size_) {
      ++i_;
    }
    return copy_iteartor;
  }
  iterator operator--(int) {
    if (i_ < 0) {
      return nullptr;
    }
    iterator copy_iteartor = massive_[i_];
    if (i_ >= size_) {
      --i_;
    }
    return copy_iteartor;
  }
  reference operator*() { return &massive_[i_]; }
  bool operator==(const_reference other){
    return (*this == *other);
  }
  bool operator != (const_reference other){
    return !(this == other);
  }
};
template <typename T>
struct Iterator<T, PostOrder> {
  typedef T value_type;
  typedef Node<value_type> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  std::vector<iterator> massive_;
  iterator begin_;
  iterator end_;
  iterator rbegin_;
  iterator rend_;
  size_type size_;
  size_type i_;

  void postorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    postorder(node->left, massive_);
    postorder(node->right, massive_);
    massive_.push_back(node->data);
  }

  Iterator(size_t size, iterator root) : size_{size} {
    postorder(root);
    i_ = 0;
    begin_ = massive_[0];
    end_ = massive_[size_ - 1];
  }
  iterator operator++() {
    if (i_ < size_) {
      return massive_[++i_];
    } else {
      return end_->left;
    }
  }
  iterator operator--() {
    if (i_ >= size_) {
      return massive_[--i_];
    } else {
      return begin_;
    }
  }
  iterator operator++(int) {
    if (i_ >= size_) {
      return end_->left;
    }
    iterator copy_iteartor = massive_[i_];
    if (i_ < size_) {
      ++i_;
    }
    return copy_iteartor;
  }
  iterator operator--(int) {
    if (i_ < 0) {
      return nullptr;
    }
    iterator copy_iteartor = massive_[i_];
    if (i_ >= size_) {
      --i_;
    }
    return copy_iteartor;
  }
  reference operator*() { return &massive_[i_]; }
    bool operator==(const_reference other){
    return (*this == *other);
  }
  bool operator != (const_reference other){
    return !(this == other);
  }
};

template <class T>
struct Iterator<T, PreOrder> {
  typedef T value_type;
  typedef Node<value_type> node_type;
  typedef node_type& reference;
  typedef const node_type& const_reference;
  typedef node_type* iterator;
  typedef const node_type* const_iterator;
  typedef size_t size_type;

  std::vector<iterator> massive_;
  iterator begin_;
  iterator end_;
  iterator rbegin_;
  iterator rend_;
  size_type size_;
  size_type i_;

  void preorder(iterator node) {
    if (node == nullptr) {
      return;
    }
    massive_.push_back(node->data);
    preorder(node->left, massive_);
    preorder(node->right, massive_);
  }

  Iterator(size_t size, iterator root) : size_{size} {
    preorder(root);
    i_ = 0;
    begin_ = massive_[0];
    end_ = massive_[size_ - 1];
  }
  iterator operator++() {
    if (i_ < size_) {
      return massive_[++i_];
    } else {
      return end_->left;
    }
  }
  iterator operator--() {
    if (i_ >= size_) {
      return massive_[--i_];
    } else {
      return begin_;
    }
  }
  iterator operator++(int) {
    if (i_ >= size_) {
      return end_->left;
    }
    iterator copy_iteartor = massive_[i_];
    if (i_ < size_) {
      ++i_;
    }
    return copy_iteartor;
  }
  iterator operator--(int) {
    if (i_ < 0) {
      return nullptr;
    }
    iterator copy_iteartor = massive_[i_];
    if (i_ >= size_) {
      --i_;
    }
    return copy_iteartor;
  }
  reference operator*() { return &massive_[i_]; }
    bool operator==(const_reference other){
    return (*this == *other);
  }
  bool operator != (const_reference other){
    return !(this == other);
  }
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

  void preorder(iterator node, std::vector<iterator>& massive) {
    if (node == nullptr) {
      return;
    }
    massive.push_back(node->data);
    preorder(node->left, massive);
    preorder(node->right, massive);
  }
  void postorder(iterator node, std::vector<iterator>& massive) {
    if (node == nullptr) {
      return;
    }
    if (node == nullptr) {
      return;
    }
    postorder(node->left, massive);
    postorder(node->right, massive);
    massive.push_back(node->data);
  }

 public:
  bst() : root_{nullptr}, size_{0}, max_size_{15352} , it_{nullptr} {}
  bst(const bst& other) : size_{this->size_}, max_size_{this->max_size_} {
    other = allocator_.allocate(1);
    allocator_.construct(other);
    std::vector<iterator> massive;
    size_t i = 0;
    preorder(this->root_, massive);
    while (i < size_) {
      other.insert(other.root_, massive[++i]);
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
    std::vector<iterator> massive;
    size_t i = 0;
    preorder(other->root_, massive);
    while (i < size_) {
      new_bst.insert(new_bst.root_, massive[++i]);
    }
    return &new_bst;
  }
  ~bst() {
    std::vector<iterator> massive;
    postorder(root_, massive);
    for (size_type i = 0; i < size_; ++i) {
      erase(root_, massive[i]);
    }
    root_ = nullptr;
    size_ = 0;
    max_size_ = 15352;
    it_ = nullptr;
  }
  // Container Requirements
  iterator begin() { return it_.begin_; }
  iterator end() { return it_.end_; }
  const_iterator begin() const { return it_.begin_; }
  const_iterator end() const { return it_.end_; }
  bool operator==(const bst& other) const {
    return std::equal(this.begin(), this.end(), other.begin(), other.end());
  }
  bool operator!=(const bst& other) const { return !(this == other); }
  void swap(bst& other) {
    std::swap(this->root_, other->root_);
  }  // тута надо подумать
  size_type size() const { return size_; }
  size_type max_size() const { return max_size_; }
  bool empty() const { return size_ == 0; }
  // BidirectionalIterator
  reference operator++() const { return ++it_; }
  reference operator++(int) const { return it_++; }
  reference operator--() const { return --it_; }
  reference operator--(int) const { return it_--; }
  reference operator*() { return *it_; }
  // ReversibleContainer
  iterator rbegin() const { return it_.rbegin_; }
  iterator rend() const { return it_.rend_; }
  // AssociativeContainer

  iterator insert(const_iterator node, const value_type& x,
                  Compare comparator) {
    if (node.i_ == nullptr) {
      ++size_;
      node = allocator_.allocate(1);
      allocator_.construct(node, x);
      return node;
    }
    if (comparator(x, node.i_->value)) {
      node.i_->left = insert(node.i_->left, x);
      node.i_->left->parent = node.i_;
    } else {
      node.i_->right = insert(node.i_->right, x);
      node.i_->right->parent = node.i_;
    }
    it_(size_ , root_);
    return node;
  }
  iterator insert(iterator i , iterator j){
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
    if (node.i_ == nullptr) {
      return node;
    }
    if (Compare()(x, node.i_->value)) {
      node.i_->left = erase(node.i_->left, x);
    } else if (Compare()(node.i_->value, x)) {
      node.i_->right = erase(node.i_->right, x);
    } else {
      if (node.i_->left == nullptr) {
        iterator current = node.i_->right;
        current.i_->parent = node.i_->parent;
        --size_;
        allocator_.destroy(node);
        node = allocator_.deallocate(1);
        return current;
      } else if (node.i_->right == nullptr) {
        iterator current = node.i_->left;
        current.i_->parent = node.i_->parent;
        allocator_.destroy(node);
        node = allocator_.deallocate(1);
        --size_;
        return current;
      }
      iterator current = minimum(node.i_->right);
      node.i_->value = current.i_->value;
      node.i_->right = erase(node.i_->right, current.i_->value);
    }
    it_(size_ , root_);
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
    if(node.i_.right != nullptr){
      return minimum(node.i_.right);
    }
    iterator y = node.i_.parent;
    while (y != nullptr && node.i_ == y.i_.right) {
      node = y;
      y = y.i_.parent;
    }
    return y;
  }
  iterator upper_bound(const_iterator node) { 
    if(node.i_.left != nullptr){
      return maximum(node.i_.right);
    }
    iterator y = node.i_.parent;
    while (y != nullptr && node.i_ == y.i_.left) {
      node = y;
      y = y.i_.parent;
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
