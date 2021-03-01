//
// Created by ZhuHonglin on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Foo {
public:
    int a_;
    int b_;
    bool c_;
    Foo(int a, int b, bool c): a_(a), b_(b), c_(c) {}
};

int main() {
    vector<int> v1 {1, 2, 3, 4};
    vector<Foo> v2;
    vector<Foo*> v3;
    list<Foo*> v4;
    v2.emplace_back(1, 1, true);
    v2.emplace_back(2, 2, true);
    v3.push_back(new Foo(1, 1, true));
    v3.push_back(new Foo(2, 2, true));
    v4.push_back(new Foo(1, 1, true));
    v4.push_back(new Foo(2, 2, true));

    vector<Foo*>::iterator v3iter = v3.begin();
    list<Foo*>::iterator v4iter = v4.begin();

    cout << (*v3iter)->a_ << endl;
    ++v3iter;
    cout << (*v3iter)->a_ << endl;

    cout << (*v4iter)->a_ << endl;
    ++v4iter;
    cout << (*v4iter)->a_ << endl;


    return 0;
}