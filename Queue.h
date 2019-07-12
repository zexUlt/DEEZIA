//
// Created by yuszafar on 11.07.2019.
//
#include "QueueAbstract.h"
#include "List2.h"
#include "Mem.h"
#pragma once
class Queue: protected AbstractQueue{
private:

    List2 l2;


public:
    explicit Queue(MemoryManager &mem) : AbstractQueue(mem), l2(mem) {}
    int push(void *elem, size_t size) final;
    int pop() final;
    void* front(size_t &size) final;
    void* back(size_t &size) final;
    int insert(Iterator *iter, void *elem, size_t size) final;
    int size() final;
    size_t max_bytes() final;
    List2::List2Iterator* find(void *elem, size_t size) final;
    List2::List2Iterator* newIterator() final;
    List2::List2Iterator* begin() final;
    List2::List2Iterator* end() final;
    void remove(Container::Iterator *iter) final;
    void clear() final;
    bool empty() final;

};
