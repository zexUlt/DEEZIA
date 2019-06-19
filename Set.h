//
// Created by zexult on 28.03.19
//

#pragma once


#include "SetAbstract.h"
#include "Exceptions.h"
#include "RBTree.h"
#include "MemoryManager.h"
#include <string>

class Set : public AbstractSet, public RBTree{
    friend class ContainerTest;
private:
    Exceptions e;
    RBTree tree;
public:
    explicit Set(MemoryManager &mem):  AbstractSet(mem), tree(mem), e("Something gone wrong."){}
    int insert(void*, size_t) final; // is working
    int size() final; // is working
    size_t max_bytes() final; // is working
    Container::Iterator* find(void *elem, size_t size) final; // is working
    Container::Iterator* newIterator() final; // is working
    Container::Iterator* begin() final; // is working
    Container::Iterator* end() final; // is working
    void remove(Container::Iterator*) final; // pretests passed;
    void clear() final; // is working
    bool empty() final; // is working
    ~Set() final = default;
};


