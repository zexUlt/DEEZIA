//
// Created by zexult on 28.03.19
//

#pragma once

#include "RBTree.h"
#include "SetAbstract.h"
#include "MemoryManager.h"

friend class Set : public AbstractSet, public RBTree{
private:
    RBTree tree;
public:
    explicit Set(MemoryManager &mem):  AbstractSet(mem), tree(mem){};
    int insert(void*, size_t) final;
    int size() final;
    size_t max_bytes() final;
    RBTree::SetIterator* find(void *elem, size_t size) final;
    RBTree::SetIterator* newIterator() final;
    RBTree::SetIterator* begin() final;
    RBTree::SetIterator* end() final;
    void remove(RBTree::SetIterator*);
    void clear() final;
    bool empty() final;
};


