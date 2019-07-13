//
// Created by zexult on 27.03.19.
//

#include "RBTree.h"
#include "Set.h"
#include "ContainerTest.h"

/** TODO List:
 * Fix recolorAfterDelete.
 */

/** Node implementation **/

MemoryManager* Set::_memory = nullptr;

Node::Node(void* data, size_t size)
{
    value = malloc(size);

    __size = size;
    memmove(value, data, size);
    _color = RED;
    left = right = parent = nullptr;
}

void* Node::operator new(size_t size)
{
    return Set::_memory->allocMem(size);
}

void Node::operator delete(void* ptr)
{
    Set::_memory->freeMem(ptr);
}

/**                     **/

/** START Protected methods of RBTree **/

color RBTree::getColor(Node *&node)
{
    if(node == nullptr)
        return BLACK;

    return node->_color;
}

void RBTree::setColor(Node *&node, color __color)
{
    if(node == nullptr)
        return;

    node->_color = __color;
}

Node* RBTree::binSearchInsert(Node *& root, Node *&ptr)
{
    if(root == nullptr)
        return ptr;

    if( (ptr->__size == root->__size && memcmp(ptr->value,root->value, ptr->__size) < 0 ) || ptr->__size < root->__size) {
        root->left = binSearchInsert(root->left, ptr);
        root->left->parent = root;
    } else {
        root->right = binSearchInsert(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::rotateLeft(Node *&node) {
    Node *pivot = node->right;
    node->right = pivot->left;

    if (node->right != nullptr)
        node->right->parent = node;

    pivot->parent = node->parent;

    if (node->parent == nullptr)
        root = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;

    pivot->left = node;
    node->parent = pivot;
}

void RBTree::rotateRight(Node *&node) {
    Node *pivot = node->left;
    node->left = pivot->right;

    if (node->left != nullptr)
        node->left->parent = node;

    pivot->parent = node->parent;

    if (node->parent == nullptr)
        root = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;

    pivot->right = node;
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
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->_color, grandparent->_color);
                node = parent;
            }
        } else {
                Node *uncle = grandparent->left;
                if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                swap(parent->_color, grandparent->_color);
                node = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::recolorAfterDelete(Node *&node)
{
    if (node == nullptr)
        return;

    if(node == this->root)
    {
        this->root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            free(node->value);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            free(node->value);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != this->root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->_color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->_color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        free(node->value);
        delete(node);
        setColor(this->root, BLACK);
    }
}

void RBTree::DFSfullRemove(Node *node)
{
    if(node->right != nullptr)
        DFSfullRemove(node->right);
    if(node->left != nullptr)
        DFSfullRemove(node->left);
    free(node->value);
    delete(node);
    this->_size--;
}
/**  END OF PROTECTED METHODS   **/

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

bool RBTree::find(void* val, size_t size)
{
    Node *pivot = this->root;
    bool found = false;


    for(;!found;)
    {
        if(pivot == nullptr)
            break;

        if(size == pivot->__size && memcmp(pivot->value, val, size) == 0)
            found = true;
        else if(pivot->__size < size || (pivot->__size == size && memcmp(pivot->value, val, size) < 0)) {
            pivot = pivot->right;
        } else
            pivot = pivot->left;
    }

    return found;
}

bool RBTree::find(void* val, size_t size, Node** node)
{
    Node *pivot = this->root;
    bool found = false;
    while(!found)
    {
        if( pivot == nullptr || (size == pivot->__size && memcmp(pivot->value, val, size) == 0) ){
            found = true;
            *node = pivot;
        } else if( pivot->__size < size || (pivot->__size == size && memcmp(pivot->value, val, size) < 0) ) {
            pivot = pivot->right;
        } else
            pivot = pivot->left;
    }

    return found;
}

int RBTree::insertVal(void* val, size_t __size)
{
    Node *node = new Node(val, __size);
    root = binSearchInsert(root, node);
    recolorAfterInsert(node);
    _size++;

    return 0;
}

void RBTree::deleteVal(Node* node)
{
    if(node == this->root && this->root->right == nullptr && this->root->left == nullptr)
    {
        free(node->value);
        delete(node);
        this->root = nullptr;
    } else if(node == this->root && this->root->right == nullptr && this->root->left != nullptr)
    {
        Node* tmp = _end->searchMaxInLeft(this->root->left);
        memcpy(this->root->value, tmp->value, this->root->__size < tmp->__size ? tmp->__size : root->__size);
        recolorAfterDelete(tmp);
    } else if(node == this->root && this->root->right != nullptr)
    {
        Node* tmp = _end->searchNextDownwards(this->root->right);
        memcpy(this->root->value, tmp->value, this->root->__size < tmp->__size ? tmp->__size : root->__size);
        recolorAfterDelete(tmp);
    } else recolorAfterDelete(node);
    _size--;
}

/** END PUBLIC METHODS **/

/** Iterator implementation **/

RBTree::SetIterator::SetIterator(RBTree* tr)
{
    Exceptions ex("Something gone wrong.");
    tree = tr;
    current = tr->_begin;
    this->e = &ex;
    isEnd = false;
}

RBTree::SetIterator::SetIterator(RBTree *tr, Node* node)
{
    Exceptions ex("Something gone wrong.");
    tree = tr;
    current = node;
    this->e = &ex;
    isEnd = false;
}


Node* RBTree::SetIterator::searchMaxInLeft(Node* cur)
{
    if(cur == nullptr)
        return nullptr;

    if(cur->right == nullptr)
        return cur;
    else searchMaxInLeft(cur->right);
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

    if(cur->left == nullptr)
        return cur;
    else searchNextDownwards(cur->left);
}

void RBTree::SetIterator::goToNext()
{

    Node* max = tree->maximalNode(tree->root);
    if(memcmp(this->current->value, max->value, this->current->__size) == 0)
    {
        this->current = nullptr;
        this->isEnd = true;
        tree->_end = this;
        return;
    }

    if(this->current->right != nullptr)
        this->current = searchNextDownwards(this->current->right);
    else this->current = searchNextUpwards(this->current);
}

bool RBTree::SetIterator::hasNext()
{
    return ( (!this->isEnd) && (searchNextUpwards(this->current) != nullptr) ) || (this->current == this->current->parent->right);
    //     If current node is not in the end of the tree AND   if node is in the left subtree from root      OR  node is in the right branch of any subtree
}

void* RBTree::SetIterator::getElement(size_t& size)
{
    if(this->current == nullptr)
        throw this->e->NULL_NODE_CALL(this);

    size = this->current->__size;
    return this->current->value;
}

bool RBTree::SetIterator::equals(Container::Iterator *right)
{
    auto right_it = (RBTree::SetIterator*) right;
    bool ret = (this->current == right_it->current) && (this->tree == right_it->tree) && (this->isEnd == right_it->isEnd);;
    return ret;
}

/** END ITERATOR IMPLEMENTATION **/
