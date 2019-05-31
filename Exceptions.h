//
// Created by zexult on 02.05.19.
//

#pragma once

#include "Container.h"
#include "iostream"
using namespace std;

struct Exceptions : public Container::Error{
    explicit Exceptions(const char* err_msg) : Error(err_msg){}
    void what();
    Exceptions NULL_NODE_CALL(Container::Iterator*);
    Exceptions END_ITERATOR_REMOVING(Container::Iterator*);
};


