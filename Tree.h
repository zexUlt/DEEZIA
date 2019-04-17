//
// Created by zexult on 27.03.19.
//

#ifndef DEEZIA_TREE_H
#define DEEZIA_TREE_H

#include <bits/stdc++.h>

enum color{RED, BLACK, WHITE, VIOLET}; // WHITE is temporary color, VIOLET is color for end

struct Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    bool color;
    int value;

    explicit  Node(int);
};

class RBTree {
private:
    Node *root;
protected:
    void rotateLeft(Node *& _pivot);
    void rotateRight(Node *& _pivot);
    void recolorAfIns(Node *& _root);
    void recolorAfDel(Node *& _root);
    bool getColor(Node *& _node);
    void setColor(Node *& _node,bool _color);
    int getBlackHeight(Node *& _root);
    Node* binSearchInsert(Node *& _root, Node *& _node);
    Node* binSearchDelete(Node *& _root, int _value);

public:
    RBTree();
    Node*& getRoot();
    void insertVal(int);
    void deleteVal(int);
    bool find(int);
    Node* minimalNode(Node *& _root);
    Node* maximalNode(Node *& _root);
    //void merge(RBTree);

    class SetIterator {
    private:
        RBTree *tree;
        Node *current;
        Node *_end = {
                this->_end->color = VIOLET,
                this->_end->parent = tree->maximalNode(tree->root),
                this->_end->left = this->_end->right = nullptr,
                this->_end->value = 0; }

        Node* searchNextUpwards(Node*);
        Node* searchNextDownwards(Node*);
    public:
        explicit SetIterator(Node*);
        void setCurrent(Node*);
        Node* getEnd();
        int getElement(size_t&);
        void goToNext();
        bool hasNext();
        bool equals(SetIterator*);
    };
};


#endif //DEEZIA_TREE_H
