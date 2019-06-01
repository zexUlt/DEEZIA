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
    double testFullremove(); // is working
    double testInsert(size_t); // is working
    double testRemove(size_t); // need fix
    void printContainer(); // is working
};


#endif //DEEZIA_CONTAINERTEST_H
