//
// Created by yuszafar on 11.07.2019.
//

#include "Queue.h"

int Queue::push(void *elem, size_t size) {

    return l2.push_back(elem, size);
}

int Queue::pop() {
    if(l2.size() == 0)
        return 0;
    l2.pop_front();
    return 1;
}

void *Queue::front(size_t &size) {
    return l2.head->data;
}

void *Queue::back(size_t &size) {
    return l2._end->data;
}

int Queue::insert(Container::Iterator *iter, void *elem, size_t size) {
    return l2.insert(iter, elem, size);

}

int Queue::size() {
    return l2._size;
}

size_t Queue::max_bytes() {
    l2.max_bytes();
}

List2::List2Iterator *Queue::find(void *elem, size_t size) {
    return l2.find(elem, size);
}

List2::List2Iterator *Queue::newIterator() {
    return l2.newIterator();
}

List2::List2Iterator *Queue::begin() {
    return l2.begin();
}

List2::List2Iterator *Queue::end() {
    return l2.end();
}

void Queue::remove(Container::Iterator *iter) {
    l2.remove(iter);
}

void Queue::clear() {
    l2.clear();

}

bool Queue::empty() {
    return l2.empty();
}


