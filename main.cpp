//
// Created by zexult on 03.04.19.
//

#include "Set.h"
#include "Mem.h"
#include "List.h"
#include "ContainerTest.h"

int main() {
    Mem mem(1000);
    List l(mem);

    int a = 1;
    size_t _size(10), sz;

    for (int i = 0; i < _size; i++)
        l.push_front(&i, sizeof(i));

    for(auto it = l.begin(); !it->equals(l.end()); it->goToNext())
        cout << *(int*) it->getElement(sz) << " "; // segfault
    cout << endl;

    auto it = l.begin();
    while( !it->equals(l.end()))
    {
        it = l.begin();
        l.remove(it);
    }

    for(auto it = l.begin(); !it->equals(l.end()); it->goToNext())
        cout << *(int*)it->getElement(sz) << " ";
    cout << endl;

    return 0;
}