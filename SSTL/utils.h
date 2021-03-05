//
// Created by ZhuHonglin on 2021/2/26.
//

#ifndef MYSTL_UTILS_H
#define MYSTL_UTILS_H

namespace sstl {

    ////// pair<> //////
    template <class T1, class T2>
    class pair {
    public:
        typedef T1      first_type;
        typedef T2      second_type;

        T1 first_;
        T2 second_;

        pair(): first_(T1()), second_(T2()) {}
        pair(const T1& a, const T2& b): first_(a), second_(b) {}

        template <class U1, class U2>
        pair(const pair<U1, U2>& p): first_(p.first_), second_(p.second_) {}

        //// 运算符重载 ////
        inline bool operator==(const pair& rhs) {
            return first_== rhs.first_ && second_ == rhs.second_;
        }

        inline bool operator<(const pair& rhs) {
            return first_ < rhs.first_ || (first_ == rhs.first_ && second_ < rhs.second_);
        }

    };

    template <class T1, class T2>
    inline pair<T1, T2> make_pair(const T1& a, const T2& b) {
        return pair<T1, T2>(a, b);
    }


    ////// 哈希函数 //////
    template <class Key>
    struct hash {};

    template <class Key>
    struct hash<Key*> {

    };

    // 整数返回原始值
#define HASH_FCN(Type)                              \
template <> struct hash<Type> {                     \
    size_t operator()(Type val) noexcept {          \
        return static_cast<size_t>(val);            \
    }                                               \
};

    HASH_FCN(short)
    HASH_FCN(int)
    HASH_FCN(unsigned int)
    HASH_FCN(long)
    HASH_FCN(unsigned long)
    HASH_FCN(long long)
    HASH_FCN(unsigned long long)
    HASH_FCN(bool)
    HASH_FCN(char)
    HASH_FCN(unsigned char)

    // 浮点数


    //////  //////
    template <class T>
    struct equal_to {
        bool operator()(const T& x, const T& y) {return x == y;}
    };

}

#endif //MYSTL_UTILS_H
