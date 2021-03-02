//
// Created by ZhuHonglin on 2021/3/2.
//

#include <iostream>
using namespace std;

template <class T>
struct iter_traits {
    typedef typename T::value_type value_type;
};

template <class T>
struct iter_traits<T*> {
    typedef T value_type;
};

template <class T>
struct MyIter {
    typedef T value_type;
    T* ptr;

    MyIter(T* p=0) : ptr(p) {}
    T& operator*() const { return *ptr; }
};

template <class I>
typename iter_traits<I>::value_type func(I ite) { return *ite; }

int main() {
    MyIter<int> ite(new int(8));
    cout << func(ite) << endl;
    int* p1 = new int(9);
    cout << func(p1) << endl;
    return 0;
}