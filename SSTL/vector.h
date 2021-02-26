//
// Created by zhuhonglin on 2021/2/26.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include <new>
#include <cstddef>
#include <algorithm>

#include "utils.h"

namespace sstl{

    template <typename T>
    class vector {
    private:
        T* begin_;
        T* end_;
        T* cap_;

        void init_space(size_t n, size_t cap);
        void fill_n(T* first, size_t n, T value);
        void destroy_and_recover(T* first, T* last, size_t n);

    public:
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

        vector& operator=(const vector& rhs);
        vector& operator=(vector&& rhs) noexcept;
        vector& operator=(std::initializer_list<T> ilist);

        // 迭代相关
        T* begin() noexcept {return begin_;}
        T* end() noexcept {return end_;}

        // 容量相关
        bool empty() const noexcept {
            return begin_ == end_;
        }
        size_t size() const noexcept {
            return static_cast<size_t>(end_ - begin_);
        }
        size_t capacity() const noexcept {
            return static_cast<size_t>(cap_ - begin_);
        }

        // 访问元素
        T operator[](size_t n) {
            assert(n < size());
            return *(begin_ + n);
        }
        T front() {
            assert(!empty());
            return *begin_;
        }
        T back() {
            assert(!empty());
            return *(end_-1);
        }

        // 插入删除
        void push_back(const T& value);
        void push_back(T&& value);
        void pop();


    };


    /******************************* helper func *******************************/
    template <typename T> void vector<T>::init_space(size_t n, size_t cap) {
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

    template <typename T> void vector<T>::fill_n(T *first, size_t n, T value) {
        for (; n > 0; --n, ++first) {
            *first = value;
        }
    }

    template <typename T> void vector<T>::destroy_and_recover(T* first, T* last, size_t n) {
        destory(first, last);
        if (first != nullptr) {
            ::operator delete(first);
        }
    }

}

#endif //MYSTL_VECTOR_H
