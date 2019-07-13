//
// Created by zexult on 03.04.19.
//

#include "ContainerTest.h"
#include "Set.h"
#include "Mem.h"
//#include "ContainerTest.h"

int main() {
    Mem mem(1000);
    List l(mem);
    Set s(mem);

    size_t _size(10);

    ContainerTest ct(&s,l);

    try{
        ct.AutoInsert(_size, CT_NORMAL);
//        ct.printContainer();
        ct.AutoRemoveTest(_size);
    }catch(Exceptions &e){
        e.what();
}
    return 0;
}