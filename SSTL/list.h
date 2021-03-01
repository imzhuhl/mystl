//
// Created by ZhuHonglin on 2021/3/1.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

namespace sstl{

    template <typename T>
    class list_iterator {
    public:
        typedef T           value_type;

    };

    template <typename T>
    class list_node {
    public:
        T               value_;
        list_node<T>*   next_;

    };

    template <typename T>
    class list {
    public:
        typedef list_iterator<T>       iterator;
    private:
        list_node<T>*     begin_;

    public:
        list();
        iterator begin() {return begin_->next_;}

    };

    template <typename T> list<T>::list() {
        begin_ = new list_node<T>();
    }

}


#endif //MYSTL_LIST_H
