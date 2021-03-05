//
// Created by zhuhonglin on 2021/2/26.
//
#include <iostream>
#include "vector.h"
#include "list.h"
#include "hashtable.h"
#include "hash_map.h"

void test_vector() {
    sstl::vector<int> v1;
    sstl::vector<int> v2(16, 1);
    v2.push_back(212);
    auto iter = v2.begin();
    for (; iter != v2.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
    std::cout << v2.size() << std::endl;

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

void test_hashmap() {

}

int main() {
//    test_list();
    test_vector();
    return 0;
}

