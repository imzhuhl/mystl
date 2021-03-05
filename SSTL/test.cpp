//
// Created by zhuhonglin on 2021/2/26.
//
#include <iostream>
#include "vector.h"
#include "list.h"
#include "hashtable.h"

void test_vector() {
    sstl::vector<int> v1;
    sstl::vector<int> v2(10, 1);
    std::cout << v2.size() << std::endl;

    sstl::vector<int*> v3;
}

void test_list() {
    sstl::list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    sstl::list<int>::iterator l1iter =  l1.begin();
    for (; l1iter != l1.end(); ++l1iter) {
        std::cout << *l1iter << std::endl;
    }
}

int main() {
    test_list();

    return 0;
}

