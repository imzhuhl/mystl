//
// Created by ZhuHonglin on 2021/3/1.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

namespace sstl{

    template <class T> class list_node;

    template <class T>
    class list_iterator {
    public:
        typedef T           value_type;

        T* node_;

        list_iterator() = default;
        list_iterator(T* x): node_(x) {}
    };

    template <class T>
    class list_node {
    public:
        T               value_;
        list_node<T>*   next_;
        list_node() = default;
        list_node(const T& value): value_(value) {}
    };

    template <class T>
    class list {
    public:
        typedef T                       value_type;
        typedef list_iterator<T>        iterator;
    private:
        list_node<T>*     begin_;

    public:
        list();
        iterator begin() {return begin_->next_;}

        // 插入
        void push_back(const value_type& value);

    };

    template <class T> list<T>::list() {
        begin_ = new list_node<T>();
    }

    template <class T> void list<T>::push_back(const value_type &value) {
        list_node<T>* p = new list_node<T>(value);

    }

}


#endif //MYSTL_LIST_H
