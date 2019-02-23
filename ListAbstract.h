#pragma once
#include "GroupContainer.h"

// Абстрактный класс: однонаправленный список
class AbstractList: public GroupContainer
{
public:
    // конструктор
    AbstractList(MemoryManager &mem): GroupContainer(mem) {}

    // деструктор
    virtual ~AbstractList() {}

    // Добавление элемента в начало контейнера.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    virtual int push_front(void *elem, size_t elemSize) = 0;

    // Удаление элемента из начала контейнера.
    virtual void pop_front() = 0;

    // Функция явно возвращает указатель на элемент, находящийся в начале контейнера.
    // и не явно возвращает размер данных
    virtual void* front(size_t &size) = 0;

    // Добавление элемента в позицию, на которую указывает итератор iter.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    virtual int insert(Iterator *iter, void *elem, size_t elemSize) = 0;
};
