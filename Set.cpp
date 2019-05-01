//
// Created by zexult on 28.03.19
//


/**
 * TODO List:
 * 1. Create Set constructor - 50%
 * 2. Create size calculating function - 100%
 * 3. Create recursive removing (clear) | Probably DFS - 0
 * 4. Create iterator constructor with proper memory allocation - 0
 */

#include "Set.h"

int Set::insert(void* elem, size_t _size)
{
    if(this->tree.find(elem,_size))
        return 1;
    else {
        return this->tree.insertVal(elem, _size);
    }
}

int Set::size()
{
    return this->tree._size;
}

size_t Set::max_bytes()
{
    return (size_t) 10e9;
}

Container::Iterator* Set::begin()
{
    auto it = new SetIterator(&this->tree);
    return (Container::Iterator*) it;
}

Container::Iterator* Set::end()
{
    RBTree::SetIterator *it;
    it = this->tree._end;
    return (Container::Iterator*)it;
}

Container::Iterator* Set::find(void *elem, size_t size)
{
    Node* node = nullptr;
    this->tree.find(elem,size,&node);
    auto it = new SetIterator(&(this->tree),node);
    Container::Iterator* iter = it;

    return iter;
}

void Set::clear()
{

}

Container::Iterator* Set::newIterator()
{
    return new SetIterator(&this->tree);
}

void Set::remove(Container::Iterator *iter)
{
    auto *it = (RBTree::SetIterator*) iter;
    tree.deleteVal(it->current->value, it->current->__size);
    it->goToNext();
}

bool Set::empty()
{
    return tree.root == nullptr;
}


