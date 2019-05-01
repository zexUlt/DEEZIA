//
// Created by zexult on 27.03.19.
//

#pragma once

#include <bits/stdc++.h>
#include "Container.h"
#include "MemoryManager.h"

enum color{RED, BLACK, WHITE}; // WHITE is temporary color

struct Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    bool color;
    void* value;
    size_t __size;

    Node(void*,size_t);
};

class RBTree {
    friend class Set; // Check out
public:
class SetIterator : public Container::Iterator {
    friend class Set;
    private:
        RBTree *tree;
        Node *current;

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
    int _size = 0;
    Node* root = nullptr;
    Node* _begin = nullptr;
    SetIterator* _end = nullptr;
protected:
    void rotateLeft(Node*& _pivot);
    void rotateRight(Node*& _pivot);
    void recolorAfterInsert(Node*& _root);
    void recolorAfterDelete(Node*& _root);
    bool getColor(Node*&  _node);
    void setColor(Node*& _node, bool _color);
    //int getBlackHeight(Node*& _root);  For merge of two trees
    Node* binSearchInsert(Node*& _root, Node*& _node);
    Node* binSearchDelete(Node*& _root, void* _value, size_t size);

    RBTree() = default;
    explicit RBTree(MemoryManager& mem){root = _begin = nullptr; _end = nullptr; _size = 0;}

    int insertVal(void*, size_t);
    void deleteVal(void*, size_t);
    bool find(void*, size_t);
    bool find(void*,size_t,Node**);
    Node* minimalNode(Node*& _root);
    Node* maximalNode(Node*& _root);
};

