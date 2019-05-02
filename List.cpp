#include "List.h"
#include <stdlib.h>
#include <stdio.h>

#define NullValue 0u   //������������ ��������� �������� � ���������� NullValue 0u 00000000 00000000 00000000 00000000
//  https://stackoverflow.com/questions/26555159/what-does-the-assignment-of-0u-to-a-variable-mean-in-c

//----------//----------//----------//----------||----------\\----------\\----------\\----------\\
//~~~~~~~~~~//~~~~~~~~~~//~~~~~~~~~~������������ ��� ���������~~~~~~~~~~\\~~~~~~~~~~\\~~~~~~~~~~\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

//  1 ����������� - ��� ������ �� ����� ���������\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::ListElement() : Znacheniye(NULL), nextElement(NULL), ElementSize(NullValue) {}

//  2 ����������� - �������� ����� ��������\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::ListElement(List::ListElement &element) {
    this->Znacheniye = new char[element.ElementSize]; // ��� �������� �������� ���������� ������
    memcpy(this->Znacheniye, element.Znacheniye,
           element.ElementSize);  //������� ��������� �� ������� ��� �������� � ����� ��� ������
    this->ElementSize = element.ElementSize; //������� ��� ������
    /*
     * �����������
void *memcpy(void *dst, const void *src, size_t n);
���:  dst � ����� ������ ����������  sr� � ����� ���������       n � ���������� ���� ��� �����������
������� �������� n ���� �� ������� ������, �� ������� ��������� src, � ������� ������, �� ������� ��������� dst.
     \������� ���������� ����� ���������� dst.
������� ������ �� ������ �������������, ����� ������ ����� ���� ����������� �����������, �������� ����� �������:
     */
}

//3 ����������� - ���� �������� � ���������\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::ListElement(void *Znacheniye, size_t size) {   //� ��������� ������������� ������ ��������� ��� ������
    this->Znacheniye = new char[size];     //    lj,fdbnm d rjycnhernjh bcgjkmpjdfybt
    memcpy(this->Znacheniye, Znacheniye, size);
    this->ElementSize = size;
    this->nextElement = NULL;

}

//����������\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\

List::ListElement::~ListElement() {
    if (this->Znacheniye)               //���� ���� ���� ��� �� � �������� �� ������� �����
    {
        delete this->Znacheniye;
    }
}


//����������� ������\\
//----------//----------//----------//----------||----------\\----------\\----------\\----------\\


List::List(MemoryManager &mem) : AbstractList(mem), FirstElement(new ListElement), ListSize(
        NullValue) {}    //����������� ������. �������� ������ ��� ������ ������� � ������ 0

List::~List() {

    this->clear();    //�������
    this->FirstElement->~ListElement();   //������ ������ �������
}


List::IteratorForList::IteratorForList() : current(NULL) {}

List::IteratorForList::IteratorForList(List::ListElement *element) : current(element) {}

List::IteratorForList::IteratorForList(List::IteratorForList &iterator) : current(iterator.current) {}

List::IteratorForList::~IteratorForList() {

}

bool List::IteratorForList::hasNext() {
    if (current->Znacheniye && current->nextElement) //���� ������� ��������� �� ���� � � ������� ���� ��� �� �� ����� 1
    {
        return true;
    }
    return false;
}

void List::IteratorForList::goToNext() {
    this->current = this->current->nextElement;   //������� �� ���� �������
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


List::IteratorForList *List::begin() {    //��������� �� ������ ������
    if (this->empty())
        return NULL; //���� ��������� ���� ������ �� ������� 0

    return new IteratorForList(this->FirstElement);
}

List::IteratorForList *List::end() {             //������
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

List::IteratorForList *List::newIterator() {    //�� ������� ��� ����
    if(this->FirstElement!=NULL)
    {
        IteratorForList *iterator = new IteratorForList();
    }
    return 0;
}

int List::push_front(void *elem, size_t elemSize) {       //�������� � ������
    ListElement *el = new ListElement(elem, elemSize);    //������ ����� �������
    el->nextElement = this->FirstElement;     //��� ��������� ������ ������ ������
    this->FirstElement = el;       //������ ������ ����� �������
    this->ListSize++;    //���������� ��������� �����������
    return 0;
}

void List::pop_front() {
    ListElement *el;
    if(this->FirstElement->nextElement)
    {
        el = this->FirstElement; //������������ ������� ������
        this->FirstElement=this->FirstElement->nextElement; //�������� ���������� �� 1 ������
        delete (el);   //������� �������
        this->ListSize--;  //��������� ���-�� ��������� � ������
    }

}

void *List::front(size_t &size) {
    size = this->FirstElement->ElementSize;  //������� ������� �������
    return this->FirstElement->Znacheniye;  //������� ��������
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
    while(iterator->current->nextElement != iter->current)  //���� �������� � ���� �������� ���� ��������� �������� ������
    {
        iterator->goToNext();
    }
    el = new ListElement(elem, elemSize);
    iterator->current->nextElement=el;  //������ ��������� ����� �������
    el->nextElement = iter->current;   //� ����� �������� ������ ������ ���������
    //�� �������� ����� �������
    this->ListSize++;
    return 0;
}

int List::size() {
    return static_cast<int>(this->ListSize);   //�������������� ���� � ��� ������ ��� �������� ���� �����
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










