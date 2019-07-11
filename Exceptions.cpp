//
// Created by zexult on 02.05.19.
//

#include "Exceptions.h"

void Exceptions::what()
{
    cout << msg << endl;
}

Exceptions Exceptions::NULL_NODE_CALL(Container::Iterator* it)
{
    auto ptr = (int*)it;
    string msg = "Oops! Something gone wrong.\nTrying to use RBTRee::SetIterator::getElement on iterator with null current node at address: .";
    auto *ex = new Exceptions(msg.c_str());
    return *ex;
}

Exceptions Exceptions::END_ITERATOR_REMOVING(Container::Iterator* it)
{
    auto ptr = (int*)it;
    string msg = "Oops! Something gone wrong.\nTrying to remove end() iterator at address: .";
    auto *ex = new Exceptions(msg.c_str());
    return *ex;
}