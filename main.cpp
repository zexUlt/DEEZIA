//
// Created by zexult on 03.04.19.
//

#include "Set.h"
#include "Mem.h"
#include "ContainerTest.h"

int main()
{
    Mem mem(1000);
    Set s(mem);

    size_t i,_size(5);
    auto* ct = new ContainerTest(&s);

    printf("%e\n",ct->testInsert(_size));


    Container::Iterator* it = s.newIterator();

    clock_t start = clock();

    s.clear();

    clock_t finish = clock();

    cout << (double)(finish - start) / CLOCKS_PER_SEC << endl;

    return 0;
}