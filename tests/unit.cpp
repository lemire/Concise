#include <iostream>
#include <cassert>

#include "concise.h"

template <bool ewahmode>
void basictest() {
    ConciseSet<ewahmode> test1;
    test1.add(1);
    assert(test1.contains(1));
    test1.add(2);
    assert(test1.contains(2));
    test1.add(3);
    assert(test1.contains(3));
    test1.add(100);
    assert(test1.contains(100));
    test1.add(1000);
    assert(test1.contains(1000));
    assert(test1.size() == 5);
    ConciseSet<ewahmode> test2;
    test2.add(0);
    assert(test2.contains(0));
    test2.add(2);
    assert(test2.contains(2));
    test2.add(3);
    assert(test2.contains(3));
    test2.add(100);
    assert(test2.contains(100));
    test2.add(3000);
    assert(test2.contains(3000));
    assert(test2.size() == 5);
    ConciseSet<ewahmode> tmp;
    tmp = test1.logicalor(test2);
    assert(tmp.size() == 7);
    tmp = test1.logicaland(test2);
    assert(tmp.size() == 3);
    tmp.add(100000);
    assert(tmp.size() == 4);
    tmp.shrink_to_fit();
 }

int main() {
    basictest<true>();
    basictest<false>();
    std::cout <<"code might be ok" << std::endl;


}
