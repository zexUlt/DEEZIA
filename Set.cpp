//
// Created by zexult on 28.03.19
//

#include "Set.h"
#include "ContainerTest.h"

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
    if(!this->tree._size)
        return end();
    else {
        it->current = tree.minimalNode(tree.root);
        return (Container::Iterator *) it;
    }
}

Container::Iterator* Set::end()
{
    Node* node = nullptr;
    auto *it = new SetIterator(&(this->tree), node);
    it->isEnd = true;
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
    tree.DFSfullRemove(tree.root);
}

Container::Iterator* Set::newIterator()
{
    return new SetIterator(&this->tree);
}

void Set::remove(Container::Iterator *iter)
{
    auto *it = (RBTree::SetIterator*) iter;

    if(it->isEnd)
        throw e.END_ITERATOR_REMOVING(it);

    Node* ptr = it->current;

    tree.deleteVal(ptr);
    tree.find(ptr->value, ptr->__size);
}

bool Set::empty()
{
    return _size == 0;
}


