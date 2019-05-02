#pragma once
#include <string.h>
#include <stdlib.h>
#include "ListAbstract.h"
#include "MemoryManager.h"
#include "Container.h"

class List : public AbstractList{
protected:   //��, ��� ����������� �����������
    class ListElement {
    public:   
        void* Znacheniye;  //���������� ��������� �� �������� ��������, ��� ����� ��� ����� ���, ������� ����
        ListElement* nextElement; //��������� �� ��������� ������� � ������
        size_t ElementSize;       //size_t ��� int ������ ������������� ����� (��� ��� ��������� ��� ���������)
        //3 �������� ������������ ��� �������� ������ � ����������
        ListElement();

        ListElement(ListElement &element);

        ListElement(void *Znacheniye, size_t size);

        ~ListElement();
    };

    size_t ListSize; //����������� ��� ������� ������   ������
    ListElement *FirstElement;  //��������� �� ������ ������� ������  ������
public:
    //�����������\����������
    List(MemoryManager &mem);

    ~List();

    //������ ����� ��� ���������
class IteratorForList : public Container::Iterator{
    public:
        ListElement *current;    //��������� �� ������� ��������

        IteratorForList();

        IteratorForList(ListElement *element);

        IteratorForList(IteratorForList &iterator);

        ~IteratorForList();

        bool hasNext();  //������� ��� �������� ������������� ���������� ������

        void goToNext();//������� �������� �� ��������� ��������

        void *getElement(size_t &my_size_element);//�������� ������ ������ ������

        bool equals(Iterator *right);  // �������� �� ��������� ����������


    };


        //������ �����
        // ���������� �������� � ������ ����������.
        // � ������ ��������� ���������� ������� ���������� �������� 0, � ������ ������� 1.
        int push_front(void *elem, size_t elemSize) override;

        // �������� �������� �� ������ ����������.
        void pop_front();

        // ������� ���� ���������� ��������� �� �������, ����������� � ������ ����������.
        // � �� ���� ���������� ������ ������
        void* front(size_t &size);

        // ���������� �������� � �������, �� ������� ��������� �������� iter.
        // � ������ ��������� ���������� ������� ���������� �������� 0, � ������ ������� 1.
        int insert(IteratorForList *iter, void *elem, size_t elemSize);



        //������ ����������

    // ������� ���������� ��������, ������ ���������� ��������� � ����������.
     int size();

    // ������� ���������� ��������, ������ ������������ ����������� ���������� � ������.
     size_t max_bytes();

    // ������� ���������� ��������� �� ��������, ����������� �� ������ ���������
    // � ���������� �������. ���� ������� �� ������, ������������ ������ ���������.
    IteratorForList* find(void *elem, size_t size);

    // �������� ���������, ���������������� ������� ���� ����������.
    IteratorForList* newIterator();

    // ������� ���������� ��������� �� ��������, ����������� �� ������ �������
    // ����������. ���� ��������� ������, ������������ ������� ���������.
    IteratorForList* begin();

    // ������� ���������� ��������� �� ��������, ����������� ������� �� ���������
    // ��������� ����������. ���� ��������� ������, ������������ ������� ���������.
    IteratorForList* end();

    // �������� �������� �� �������, �� ������� ��������� �������� iter.
    // ����� �������� �������� ��������� �� ��������� �� ��������� �������.
     void remove(Iterator *iter);

    // �������� ���� ��������� �� ����������.
     void clear();

    // ���� ��������� ���� ���������� true, ����� false
     bool empty() = 0;

};

