//
// Created by zexult on 27.03.19.
//

#include "Mem.h"
#include "RBTree.h"

/** Node implementation **/
Node::Node(void* data)
{
    Mem m;
    this->value = m.allocMem(data);
    color = RED;
    left = right = parent = nullptr;
}

/**                     **/

/** START Protected methods of RBTree **/

bool RBTree::getColor(Node *&node)
{
    if(node == nullptr)
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node *&node, bool color)
{
    if(node == nullptr)
        return;

    node->color = color;
}

Node* RBTree::binSearchInsert(Node *& root, Node *&ptr)
{
    if(root == nullptr)
        return ptr;

    if(memcmp(ptr->value,root->value, sizeof(root->value)) < 0) {
        root->left = binSearchInsert(root->left, ptr);
        root->left->parent = root;
    } else {
        root->right = binSearchInsert(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::rotateRight(Node *&node)
{
    Node *pivot = node->right;
    node->left = pivot->left;

    if(node->left != nullptr)
        node->left->parent = node;

    pivot->parent = node->parent;

    if(node->parent == nullptr)
        root = pivot;
    else if(node == node->parent->right)
        node->parent->right = pivot;
    else
        node->parent->left = pivot;

    pivot->right = node;
    node->parent = pivot;
}

void RBTree::rotateLeft(Node *&node) {
    Node *pivot = node->right;
    node->right = pivot->left;

    if(node->right != nullptr)
        node->right->parent = node;

    pivot->parent = node->right->parent;

    if(node->parent == nullptr)
        root = pivot;
    else if(node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;

    pivot->left = node;
    node->parent = pivot;
}

void RBTree::recolorAfterInsert(Node *&node)
{
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    for(;node != root && getColor(node) == RED && getColor(node->parent) == RED;) {
        parent = node->parent;
        grandparent = parent->parent;
        if(parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if(getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            }
        } else {
            if(node == parent->left) {
                rotateLeft(parent);
                node = parent;
                parent = node->parent;
            }
            rotateRight(grandparent);
            std::swap(parent->color, grandparent->color);
            node = parent;
        }
    }
    setColor(root, BLACK);
}

void RBTree::recolorAfterDelete(Node *&node)
{
    if(node == nullptr)
        return;
    if(node == root){
        root = nullptr;
        return;
    }

    if(getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED){
        Node *child = node->left != nullptr ? node->left : node->right;

        if(node->parent->left == node){
            node->parent->left = child;
            if(child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete(node);
        } else {
            node->parent->right = child;
            if(child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete(node);
        }
    } else {
        Node *brother = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, WHITE);
        for(;ptr != root && getColor(ptr) == WHITE;) {
            parent = ptr->parent;
            if(ptr == parent->left) {
                brother = parent->right;
                if (getColor(brother) == RED) {
                    setColor(brother, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
                        setColor(brother, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else setColor(parent, WHITE);
                        ptr = parent;
                    } else {
                        if (getColor(brother->right) == BLACK) {
                            setColor(brother->left, BLACK);
                            setColor(brother, RED);
                            rotateRight(brother);
                            brother = parent->right;
                        }
                        setColor(brother, parent->color);
                        setColor(parent, BLACK);
                        setColor(brother->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                brother = parent->left;
                if(getColor(brother) == RED) {
                    setColor(brother, RED);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if(getColor(brother->left) == BLACK && getColor(brother->right) == BLACK) {
                        setColor(brother, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else setColor(parent, WHITE);
                        ptr = parent;
                    } else {
                        if(getColor(brother->left) == BLACK) {
                            setColor(brother->right, BLACK);
                            setColor(brother, RED);
                            rotateLeft(brother);
                            brother = parent->left;
                        }
                        setColor(brother, parent->color);
                        setColor(parent, BLACK);
                        setColor(brother->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if(node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

Node* RBTree::binSearchDelete(Node *& root, void* val)
{
    if(root == nullptr)
        return root;

    if(memcmp(val,root->value, sizeof(root->value)) < 0)
        return binSearchDelete(root->left, val);

    if(memcmp(val,root->value, sizeof(root->value)) > 0)
        return binSearchDelete(root->right, val);

    if(root->right == nullptr || root->left == nullptr)
        return root;

    Node *tmp = minimalNode(root->right);
    root->value = tmp->value;
    return binSearchDelete(root->right, val);
}


int RBTree::getBlackHeight(Node *&node)
{
    int blackheight = 0;
    for(;node != nullptr;) {
        if(getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

/**  END OF PROTECTED METHODS   **/


/** START GETTERS **/

int RBTree::getSize()
{
    return this->_size;
}

Node*& RBTree::getRoot()
{
    return this->root;
}

RBTree::SetIterator* RBTree::getEnd()
{
    return _end;
}

Node* RBTree::getBegin()
{
    return this->_begin;
}

/** END GETTERS **/

/** START PUBLIC METHODS **/

Node* RBTree::maximalNode(Node *&node)
{
    Node* ptr = node;

    for(;ptr->right != nullptr;) {
        ptr = ptr->right;
    }

    return ptr;
}

Node* RBTree::minimalNode(Node *&node)
{
    Node* ptr = node;

    for(;ptr->left != nullptr;) {
        ptr = ptr->left;
    }

    return ptr;
}

bool RBTree::find(void* val)
{
    Node *pivot = this->root;
    bool found = false;
    for(;!found;)
    {
        if(pivot->value == val)
            found = true;
        else if(pivot->value < val){
            pivot = pivot->right;
        } else
            pivot = pivot->left;
    }

    return found;
}

int RBTree::insertVal(void* data, size_t _size)
{
    Node *node = new Node(data);
    root = binSearchInsert(root, node);
    recolorAfterInsert(node);
    _begin = minimalNode(this->root);
    _size++;

    return 0;
}

void RBTree::deleteVal(void* val)
{
    Node *node = binSearchDelete(root, val);
    recolorAfterDelete(node);
    _size--;
}

/** END PUBLIC METHODS **/

/** Iterator implementation **/

RBTree::SetIterator::SetIterator(RBTree* tr)
{
    this->tree = tr;
    this->current = tr->_begin;
}


Node* RBTree::SetIterator::searchNextUpwards(Node* cur)
{
    if(cur == nullptr)
        return nullptr;

    if(cur->parent != nullptr && cur == cur->parent->left)
        return cur->parent;
    else searchNextUpwards(cur->parent);
}

Node* RBTree::SetIterator::searchNextDownwards(Node *cur) 
{
    if(cur == nullptr)
        return nullptr;
    
    if(cur->parent != nullptr && cur->right == nullptr)
        return cur;
    else searchNextDownwards(cur->right);
}

void RBTree::SetIterator::goToNext()
{
    if(this->current == tree->maximalNode(tree->root))
        this->current = this->tree->_end->current;

    if(this->current == this->current->parent->left) // If current node is located at the left subtree
        this->current = this->current->parent;

    if(this->current == this->current->parent->right && searchNextUpwards(this->current) != nullptr && this->current->right == nullptr)
        this->current = searchNextUpwards(this->current); // If current node is located at the right subtree of the left subtree from root
    else if(this->current == this->current->parent->right && searchNextUpwards(this->current) != nullptr && this->current->right != nullptr)
            this->current = this->current->right;
    else this->current = searchNextDownwards(this->current); // If current node is located at the right subtree of the right subtree from root or at root itself

}

bool RBTree::SetIterator::hasNext()
{
    return ( (this->current != this->tree->_end->current) && (searchNextUpwards(this->current) != nullptr) ) || (this->current == this->current->parent->right);
    //     If current node is not in the end of the tree AND   if node is in the left subtree from root      OR  node is in the right branch of any subtree
}

void* RBTree::SetIterator::getElement(size_t& size)
{
    //size_t *ptr = size;
    size = sizeof(this->current->value);

    return this->current->value;
}

bool RBTree::SetIterator::equals(RBTree::SetIterator *right)
{
    return (this->current == right->current) && (this->tree->_end == right->tree->_end) && (this->tree->_begin == right->tree->_begin);
}

void RBTree::SetIterator::setCurrent(Node *node)
{
    this->current = node;
}
/** END ITERATOR IMPLEMENTATION **/
