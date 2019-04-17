//
// Created by zexult on 28.03.19
//

#ifndef DEEZIA_SET_H
#define DEEZIA_SET_H

#include "Tree.h"

class Set {
private:
    RBTree tree;
public:
    explicit Set(int);
    int insert(int, size_t);
    int size();
    size_t max_bytes();
    RBTree::SetIterator* find(void *elem, size_t size);
    RBTree::SetIterator* newIterator();
    RBTree::SetIterator* begin();
    RBTree::SetIterator* end();
    void remove(RBTree::SetIterator*);
    void clear();
    bool empty();
};


#endif //DEEZIA_SET_H
