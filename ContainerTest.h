//
// Created by zexult on 30.04.19.
//

#ifndef DEEZIA_CONTAINERTEST_H
#define DEEZIA_CONTAINERTEST_H

#include "GroupContainer.h"
#include "Set.h"
#include <ctime>

#define CT_NORMAL 1
#define CT_EQUAL 2
#define CT_STRINT 3
#define CT_CHRINT 4


class ContainerTest {
private:
    Set *cont;

    char* rand_string(size_t);

public:
    explicit ContainerTest(Set *);

    double testClear(); // is working
    double testInsert(size_t, int); // is working
    double testRemove(size_t); // need fix
    void printContainer(); // is working
};


#endif //DEEZIA_CONTAINERTEST_H
