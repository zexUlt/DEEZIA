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
        this->cont->insert(&i, sizeof(i));
    }
    clock_t finish = clock();

    return (double) (finish - start) / CLOCKS_PER_SEC;
}

double ContainerTest::testRemove(size_t n)
{
    double time;
    Container::Iterator *it = cont->newIterator();

    if (n >= this->cont->size())
        time = testFullremove();
    else {
        clock_t start = clock();

        size_t i = 0;
        it = cont->begin();
        while (i < n || !it->equals(cont->end())) {
            it = cont->begin();
            printContainer();
            this->cont->remove(it);
            i++;
        }

        clock_t finish = clock();

        time = (double) (finish - start) / CLOCKS_PER_SEC;
    }

    return time;
}

double ContainerTest::testFullremove()
{
    clock_t start = clock();

    this->cont->clear();

    clock_t finish = clock();

    return (double) (finish - start) / CLOCKS_PER_SEC;
}

void ContainerTest::printContainer()
{
    Container::Iterator* it = cont->newIterator();
    size_t size;

    for(it = cont->begin(); !it->equals(cont->end()); it->goToNext())
    {
        cout << *(int*)it->getElement(size) << " ";
    }
    cout << endl;
}