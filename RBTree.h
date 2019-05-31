//
// Created by zexult on 27.03.19.
//

#pragma once

#include <bits/stdc++.h>
#include "Exceptions.h"
#include "Container.h"
#include "MemoryManager.h"

enum color{RED, BLACK, DOUBLE_BLACK}; // WHITE is temporary color

struct Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    color _color;
    void* value;
    int real_value;
    size_t __size;

    Node(void*,size_t);
};

class RBTree {
    friend class Set; // Check out
public:
class SetIterator : public Container::Iterator {
    friend class Set;
    friend class RBTree;
    private:
        Exceptions* e;
        RBTree *tree;
        Node *current;
        bool isEnd;

        Node* searchMaxInLeft(Node*);
        Node* searchNextUpwards(Node*);
        Node* searchNextDownwards(Node*); // finds minimum in the subtree
    public:
        explicit SetIterator(RBTree*);
        explicit SetIterator(RBTree*, Node*);
        void* getElement (size_t&) final;
        void goToNext() final;
        bool hasNext() final;
        bool equals(Container::Iterator*) final;
    };
private:
    int _size;
    Node* root;
    Node* _begin;
    SetIterator* _end;

    void DFSfullRemove(Node*);
protected:
    void rotateLeft(Node*& _pivot);
    void rotateRight(Node*& _pivot);
    void recolorAfterInsert(Node*& _root);
    void recolorAfterDelete(Node*& _root);
    color getColor(Node*&  _node);
    void setColor(Node*& _node, color _color);
    Node* binSearchInsert(Node*& _root, Node*& _node);
public:
    RBTree() = default;
    explicit RBTree(MemoryManager& mem){root = _begin = nullptr; _end = new SetIterator(this,nullptr); _end->isEnd = true; _size = 0;}

    int insertVal(void*, size_t);
    void deleteVal(Node*);
    bool find(void*, size_t);
    bool find(void*,size_t,Node**);
    Node* minimalNode(Node*& _root);
    Node* maximalNode(Node*& _root);
};

