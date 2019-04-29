//
// Created by zexult on 28.03.19
//

#pragma once


#include "SetAbstract.h"
#include "RBTree.h"
#include "MemoryManager.h"

class Set : public AbstractSet, public RBTree{
private:
    RBTree tree;
public:
    explicit Set(MemoryManager &mem):  AbstractSet(mem), tree(mem){}
    int insert(void*, size_t) final;
    int size() final;
    size_t max_bytes() final;
    Container::Iterator* find(void *elem, size_t size) final;
    Container::Iterator* newIterator() final;
    Container::Iterator* begin() final;
    Container::Iterator* end() final;
    void remove(Container::Iterator*) final;
    void clear() final;
    bool empty() final;
    ~Set() override {}
};


