//
// Created by yuszafar on 17.06.2019.
//

#ifndef DEEZIA_LIST_H
#define DEEZIA_LIST_H

#endif //DEEZIA_LIST_H

#include "ListAbstract.h"
#include "Exceptions.h"

class List : protected AbstractList {
private:
    struct Vertx {
        void *data;
        size_t size;
        Vertx *next;
        int real;

        explicit Vertx(void *elem, size_t _size, List *list);
    };
    
    Vertx *head;
    int _size;

public:
    explicit List(MemoryManager &mem) : AbstractList(mem){head = new Vertx(nullptr, 0, this); _size = 0;}

    class ListIterator : public Iterator {
        friend class List;
    private:
        Exceptions* e;
        Vertx *current;
        List *list;
        bool isEnd;

        ListIterator(Vertx *_current, List *_list);

    public:
        void *getElement(size_t &size) final;
        bool hasNext() final;
        void goToNext() final;
        bool equals(Container::Iterator *right) final;
    };

    int push_front(void *elem, size_t elemSize) final;
    void pop_front() final;
    void* front(size_t &size) final;
    int insert(Container::Iterator *iter, void *elem, size_t elemSize) final;
    int size() final;
    size_t max_bytes() final;
    ListIterator* find(void *elem, size_t size) final;
    ListIterator* newIterator() final;
    ListIterator* begin() final;
    ListIterator* end() final;
    void remove(Container::Iterator *iter) final;
    void clear() final;
    bool empty() final;

};
