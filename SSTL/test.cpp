//
// Created by zhuhonglin on 2021/2/26.
//
#include <iostream>
#include "vector.h"
#include "list.h"

int main() {
    /********vector*********/
    sstl::vector<int> v1;
    sstl::vector<int> v2(10, 1);
    std::cout << v2.size() << std::endl;

    sstl::vector<int*> v3;

    /********list*********/

    sstl::list<int> l1;
    sstl::list<int>::iterator l1iter =  l1.begin();

    return 0;
}

