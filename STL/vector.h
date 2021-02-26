//
// Created by zhuhonglin on 2021/2/25.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "iterator.h"
#include "memory.h"

namespace mystl {

template<class T>
class vector {
public:
    typedef mystl::allocator<T>         allocator_type;
    typedef mystl::allocator<T>         data_allocator;

    typedef typename allocator_type::value_type         value_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;

    typedef value_type*                 iterator;
    typedef const value_type*           const_iterator;

private:
    iterator begin_;    // 使用空间头部
    iterator end_;      // 使用空间尾部
    iterator cap_;      // 存储空间尾部

    void try_init() noexcept;
    void init_space(size_type size, size_type cap);
    void fill_init(size_type n, const value_type& value);

public:
    vector() noexcept {
        try_init();
    };

    explicit vector(size_type n) {

    }


};


/*****************************************************************************************/
// helper function
template <class T> void vector<T>::try_init() noexcept {
    try {
        begin_ = data_allocator::allocate(16);
        end_ = begin_;
        cap_ = begin_ + 16;
    } catch (...) {
        begin_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }
}


}

#endif //MYSTL_VECTOR_H
