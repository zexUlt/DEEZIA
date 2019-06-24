//
// Created by zexult on 24.06.19.
//

#include "List.h"

List::Vertx::Vertx(void *elem, size_t _size, List *list)
{
    if(elem != nullptr) {
        data = list->_memory.allocMem(_size);
        memcpy(data, elem, _size);
    } else
        data = nullptr;
    size = _size;
    next = nullptr;
}

int List::push_front(void *elem, size_t elemSize)
{
    Vertx *tmp = head;
    head = new Vertx(elem, elemSize, this);
    head->next = tmp;
    _size++;
    return 1;
}

void List::pop_front()
{
    Vertx *tmp = head;
    head = head->next;
    _memory.freeMem(tmp->data);
    delete[] tmp;
    _size--;
}

void* List::front(size_t &size)
{
    size = head->size;
    return head->data;
}

int List::insert(Container::Iterator *iter, void *elem, size_t elemSize)
{
    auto *i = (List::ListIterator *) iter;
    auto *added = new Vertx(elem, elemSize, this);
    added->next = i->curr;
    Vertx *tmp = head;
    while(tmp->next != nullptr)
    {
        if(tmp->next == i->curr)
            tmp ->next = added;
        tmp = tmp->next;
    }
    _size++;
    return 0;
}

int List::size()
{
    return _size;
}

size_t List::max_bytes()
{
    return (size_t) 10e8;
}

List::ListIterator* List::find(void *elem, size_t size)
{
    for (Vertx *tmp = head; tmp->next != nullptr; tmp = tmp->next)
        if (size == tmp->size && memcmp(elem, tmp->data, size) == 0)
            return new ListIterator(tmp, this);
    return new ListIterator(nullptr, this);
}

List::ListIterator* List::newIterator()
{
    return new ListIterator(nullptr, this);
}

List::ListIterator* List::begin()
{
    return new ListIterator(head, this);
}

List::ListIterator* List::end()
{
    return new ListIterator(nullptr, this);
}

void List::remove(Container::Iterator *iter)
{
    auto *i = (ListIterator *) iter;
    if (i->curr == head)
        head = head->next;
    else {
        for(Vertx* tmp = head; tmp->next != nullptr; tmp = tmp->next)
            if(tmp->next == i->curr)
            {
                tmp = i->curr->next;
                break;
            }
    }

    _memory.freeMem(i->curr->data);
    delete[] i->curr;

    _size--;
}

void List::clear()
{
    for(Vertx *tmp = head; tmp->next != nullptr;)
    {
        auto to_del = tmp;
        tmp = tmp->next;
        _memory.freeMem(to_del->data);
        delete[] to_del;

    }

    _size = 0;
//         for (tmp; tmp->next != nullptr; tmp = tmp->next){
//             _memory.freeMem(tmp->data);
//             delete[] tmp;
//         }
}

bool List::empty()
{
    return (head == nullptr);
}

// List Iterator

void* List::ListIterator::getElement(size_t &size)
{
    size = curr->size;
    return curr->data;
}

bool List::ListIterator::hasNext()
{
    return (curr->next != nullptr);
}

void List::ListIterator::goToNext()
{
    curr = curr ->next;
}

bool List::ListIterator::equals(Container::Iterator *right)
{
    auto *rght = (ListIterator *) right;
    return (list == rght->list);    
}
