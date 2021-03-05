//
// Created by zhuhonglin on 2021/3/5.
//

#ifndef MYSTL_HASH_MAP_H
#define MYSTL_HASH_MAP_H

#include "utils.h"
#include "hashtable.h"

namespace sstl {

    // Key: 键的类型, T: 值的类型, Hash: 哈希函数, KeyEqual: 键的比较方式
    template <class Key, class T, class Hash=hash<Key>, class KeyEqual=equal_to<Key>>
    class hash_map {
    public:
        typedef hashtable<pair<Key, T>, Hash, KeyEqual> base_type;

    private:
        base_type ht_;

    public:
        hash_map(): ht_(100, Hash(), KeyEqual()) {}

    };

};

#endif //MYSTL_HASH_MAP_H
