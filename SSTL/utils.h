//
// Created by ZhuHonglin on 2021/2/26.
//

#ifndef MYSTL_UTILS_H
#define MYSTL_UTILS_H

namespace sstl {

    // 获取对象地址
    template <class T>
    constexpr T* address_of(T& value) noexcept {
        return &value;
    }


}

#endif //MYSTL_UTILS_H
