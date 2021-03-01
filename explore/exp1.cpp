//
// Created by ZhuHonglin on 2021/3/1.
//
#include <iostream>
using namespace std;

template <typename T>
class Foo {
public:
    typedef T   value_type;
    typedef T*  pointer;

    value_type a;
    pointer b;
};

template <typename I>
typename I::value_type func(I foo) {
    return foo.a;
}

int main() {
    Foo<double> f;
    cout << typeid(f.b).name() << endl;
    cout << func(f) << endl;
    return 0;
}