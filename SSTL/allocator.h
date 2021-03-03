//
// Created by zhuhonglin on 2021/3/3.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include <new>


namespace sstl {
    /********** construct and destroy function ************/
    template <class T>
    void construct(T* ptr) {
        ::new (ptr) T();
    }

    template <class T, class VT>
    void construct(T* ptr, const VT& value) {
        ::new (ptr) T(value);
    }

    template <class T>
    void destroy_one(T*, std::true_type) {}

    template <class T>
    void destroy_one(T* ptr, std::false_type) {
        if (ptr != nullptr) {
            ptr->~T();
        }
    }

    template <class T> void destroy_cat(T* first, T* last, std::true_type) {}

    template <class T> void destroy_cat(T* first, T* last, std::false_type) {
        for (; first != last; ++first) {
            destory(first);
        }
    }
    template <class T>
    void destroy(T* ptr) {
        destroy_one(ptr, std::is_trivially_destructible<T>{});
    }

    template <class T> void destroy(T* first, T* last) {
        destroy_cat(first, last, std::is_trivially_destructible<T>{});
    }

    /********** allocator ************/
    template<class T>
    class allocator {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        static T *allocate() {
            return static_cast<T *>(::operator new(sizeof(T)));
        }

        static T *allocate(size_type n) {
            if (n == 0) return nullptr;
            return static_cast<T *>(::operator new(n * sizeof(T)));
        }

        static void deallocate(T *ptr) {
            if (ptr == nullptr) return;
            ::operator delete(ptr);
        }

        static void deallocate(T *ptr, size_type n) {
            // TODO
        }

        static void construct(T *ptr) {
            sstl::construct(ptr);
        }

        static void construct(T *ptr, const T &value) {
            sstl::construct(ptr, value);
        }

        static void destroy(T *ptr) {
            sstl::destroy(ptr);
        }

    };
}



#endif //MYSTL_ALLOCATOR_H
