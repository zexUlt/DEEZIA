//
// Created by zexult on 28.03.19
//


/**
 * TODO List:
 * 1. Create Set constructor - 50%
 * 2. Create size calculating function - 0
 * 3. Create recursive removing (clear) | Probably DFS - 0
 * 4. Create iterator constructor with proper memory allocation - 0
 */

// Вопросы к куратору практикума
// Q1: Как исправить замечания компилятора на отсутствие дефолтного конструктора в абстрактных классах?
// Q2: Что делать с тем, что итератор описан в параллельной ветке иерархии классов, отличной от абстрактного класса итератора?
// Q3: Как корректно удалить void*?
// Q4: Как выделить память под поле RBTree tree в классе Set?

#include "Set.h"

int Set::insert(void* elem, size_t _size)
{
    if(tree.find(elem))
        return 1;
    else {
        return this->tree.insertVal(elem, _size);
    }
}

Set::Set(int size)
{
    RBTree *tree;

    tree = new RBTree();
}

int Set::size()
{
    return this->tree.getSize();
}

size_t Set::max_bytes()
{

}

RBTree::SetIterator* Set::begin()
{
    RBTree::SetIterator* it;
    it->setCurrent(this->tree.getBegin());
    return it;
}

RBTree::SetIterator* Set::end()
{
    RBTree::SetIterator *it;
    it = this->tree.getEnd();
    return it;
}

RBTree::SetIterator* Set::find(void *elem, size_t size)
{

}

void Set::clear()
{

}

RBTree::SetIterator* Set::newIterator()
{
    return new SetIterator(this->tree);
}

void Set::remove(RBTree::SetIterator *iter)
{
    tree.deleteVal(iter->current->value);
    iter->goToNext();
}

bool Set::empty()
{
    return tree.getRoot() == nullptr;
}


