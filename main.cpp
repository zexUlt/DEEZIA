//
// Created by zexult on 03.04.19.
//

#include "Set.h"
#include "Mem.h"
#include <exception>

int main()
{
    Mem mem(1000);
    Set s(mem);

    int a = 10;
    char c = 5;

    cout << s.insert(&a, sizeof(a)) << endl;
    cout << s.insert(&c, sizeof(c)) << endl;

    return 0;
}