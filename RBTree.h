//
// Created by zexult on 27.03.19.
//

#pragma once

#include <bits/stdc++.h>
#include "MemoryManager.h"
#include "Tree.h"

enum color{RED, BLACK, WHITE}; // WHITE is temporary color

struct Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    bool color;
    void* value;

    explicit  Node(void*);
};

class RBTree {
public:
    class SetIterator : public Iterator {
    private:
        RBTree *tree;

        Node* searchNextUpwards(Node*);
        Node* searchNextDownwards(Node*);
    public:
        Node *current;
        explicit SetIterator(RBTree*);
       // explicit SetIterator(Node*, RBTree*);
        void setCurrent(Node*);
        void* getElement (size_t&);// final;
        void goToNext();// final;
        bool hasNext();// final;
        bool equals(SetIterator*);
    };
private:
    int _size;
    Node* root;
    Node* _begin;
    SetIterator* _end;
protected:
    void rotateLeft(Node*& _pivot);
    void rotateRight(Node*& _pivot);
    void recolorAfterInsert(Node*& _root);
    void recolorAfterDelete(Node*& _root);
    bool getColor(Node*&  _node);
    void setColor(Node*& _node, bool _color);
    int getBlackHeight(Node*& _root); // For merge of two trees
    Node* binSearchInsert(Node*& _root, Node*& _node);
    Node* binSearchDelete(Node*& _root, void* _value);
public:
    RBtree(){_size = 0; root = _begin = nullptr; _end = nullptr;};
    explicit RBTree(MemoryManager& mem){root = _begin = nullptr; _end = nullptr; _size = 0;}

    /** GETTERS **/
    Node* getBegin();
    SetIterator* getEnd();
    Node*& getRoot();
    int getSize();
    /** GETTERS **/

    int insertVal(void*, size_t);
    void deleteVal(void*);
    bool find(void*);
    Node* minimalNode(Node*& _root);
    Node* maximalNode(Node*& _root);
};

