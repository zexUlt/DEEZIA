//
// Created by yuszafar on 17.06.2019.
//

#ifndef DEEZIA_LIST_H
#define DEEZIA_LIST_H

#endif //DEEZIA_LIST_H

#include "ListAbstract.h"

class List : protected AbstractList {
private:
    struct Element {
        void *data;
        size_t size;
        Element *pnext;

        Element(void *elem, size_t elemSize, List *list) {
            if (elem != nullptr) {
                data = list->_memory.allocMem(elemSize);
                memcpy(data, elem, elemSize);
            }
            else
            {
                data = nullptr;
            }
            size = elemSize;
            pnext = nullptr;
        }
    };
    Element *head;
    int _size;
public:
    explicit List(MemoryManager &mem) : AbstractList(mem) {
        head = new Element(nullptr, 0, this);
        _size = 0;
    }

    class Itr : public Iterator {
    private:
        Element *curr;
        List *this_list;

        Itr(Element *curr, List *this_list) {
            this -> curr = curr;
            this -> this_list = this_list;
        }

    public:
        void *getElement(size_t &size) override {
            size = curr->size;
            return curr->data;
        }

        bool hasNext() override {
            return (curr->pnext != nullptr);
        }

        void goToNext() override {
            curr = curr ->pnext;
        }

        bool equals(Container::Iterator *right) override {
            auto *rght = (Itr *) right;
            return (this_list == rght->this_list);
        }

        friend class List;
    };

    int push_front(void *elem, size_t elemSize) override {
        Element *tmp = head;
        head = new Element(elem, elemSize, this);
        head->pnext = tmp;
        _size++;
        return 1;
    }

    void pop_front() override {
        Element *tmp = head;
        head = head->pnext;
        _memory.freeMem(tmp->data);
        delete[] tmp;
        _size--;
    }

    void *front(size_t &size) override {
        size = head->size;
        return head->data;
    }

    int insert(Container::Iterator *iter, void *elem, size_t elemSize) override {
        auto *i = (Itr *) iter;
        auto *added = new Element(elem, elemSize, this);
        added->pnext = i->curr;
        Element *tmp = head;
        while(tmp->pnext != nullptr)
        {
            if(tmp->pnext == i->curr)
                tmp ->pnext = added;
            tmp = tmp->pnext;
        }
        _size++;
        return 0;
    }

    int size() override {
        return _size;
    }

    size_t max_bytes() override {
        // return 10e8; так как не реализован свой менеджер памяти - дефолтный будет говорить, что места "бесконечно"
        return _memory.maxBytes();
    }

    Itr *find(void *elem, size_t size) override {
        Element *tmp = head;
        for (tmp; tmp->pnext != nullptr; tmp = tmp->pnext)
            if (size == tmp->size && memcmp(elem, tmp->data, size) == 0)
                return new Itr(tmp, this);
        return new Itr(nullptr, this);

    }

    Itr *newIterator() override {
        return new Itr(nullptr, this);
    }

    Itr *begin() override {
        return new Itr(head, this);
    }

    Itr *end() override { // спорная функция, я бы сделал end уникальным
        return new Itr(nullptr, this);
    }

    void remove(Container::Iterator *iter) override {
        auto *i = (Itr *) iter;
        if (i->curr == head)
        {
            //_memory.freeMem(i->curr->data);
            //delete[] i->curr;
            head = head->pnext;
            //i->curr = head; // нам пофиг на итератор после удаления, так что это можно и не делать
        } else {
            Element *tmp = head;
            for(tmp; tmp->pnext != nullptr; tmp = tmp->pnext)
                if(tmp->pnext == i->curr)
                {
                    //tmp->pnext = i->curr->pnext;
                    tmp = i->curr->pnext;
                    break;
                }
        }


        //Element *next = i->curr->pnext;
        _memory.freeMem(i->curr->data);
        delete[] i->curr;
        //i->curr = next;
        _size--;
    };

    void clear() override {
        Element *tmp = head;
//         for (tmp; tmp->pnext != nullptr; tmp = tmp->pnext){
//             _memory.freeMem(tmp->data);
//             delete[] tmp;
//         }
        for(tmp; tmp->pnext != nullptr;)
        {
            auto to_del = tmp;
            tmp = tmp->pnext;
            _memory.freeMem(to_del->data);
            delete[] to_del;
            
        }

        _size = 0;
    }

    bool empty() override {
        return (head == nullptr);
    }

};
