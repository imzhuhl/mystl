//
// Created by zhuhonglin on 2021/2/26.
//

#ifndef MYSTL_CONSTRUCT_H
#define MYSTL_CONSTRUCT_H

namespace mystl {

template <class Ty>
void construct(Ty* ptr) {
    ::new ((void*)ptr) Ty();
}



}

#endif //MYSTL_CONSTRUCT_H
