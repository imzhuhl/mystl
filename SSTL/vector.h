//
// Created by zhuhonglin on 2021/2/26.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include <new>
#include <cstddef>
#include <algorithm>

#include "allocator.h"

namespace sstl{

    template <typename T>
    class vector {
    public:
        typedef T                                       value_type;
        typedef T*                                      pointer;
        typedef const T*                                const_pointer;
        typedef T&                                      reference;
        typedef const T&                                const_reference;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef T*                                      iterator;
    private:
        iterator begin_;
        iterator end_;
        iterator cap_;

    public:
        // 构造、复制、移动、析构函数
        vector() noexcept {
            init_space(0, 16);
        }
        explicit vector(size_t n) {
            vector(n, 0);
        }
        vector(size_t n, T value) {
            const size_t init_size = std::max(static_cast<size_t>(16), n);
            init_space(n, init_size);
            fill_n(begin_, n, value);
        }
        ~vector() {
            destroy_and_recover(begin_, end_, cap_ - begin_);
            begin_ = end_ = cap_ = nullptr;
        }

        // 迭代相关
        iterator begin() noexcept {return begin_;}
        iterator end() noexcept {return end_;}

        // 容量相关
        bool empty() const noexcept {
            return begin_ == end_;
        }
        size_type size() const noexcept {
            return static_cast<size_type>(end_ - begin_);
        }
        size_type capacity() const noexcept {
            return static_cast<size_type>(cap_ - begin_);
        }

        // 访问元素
        reference operator[](size_type n) {
            assert(n < size());
            return *(begin_ + n);
        }
        reference front() {
            assert(!empty());
            return *begin_;
        }
        reference back() {
            assert(!empty());
            return *(end_-1);
        }

        // 插入删除
        void push_back(const T& value) {

        }
        void pop();

        /*********helper function*********/
        void init_space(size_type n, size_type cap) {
            try {
                begin_ = static_cast<T*>(::operator new(cap*sizeof(T)));
                end_ = begin_ + n;
                cap_ = begin_ + cap;
            } catch (...) {
                begin_ = nullptr;
                end_ = nullptr;
                cap_ = nullptr;
            }
        }
        void fill_n(T* first, size_t n, T value) {
            for (; n > 0; --n, ++first) {
                *first = value;
            }
        }
        void destroy_and_recover(T* first, T* last, size_t n) {
            sstl::destroy(first, last);
            if (first != nullptr) {
                ::operator delete(first);
            }
        }


    };

}

#endif //MYSTL_VECTOR_H
