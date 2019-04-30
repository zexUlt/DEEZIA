//
// Created by zexult on 30.04.19.
//

#ifndef DEEZIA_CONTAINERTEST_H
#define DEEZIA_CONTAINERTEST_H


#include "GroupContainer.h"
#include "Set.h"
#include <ctime>

class ContainerTest {
private:
    Set *cont;
public:
    explicit ContainerTest(Set*);
    double testInsert(size_t);
    double testRemove(size_t);
    double printContainer();
};


#endif //DEEZIA_CONTAINERTEST_H
