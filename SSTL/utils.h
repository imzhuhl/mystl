//
// Created by ZhuHonglin on 2021/2/26.
//

#ifndef MYSTL_UTILS_H
#define MYSTL_UTILS_H

namespace sstl {

    // 获取对象地址
    template <class Tp>
    constexpr Tp* address_of(Tp& value) noexcept {
        return &value;
    }

}

#endif //MYSTL_UTILS_H
