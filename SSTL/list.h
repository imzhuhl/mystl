//
// Created by ZhuHonglin on 2021/3/1.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

#include <cassert>
#include "allocator.h"

namespace sstl{

    template <class T> class list_node;

    template <class T>
    struct node_traits {
        typedef list_node<T>* node_ptr;
    };

    template <class T>
    class list_iterator {
    public:
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef typename node_traits<T>::node_ptr   node_ptr;
        typedef list_iterator<T>                    self;

        node_ptr node_;

        list_iterator() = default;
        list_iterator(node_ptr x): node_(x) {}
        list_iterator(const list_iterator& rhs): node_(rhs.node_) {}

        reference operator*() const { return node_->value_; }
        pointer operator->() const { return &(operator*()); }

        // ++ --
        self& operator++() {  // 前缀++（++a)
            assert(node_ != nullptr);
            node_ = node_->next_;
            return *this;
        }
        self operator++(int) {  // 后缀 a++
            list_iterator<T> tmp = *this;
            ++(*this);
            return tmp;
        }
        self& operator--() {
            assert(node_ != nullptr);
            node_ = node_->prev_;
            return *this;
        }
        self operator--(int) {  // 后缀 a++
            list_iterator<T> tmp = *this;
            --(*this);
            return tmp;
        }

        // == !=
        bool operator==(const self& rhs) const {return node_ == rhs.node_;}
        bool operator!=(const self& rhs) const {return node_ != rhs.node_;}

    };

    template <class T>
    class list_const_iterator {
    public:
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef typename node_traits<T>::node_ptr   node_ptr;
        typedef list_iterator<T>                    self;

        node_ptr node_;

        list_const_iterator() = default;
        explicit list_const_iterator(node_ptr x): node_(x) {}
        explicit list_const_iterator(const list_iterator<T>& rhs): node_(rhs.node_) {}
        list_const_iterator(const list_const_iterator& rhs): node_(rhs.node_) {}
        reference operator*() const { return node_->value_; }
        pointer operator->() const { return &(operator*()); }

        // ++ --
        self& operator++() {  // 前缀++（++a)
            assert(node_ != nullptr);
            node_ = node_->next_;
            return *this;
        }
        self operator++(int) {  // 后缀 a++
            list_iterator<T> tmp = *this;
            ++(*this);
            return tmp;
        }
        self& operator--() {
            assert(node_ != nullptr);
            node_ = node_->prev_;
            return *this;
        }
        self operator--(int) {  // 后缀 a++
            list_iterator<T> tmp = *this;
            --(*this);
            return tmp;
        }

        // == !=
        bool operator==(const self& rhs) const {return node_ == rhs.node_;}
        bool operator!=(const self& rhs) const {return node_ != rhs.node_;}
    };

    template <class T>
    class list_node {
    public:
        typedef typename node_traits<T>::node_ptr node_ptr;
        T           value_;
        node_ptr    next_;
        node_ptr    prev_;

        list_node(): value_(), next_(this), prev_(this) {}
        explicit list_node(const T& value): value_(value), next_(this), prev_(this) {}

    };

    template <class T>
    class list {
    public:
//        typedef sstl::allocator<T>                      allocator_type;
//        typedef sstl::allocator<T>                      data_allocator;
//        typedef sstl::allocator<list_node<T>>           node_allocator;

        typedef T                                       value_type;
        typedef T*                                      pointer;
        typedef const T*                                const_pointer;
        typedef T&                                      reference;
        typedef const T&                                const_reference;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef list_iterator<T>                        iterator;
        typedef list_const_iterator<T>                  const_iterator;
        typedef typename node_traits<T>::node_ptr       node_ptr;

    private:
        node_ptr    begin_;  // 头节点
        size_type   size_;

    public:
        list() {
            fill_init(0, value_type());
        }
        explicit list(size_type n) {
            fill_init(n, value_type());
        }
        list(size_type n, const T& value)
        {
            fill_init(n, value);
        }
        list(const list& rhs) {

        }

        iterator begin() {return begin_->next_;}
//        const_iterator begin() const {return begin_->next_;}

        iterator end() {return begin_;}
        const_iterator cbegin() const {return begin();}
        const_iterator cend() const {return end();}
        bool empty() const { return begin_->next_ == begin_;}
        size_type size() const {return size_;}

        // 访问元素
        reference front() {
            assert(!empty());
            return *begin();
        }
        reference back() {
            assert(!empty());
            return *(--end());
        }

        // 插入删除
        void push_front(const value_type& value) {
            node_ptr p = new list_node<T>(value);
            link_nodes_at_front(p);
            ++size_;
        }
        void push_back(const value_type& value) {
            node_ptr p = new list_node<T>(value);
            link_nodes_at_back(p);
            ++size_;
        }
        void pop_front() {
            assert(!empty());
            node_ptr p = begin_->next_;
            unlink_node(p);
            delete p;
        }
        void pop_back() {
            assert(!empty());
            node_ptr p = begin_->prev_;
            unlink_node(p);
            delete p;
        }

        /*********helper function*********/
        void fill_init(size_type n, const value_type& value) {
            begin_ = new list_node<T>();
            size_ = n;
            for (; n > 0; --n) {
                node_ptr p = new list_node<T>(value);
                link_nodes_at_back(p);
            }
        }

        void copy_init() {

        }

        void unlink_node(node_ptr ptr) {
            ptr->prev_->next_ = ptr->next_;
            ptr->next_->prev_ = ptr->prev_;
        }

        void link_nodes_at_front(node_ptr ptr) {
            node_ptr first = begin_->next_;
            ptr->next_ = first;
            first->prev_ = ptr;
            begin_->next_ = ptr;
            ptr->prev_ = begin_;
        }

        void link_nodes_at_back(node_ptr ptr) {
            node_ptr last = begin_->prev_;
            ptr->prev_ = last;
            last->next_ = ptr;
            begin_->prev_ = ptr;
            ptr->next_ = begin_;
        }
    };

}


#endif //MYSTL_LIST_H
