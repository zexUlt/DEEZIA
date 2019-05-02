#include "List.h"
#include <stdlib.h>
#include <stdio.h>

#define NullValue 0u   //устанавливаю побитовое значение в переменную NullValue 0u 00000000 00000000 00000000 00000000
//  https://stackoverflow.com/questions/26555159/what-does-the-assignment-of-0u-to-a-variable-mean-in-c

//----------//----------//----------//----------||----------\\----------\\----------\\----------\\
//~~~~~~~~~~//~~~~~~~~~~//~~~~~~~~~~Конструкторы для элементов~~~~~~~~~~\\~~~~~~~~~~\\~~~~~~~~~~\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

//  1 Конструктор - все просто по нулям заполняем\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::ListElement() : Znacheniye(NULL), nextElement(NULL), ElementSize(NullValue) {}

//  2 Конструктор - получаем адрес элемента\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::ListElement(List::ListElement &element) {
    this->Znacheniye = new char[element.ElementSize]; // под значение элемента выделяется память
    memcpy(this->Znacheniye, element.Znacheniye,
           element.ElementSize);  //копирую полностью из данного мне элемента в новый под размер
    this->ElementSize = element.ElementSize; //копирую его размер
    /*
     * Определение
void *memcpy(void *dst, const void *src, size_t n);
где:  dst — адрес буфера назначения  srс — адрес источника       n — количество байт для копирования
Функция копирует n байт из области памяти, на которую указывает src, в область памяти, на которую указывает dst.
     \Функция возвращает адрес назначения dst.
Области памяти не должны перекрываться, иначе данные могут быть скопированы неправильно, например таким образом:
     */
}

//3 Конструктор - дали значение и положение\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::ListElement(void *Znacheniye, size_t size) {   //в параметры коннструктора довать параметры мем менедж
    this->Znacheniye = new char[size];     //    lj,fdbnm d rjycnhernjh bcgjkmpjdfybt
    memcpy(this->Znacheniye, Znacheniye, size);
    this->ElementSize = size;
    this->nextElement = NULL;

}

//Деструктор\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::~ListElement() {
    if (this->Znacheniye)               //если есть хоть что то в элементе то удаляем нахер
    {
        delete this->Znacheniye;
    }
}


//Конструктор списка\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\


List::List(MemoryManager &mem) : AbstractList(mem), FirstElement(new ListElement), ListSize(
        NullValue) {}    //конструктор списка. Выделяем память под первый элемент и размер 0

List::~List() {

    this->clear();    //Очищаем
    this->FirstElement->~ListElement();   //даляем первый элемент
}


List::IteratorForList::IteratorForList() : current(NULL) {}

List::IteratorForList::IteratorForList(List::ListElement *element) : current(element) {}

List::IteratorForList::IteratorForList(List::IteratorForList &iterator) : current(iterator.current) {}

List::IteratorForList::~IteratorForList() {

}

bool List::IteratorForList::hasNext() {
    if (current->Znacheniye && current->nextElement) //если текущий указывает на след и в текущем есть что то то возвр 1
    {
        return true;
    }
    return false;
}

void List::IteratorForList::goToNext() {
    this->current = this->current->nextElement;   //переход на сдел элемент
}

void *List::IteratorForList::getElement(size_t &my_size_element) {
    my_size_element = this->current->ElementSize;
    return this->current->Znacheniye;
}

bool List::IteratorForList::equals(List::Iterator *right) {
    if (this && right) {
        return !(memcmp(this, right, sizeof(*this)));
    } else if (!this && !right)
        return true;
    return false;
}


List::IteratorForList *List::begin() {    //указатель на начало списка
    if (this->empty())
        return NULL; //если указатель этот пустой то вернуть 0

    return new IteratorForList(this->FirstElement);
}

List::IteratorForList *List::end() {             //ГОТОВО
    if (this->empty())
        return NULL;
    IteratorForList *iterator = this->begin();
    if (!iterator)
        return NULL;
    while (iterator->hasNext()) {
        iterator->goToNext();
    }
    return iterator;
}

List::IteratorForList *List::newIterator() {    //не выходит что хочу
    if(this->FirstElement!=NULL)
    {
        IteratorForList *iterator = new IteratorForList();
    }
    return 0;
}

int List::push_front(void *elem, size_t elemSize) {       //Добавить в начало
    ListElement *el = new ListElement(elem, elemSize);    //создаю новый элемент
    el->nextElement = this->FirstElement;     //его следующим ставим бывший первый
    this->FirstElement = el;       //первым ставим новый элемент
    this->ListSize++;    //количество элементов увеличиваем
    return 0;
}

void List::pop_front() {
    ListElement *el;
    if(this->FirstElement->nextElement)
    {
        el = this->FirstElement; //приравниваем елемент первый
        this->FirstElement=this->FirstElement->nextElement; //сдвигаем первенство на 1 вперед
        delete (el);   //удаляем элемент
        this->ListSize--;  //уменьшаем кол-во элементов в списке
    }

}

void *List::front(size_t &size) {
    size = this->FirstElement->ElementSize;  //неявный возврат размера
    return this->FirstElement->Znacheniye;  //возврат значения
}

int List::insert(IteratorForList *iter, void *elem, size_t elemSize)
{
    IteratorForList *iterator = this->begin();
    ListElement *el;
    if(iterator==iter)
    {
        this->push_front(elem, elemSize);
        return 0;
    }
    while(iterator->current->nextElement != iter->current)  //идем вплотную к тому указател куда указывает итератов данный
    {
        iterator->goToNext();
    }
    el = new ListElement(elem, elemSize);
    iterator->current->nextElement=el;  //ставим следующим новый элемент
    el->nextElement = iter->current;   //а после элемента ставим данный указатель
    //мы вклинили новый элемент
    this->ListSize++;
    return 0;
}

int List::size() {
    return static_cast<int>(this->ListSize);   //преобразование типа в инт потому что ЛистСайз типа сайзт
}

size_t List::max_bytes() {
    return 0;
}

Container::Iterator *List::find(void *elem, size_t size) {
    return nullptr;
}

void List::remove(Container::Iterator *iter) {

}

void List::clear() {

}










