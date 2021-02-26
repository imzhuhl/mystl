//
// Created by zhuhonglin on 2021/2/25.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include <cstddef>

#include "construct.h"

namespace mystl{

template <class T>
class allocator {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

    static T* allocate();
    static T* allocate(size_type n);
    static void deallocate(T* ptr);
    static void deallocate(T* ptr, size_type n);
    static void construct(T* ptr);
    static void construct(T* ptr, const T& value);
    static void construct(T* ptr, T&& value);
};

template <class T> T* allocator<T>::allocate() {
    return static_cast<T*>(::operator new(sizeof(T)));  // :: 全局作用域中的 operator new
}

template <class T> T* allocator<T>::allocate(size_type n) {
    if (n==0)
        return nullptr;
    return static_cast<T*>(::operator new(n*sizeof(T)));
}

template <class T> void allocator<T>::deallocate(T* ptr) {
    if (ptr == nullptr)
        return;
    ::operator delete(ptr);
}

template <class T> void allocator<T>::deallocate(T* ptr, size_type n){
    if (ptr == nullptr)
        return;
    ::operator delete(ptr);
}

template <class T> void allocator<T>::construct(T* ptr) {
    mystl::construct(ptr);
}




}


#endif //MYSTL_ALLOCATOR_H
