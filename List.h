#pragma once
#include <string.h>
#include <stdlib.h>
#include "ListAbstract.h"
#include "MemoryManager.h"
#include "Container.h"

class List : public AbstractList{
protected:   //то, что разрешается наследовать
    class ListElement {
    public:   
        void* Znacheniye;  //Войдовский указатель на значение элемента, там будет хер пойми что, поэтому войд
        ListElement* nextElement; //Указатель на следующий элемент в списке
        size_t ElementSize;       //size_t как int только положительные числа (исп для счетчиков или подобного)
        //3 варианта конструктора для элемента списка и деструктор
        ListElement();

        ListElement(ListElement &element);

        ListElement(void *Znacheniye, size_t size);

        ~ListElement();
    };

    size_t ListSize; //переменнная для размера списка   приват
    ListElement *FirstElement;  //Указатель на первый элемент списка  приват
public:
    //конструктор\деструктор
    List(MemoryManager &mem);

    ~List();

    //Создаю класс для итератора
class IteratorForList : public Container::Iterator{
    public:
        ListElement *current;    //указатель на текущий итератор

        IteratorForList();

        IteratorForList(ListElement *element);

        IteratorForList(IteratorForList &iterator);

        ~IteratorForList();

        bool hasNext();  //функция для проверки существования следующего номера

        void goToNext();//функция перехода на следующий итератор

        void *getElement(size_t &my_size_element);//получить неявно размер данных

        bool equals(Iterator *right);  // проверка на равенство итераторов


    };


        //методы листа
        // Добавление элемента в начало контейнера.
        // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
        int push_front(void *elem, size_t elemSize) override;

        // Удаление элемента из начала контейнера.
        void pop_front();

        // Функция явно возвращает указатель на элемент, находящийся в начале контейнера.
        // и не явно возвращает размер данных
        void* front(size_t &size);

        // Добавление элемента в позицию, на которую указывает итератор iter.
        // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
        int insert(IteratorForList *iter, void *elem, size_t elemSize);



        //методы контейнера

    // Функция возвращает значение, равное количеству элементов в контейнере.
     int size();

    // Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
     size_t max_bytes();

    // Функция возвращает указатель на итератор, указывающий на первый найденный
    // в контейнере элемент. Если элемент не найден, возвращается пустой указатель.
    IteratorForList* find(void *elem, size_t size);

    // Создание итератора, соответствующего данному типу контейнера.
    IteratorForList* newIterator();

    // Функция возвращает указатель на итератор, указывающий на первый элемент
    // контейнера. Если контейнер пустой, возвращается нулевой указатель.
    IteratorForList* begin();

    // Функция возвращает указатель на итератор, указывающий позицию за последним
    // элементом контейнера. Если контейнер пустой, возвращается нулевой указатель.
    IteratorForList* end();

    // Удаление элемента из позиции, на которую указывает итератор iter.
    // После удаления итератор указывает на следующий за удаленным элемент.
     void remove(Iterator *iter);

    // Удаление всех элементов из контейнера.
     void clear();

    // Если контейнер пуст возвращает true, иначе false
     bool empty() = 0;

};

