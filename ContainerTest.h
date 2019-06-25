//
// Created by zexult on 30.04.19.
//

#ifndef DEEZIA_CONTAINERTEST_H
#define DEEZIA_CONTAINERTEST_H

#include "GroupContainer.h"
#include "Set.h"
#include <ctime>

/** TODO LIST
 * Create automatic tests.
 *
 */


enum ops{CT_NORMAL, CT_EQUAL, CT_STRINT, CT_CHRINT};

class ContainerTest {
private:
    Set *cont;
    //List list;
public:
    struct data{
        void* elem;
        char name[20];

        data() = default;
        explicit data(void* _data, string _name, size_t size) {elem = malloc(size); memmove(elem, _data, size); strcpy(this->name,_name.c_str());}
    };

    char* rand_string(size_t);

//public:
    explicit ContainerTest(Set *);

//    int AutoInsert(size_t num_elem, int flag);
//    int AutoRemoveTest();
    double testClear(); // is working
    double testInsert(size_t num_elem, int flag); // is working
    double testRemove(size_t num_elem); // need fix
    void printContainer(); // is working
};


#endif //DEEZIA_CONTAINERTEST_H
