//
// Created by ZhuHonglin on 2021/2/26.
//

#ifndef MYSTL_UTILS_H
#define MYSTL_UTILS_H

namespace sstl {

    template <class T> void destory_cat(T* first, T* last, std::true_type) {}

    template <class T> void destory_cat(T* first, T* last, std::false_type) {
        for (; first != last; ++first) {
            destory(first);
        }
    }

    template <class T> void destory_one(T* ptr, std::true_type) {}

    template <class T> void destory_one(T* ptr, std::false_type) {
        if (ptr != nullptr) {
            ptr->~T();
        }
    }

    template <class T> void destory(T* ptr) {
        destory_one(ptr, std::is_trivially_destructible<T>{});
    }

    template <class T> void destory(T* first, T* last) {
        destory_cat(first, last, std::is_trivially_destructible<T>{});
    }



}

#endif //MYSTL_UTILS_H
