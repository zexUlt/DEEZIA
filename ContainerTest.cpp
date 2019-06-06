//
// Created by zexult on 30.04.19.
//

#include "ContainerTest.h"
#include "RBTree.h"
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <typeinfo>

ContainerTest::ContainerTest(Set* _container)
{
    cont = _container;
}

char* ContainerTest::rand_string(size_t len)
{
    char* rand_str = new char[len];

    const char ch_set[] = {'A','B','C','D','E','F',
                          'G','H','I','J','K',
                          'L','M','N','O','P',
                          'Q','R','S','T','U',
                          'V','W','X','Y','Z',
                          'a','b','c','d','e','f',
                          'g','h','i','j','k',
                          'l','m','n','o','p',
                          'q','r','s','t','u',
                          'v','w','x','y','z'
                         };

    std::default_random_engine rng(std::random_device{}());

    std::uniform_int_distribution<> dist(0, (int)strlen(ch_set)-1);

    auto rand_char = [ch_set, &dist, &rng](){return ch_set[ dist(rng) ]; };

    generate_n(rand_str, len, rand_char);

    return rand_str;
}

double ContainerTest::testInsert(size_t size, int flag)
{
    clock_t time(0), start, finish;
    switch (flag)
    {
        case CT_NORMAL:
            start = clock();
            for(int i = 0; i < size; i++)
            {
                this->cont->insert(&i, sizeof(i));
                this->cont->name = typeid(i).name();
            }
            finish = clock();
            time = finish - start;
            break;

        case CT_EQUAL:
            start = clock();
            for(int i = 0; i < size; i++)
                for(int j = 0; j < sqrt(size)/2; j++)
                {
                    this->cont->insert(&i, sizeof(i));
                    this->cont->name = typeid(i).name();
                }
            finish = clock();
            time = finish - start;
            break;

        case CT_STRINT:
            start = clock();
            for(int i = 0; i < size; i++)
            {
                if (i % 2) {
                    char* str = rand_string((size_t) i);
                    this->cont->name = typeid(str).name();
                    this->cont->insert(str, (size_t) i);
                } else {
                    this->cont->name = typeid(i).name();
                    this->cont->insert(&i, sizeof(i));
                }
            }
            finish = clock();
            time = finish - start;
            break;

        case CT_CHRINT:
            start = clock();
            for(int i = 0; i < size; i++)
            {
                if (i % 2) {
                    char* ch = rand_string(1);
                    this->cont->name = typeid(ch).name();
                    this->cont->insert(ch, sizeof(ch));
                } else {
                    this->cont->name = typeid(i).name();
                    this->cont->insert(&i, sizeof(i));
                }
            }
            finish = clock();
            time = finish - start;
            break;
    }

    return (double) time / CLOCKS_PER_SEC;
}

double ContainerTest::testRemove(size_t n)
{
    double time;
    Container::Iterator *it = cont->newIterator();

    if (n >= this->cont->size())
        time = testClear();
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

double ContainerTest::testClear()
{
    clock_t start = clock();

    this->cont->clear();

    clock_t finish = clock();

    return (double) (finish - start) / CLOCKS_PER_SEC;
}

void ContainerTest::printContainer()
{
    Container::Iterator* it = cont->newIterator();
    auto s_it = (RBTree::SetIterator*) it;
    size_t size;

    for(it = this->cont->begin(); !it->equals(this->cont->end()); it->goToNext())
    {
        s_it = (RBTree::SetIterator*)it;
        if(s_it->current->name == "i") {
            int elem = *(int *) it->getElement(size);
            printf("%20d | size (bytes) = %lu\n", elem, size);
        }
       if(s_it->current->name == "Pc"){
           char* elem = (char*)it->getElement(size);
           printf("%20s | size (bytes) = %lu\n", elem, size);
       }

    }
    cout << endl;
}