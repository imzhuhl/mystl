//
// Created by zhuhonglin on 2021/2/25.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include <cstddef>

namespace mystl{

template <class T>
class allocator {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

    static T* allocate();
    static T* allocate(size_type n);
};

template <class T>
T* allocator<T>::allocate() {
    return static_cast<T*>(::operator new(sizeof(T)));  // :: 全局作用域中的 operator new
}


}


#endif //MYSTL_ALLOCATOR_H
