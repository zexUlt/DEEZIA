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

    size_t _size(10);
    auto* ct = new ContainerTest(&s);

    printf("%e\n",ct->testInsert(_size, CT_NORMAL));

    cout << s.size() << endl;

    ct->printContainer();

    printf("%e\n",ct->testClear());

    return 0;
}