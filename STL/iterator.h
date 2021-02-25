//
// Created by zhuhonglin on 2021/2/25.
//

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H

#include <cstddef>

namespace mystl {

template <class Category, class T, class Distance=ptrdiff_t, class Pointer=T*, class Reference=T&>
struct iterator {
    typedef Category        iterator_category;
    typedef T               value_type;
    typedef Pointer         pointer;
    typedef Reference       reference;
    typedef Distance        difference_type;
};



}



#endif //MYSTL_ITERATOR_H
