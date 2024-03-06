#include "bst.h"
typedef size_t size_type;

template <class T,class Tresval, class Compare, class Allocator>
bst<T,Tresval,  Compare, Allocator>::bst() : root{nullptr} {}

template <class T,class Tresval, class Compare, class Allocator>
bst<T,  Tresval ,Compare, Allocator>::bst(const bst& other) : root{other.root} {}

template <class T,class Tresval, class Compare, class Allocator>
bst<T,Tresval, Compare, Allocator>::~bst() {}

template <class T, class Tresval, class Compare, class Allocator>
size_type bst<T, Tresval, Compare, Allocator>::size() const {
  return size_type();
}

template <class T, class Tresval, class Compare, class Allocator>
inline size_type bst<T, Tresval, Compare, Allocator>::max_size() const {
  return size_type();
}

template <class T, class Tresval, class Compare, class Allocator>
bool bst<T, Tresval, Compare, Allocator>::empty() const {
  return false;
}

template<class T,class Tresval, class Compare, class Allocator>
void swap(bst<T, Tresval>& lhs, bst<T, Tresval>& rhs){
    lhs.swap(rhs);
}