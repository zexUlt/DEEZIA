//
// Created by yuszafar on 09.07.2019.
//
#pragma once
#include "List2Abstract.h"
#include "Exceptions.h"

class List2: public AbstractList2 {
    friend class Queue;
private:
    struct Vertx_2 {
        void *data;
        size_t size;
        Vertx_2 *next;
        Vertx_2 *prev;
        int real;

        explicit Vertx_2(void *elem, size_t _size, List2 *list2) {
                data = list2->_memory.allocMem(_size);
                memcpy(data, elem, _size);
                real =* (int*)elem;

            size = _size;
            next = nullptr;
            prev = nullptr;

        }
    };

    Vertx_2 *head;
    Vertx_2 *_end;
    int _size;
public:
    explicit List2(MemoryManager &mem) : AbstractList2(mem){head = nullptr; _end= nullptr;  _size = 0;}

    class List2Iterator : public Iterator {
        friend class List2;
        friend class Queue;
    private:
        Exceptions* e;
        Vertx_2 *current;
        List2 *list2;
        bool isEnd;

        List2Iterator(Vertx_2 *_current, List2 *_list2) {
            Exceptions ex("Something went wrong.");

            e = &ex;
            current = _current;
            list2 = _list2;
            isEnd = false;

        }

    public:

        void *getElement(size_t &size) final {
            if(this->current == nullptr)
                throw this->e->NULL_NODE_CALL(this);

            size = current->size;
            return current->data;
        }
        bool hasNext() final {
            return (current->next != nullptr);
        }
        void goToNext() final {
            if(this->current->next == nullptr)
                this->isEnd = true;
            this->current = this->current->next;

        }
        bool equals(Container::Iterator *right) final {
            auto* rght = (List2Iterator* ) right;
            return (list2 == rght->list2) && (this->current == rght->current) && (this->isEnd == rght->isEnd);
        }
    };

    int push_back(void *elem, size_t elemSize) final {
        if(head == nullptr)
        {
            head = new Vertx_2(elem, elemSize, this);
            _end = head;
        }
        else{
            Vertx_2* tmp = _end;
            _end = new Vertx_2(elem, elemSize, this);
            _end->prev = tmp;
            _end->next = nullptr;
            tmp->next = _end;
        }

        _size++;
        return 1;
    }

    int push_front(void *elem, size_t elemSize) final {
        if(head == nullptr)
        {
            head = new Vertx_2(elem, elemSize, this);
            _end = head;

        }
        else{
            Vertx_2* tmp = head;
            head = new Vertx_2(elem, elemSize, this);
            head->next = tmp;
            head->prev = nullptr;
            tmp->prev = head;
        }

        _size++;
        return 1;
    }

    void pop_back() final {
        if(_size == 1)
        {
            _memory.freeMem(head->data);
            delete[] head;
            _size--;
            return;
        }
        Vertx_2* tmp = _end;
        _end = _end->prev;
        _end->next = nullptr;
        _memory.freeMem(tmp->data);
        delete[] tmp;
        _size--;

    }

    void pop_front() final {
        if(_size == 1)
        {
            _memory.freeMem(head->data);
            delete[] head;
            _size--;
            return;
        }
        Vertx_2* tmp = head;
        head = head->next;
        head->prev = nullptr;
        _memory.freeMem(tmp->data);
        delete[] tmp;
        _size--;

    }

    void* front(size_t &size) final {
        size = head->size;
        return head->data;
    }

    void* back(size_t &size) final {
        size = _end->size;
        return _end->data;
    }

    int insert(Iterator *iter, void *elem, size_t elemSize) final {
        auto* i = (List2::List2Iterator* ) iter;
        auto* added = new Vertx_2(elem, elemSize, this);
        added->next = i->current;
        added->prev = i->current->prev;
        i->current->prev->next = added;
        i->current->prev = added;
        _size++;
        return 0;
    }
    int size() final{
        return _size;
    }

    size_t max_bytes() final{
        return (size_t) 10e8;
    }

    List2Iterator* find(void *elem, size_t size) final{
        for (Vertx_2* tmp = head; tmp->next != nullptr; tmp = tmp->next)
            if (size == tmp->size && memcmp(elem, tmp->data, size) == 0)
                return new List2Iterator(tmp, this);
        return new List2Iterator(nullptr, this);
    }
    List2Iterator* newIterator() final {
        return new List2Iterator(nullptr, this);
    }

    List2Iterator* begin() final {
        return new List2Iterator(head, this);
    }

    List2Iterator* end() final {
        auto it = new List2Iterator(nullptr, this); // ??
        it->isEnd = true;

        return it;
    }

    void remove(Container::Iterator *iter) final {
        auto* i = (List2Iterator* ) iter;
        if (i->current == head)
            if(head->next == nullptr)
                i->isEnd = true;
            else
                head = head->next;

        else if(i->current == _end)
        {
            _end = _end->prev;
        }
        else {
            i->current->prev->next = i->current->next;
            i->current->next->prev = i->current->prev;

        }
        _memory.freeMem(i->current->data);
        delete[] i->current;

        _size--;
        if (_size == 0){
            i->current = nullptr;
        }

    }

    void clear() final {
        for(Vertx_2* tmp = head; tmp->next != nullptr;)
        {
            auto to_del = tmp;
            tmp = tmp->next; // ?????
            _memory.freeMem(to_del->data);
            delete[] to_del;

        }

        _size = 0;

    }

    bool empty() final {
        return (head == nullptr);
    }

    ~List2() final = default;

};


