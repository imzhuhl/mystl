//
// Created by zhuhonglin on 2021/2/26.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include <new>
#include <cstddef>
#include <algorithm>

namespace sstl{

class vector {
private:
    int *begin_;
    int *end_;
    int *cap_;

    void init_space(size_t cap);
    void fill_n(int* first, size_t n, int value);

public:
    vector() noexcept;
    explicit vector(size_t n);
    vector(size_t n, int value);
    ~vector();

    vector& operator=(const vector& rhs);
    vector& operator=(vector&& rhs) noexcept;
    vector& operator=(std::initializer_list<int> ilist);

    // 迭代相关
    int* begin() noexcept {return begin_;}
    int* end() noexcept {return end_;}

    // 容量相关
    bool empty() const noexcept {
        return begin_ == end_;
    }

};

vector::vector() noexcept {
    init_space(16);
}

vector::vector(size_t n) {
    vector(n, 0);
}

vector::vector(size_t n, int value) {
    const size_t init_size = std::max(static_cast<size_t>(16), n);
    init_space(init_size);
    fill_n(begin_, n, value);
}


/******************************* helper func *******************************/
void vector::init_space(size_t cap) {
    try {
        begin_ = static_cast<int*>(::operator new(cap*sizeof(int)));
        end_ = begin_;
        cap_ = begin_ + cap;
    } catch (...) {
        begin_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }
}


void vector::fill_n(int *first, size_t n, int value) {
    for (; n > 0; --n, ++first) {
        *first = value;
    }
}


}

#endif //MYSTL_VECTOR_H
