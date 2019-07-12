//
// Created by zexult on 30.04.19.
//

#include "ContainerTest.h"
#include "RBTree.h"
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <typeinfo>

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
                auto __data = new data(&i, typeid(i).name(), sizeof(i));

                this->list.push_front(&__data, sizeof(data));
//                this->list.push_front(&i, sizeof(i));

                this->cont->insert(&__data, sizeof(data));
//                this->cont->insert(&i, sizeof(i));

            }
            finish = clock();
            time = finish - start;
            break;

        case CT_EQUAL:
            start = clock();
            for(int i = 0; i < size; i++)
                for(int j = 0; j < sqrt(size)/2; j++)
                {
                    auto __data = new data(&i, typeid(i).name(), sizeof(i));
                    this->cont->insert(&__data, sizeof(__data));
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
                    auto __data = new data(&str, typeid(str).name(), sizeof(str));

                    this->list.push_front(&__data, sizeof(data));
//                    this->list.push_front(&str, sizeof(str));

                    this->cont->insert(&__data, sizeof(data));
//                    this->cont->insert(&str, sizeof(str));
                } else {
                    auto __data = new data(&i, typeid(i).name(), sizeof(i));

                    this->list.push_front(__data, sizeof(data));

                    this->cont->insert(&__data, sizeof(data));
//                    this->cont->insert(&i, sizeof(i));
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
                    auto __data = new data(&ch, typeid(ch).name(), sizeof(ch));

                    this->list.push_front(&__data, sizeof(__data));
//                    this->list.push_front(&ch, sizeof(ch));

                    this->cont->insert(&__data, sizeof(__data));
//                    this->cont->insert(&ch, sizeof(ch));
                } else {
                    auto __data = new data(&i, typeid(i).name(), sizeof(i));

                    this->list.push_front(&__data, sizeof(__data));
//                    this->list.push_front(&i, sizeof(i));

                    this->cont->insert(&__data, sizeof(__data));
//                    this->cont->insert(&i, sizeof(i));
                }
            }
            finish = clock();
            time = finish - start;
            break;
    }

    return (double) time / CLOCKS_PER_SEC;
}

double ContainerTest::testRemove(size_t num_elem)
{
    double time;
    Container::Iterator *it = cont->newIterator();

    if (num_elem >= this->cont->size())
        time = testClear();
    else {
        clock_t start = clock();

        size_t i = 0;
        it = cont->begin();
        while (i < num_elem || !it->equals(cont->end())) {
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
    size_t size;

    for(it = this->cont->begin(); !it->equals(this->cont->end()); it->goToNext())
    {
        auto _data  = *(data**) (it->getElement(size));
        if( !strcmp(_data->name, "i") ) {
            printf("%22d | size (bytes) = %lu\n", *(int*)(_data->elem), size);
        }
        if( !strcmp(_data->name, "Pc") ){
           printf("%22s | size (bytes) = %lu\n", (char*)(_data->elem), size);
        }
    }
    cout << endl;
}

int ContainerTest::AutoInsert(size_t num_elem, int flag)
{
    double time = testInsert(num_elem, flag);

    bool success = true;
    size_t size;

    auto l_it = this->list.newIterator();
    auto it = this->cont->newIterator();

    l_it = list.begin();

    for(size_t i = 0; i < this->list.size(); i++)
    {

        void* elem = l_it->getElement(size);
        it = this->cont->find(elem, size);

        l_it->goToNext();

        success &= (it != nullptr);
    }

    success? printf("Test passed. Elapsed time: %lf\n",time) : printf("Test failed.\n");

    return success;
}

int ContainerTest::AutoRemoveTest(size_t num_elem)
{
    clock_t elapsed(0), start_1, start_2, end_1, end_2;
    bool success = true;
    size_t size;

    auto l_it = this->list.newIterator();


    l_it = this->list.begin();

    for(size_t i = 0; i < this->list.size(); i++)
    {
        auto it = this->cont->newIterator();

        void* elem = l_it->getElement(size);

        start_1 = clock();
        it = this->cont->find(elem, size);
        end_1 = clock();

        success &= (it != nullptr); // first time found

        start_2 = clock();
        this->cont->remove(it);
        end_2 = clock();

        it = this->cont->find(elem, size);

        success &= (it == nullptr); // found after deletion out of Set

        l_it->goToNext();

        elapsed += (end_1 - start_1) + (end_2 - start_2);
    }

    success? printf("Test passed. Elapsed time: %lf",(double) elapsed / CLOCKS_PER_SEC) : printf("Test failed.");

    return success;
}
