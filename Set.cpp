//
// Created by zexult on 28.03.19
//


#include "Set.h"

int Set::insert(int elem, size_t _size)
{
    if(tree.find(elem))
        return 1;
    else {
        this->tree.insertVal(elem);
        return 0;
    }
}

Set::Set(int)
{

}

int Set::size()
{

}

size_t Set::max_bytes()
{

}

RBTree::SetIterator* Set::begin()
{
    RBTree::SetIterator *it;
    Node* begin = this->tree.minimalNode(this->tree.getRoot());
    it->setCurrent(begin);
    return it;
}

RBTree::SetIterator * Set::end()
{
    RBTree::SetIterator *it;
    it->setCurrent(it->getEnd());
    return it;
}

RBTree::SetIterator * Set::find(void *elem, size_t size)
{

}

void Set::clear()
{

}

RBTree::SetIterator * Set::newIterator()
{

}

void Set::remove(RBTree::SetIterator *iter)
{

}

bool Set::empty()
{

}