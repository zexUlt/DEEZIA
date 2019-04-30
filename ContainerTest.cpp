//
// Created by zexult on 30.04.19.
//

#include "ContainerTest.h"

ContainerTest::ContainerTest(Set* _container)
{
    cont = _container;
}

double ContainerTest::testInsert(size_t size)
{
    clock_t start = clock();
    for(int i = 0; i < size; i++)
    {
        this->cont->insert(&i, sizeof(int*));
    }
    clock_t finish = clock();

    return (double) (finish - start) / CLOCKS_PER_SEC;
}

double ContainerTest::testRemove(size_t size)
{
    clock_t start = clock();
    for(int i = 0; i < size; i++)
    {

    }
    clock_t finish = clock();

    return (double) (finish - start) / CLOCKS_PER_SEC;
}

double ContainerTest::printContainer()
{

}