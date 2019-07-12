//
// Created by yuszafar on 12.07.2019.
//
#include "List.h"

#pragma once

bool test_push(List l, int size)
{
    for(int i = 0; i < size; i++)
        l.push_front(&i, sizeof(int));
    size_t sz;


    int i = size - 1;
    for(auto it = l.begin(); !it->equals(l.end()); it->goToNext()) {
        if (*(int *) it->getElement(sz) != i)
            return 0;
        i--;
    }
    cout << endl;

        return 1;
}