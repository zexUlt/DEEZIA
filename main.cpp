//
// Created by zexult on 03.04.19.
//

#include "Set.h"
#include "Mem.h"

int main()
{
    Mem mem(1000);
    Set s(mem);


    size_t size = 0;
    int a = 10;
    int c = 10;

    cout << s.insert(&a, sizeof(a)) << endl;
    cout << s.insert(&c, sizeof(c)) << endl;

    Container::Iterator* it = s.find(&a, sizeof(a));

    cout << *(int*)it->getElement(size) << " " << size << endl;

    cout << s.size() << endl;

    s.remove(it);

    cout << s.size() << endl;

    return 0;
}