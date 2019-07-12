#include "List2.h"

bool list2test(List2 l2, int size)
{
    for(int i = 0; i < size; i++)
        l2.push_back(&i, sizeof(int));
    size_t sz;

    int i = 1;
    for(auto it = l2.begin(); !it->equals(l2.end()); it->goToNext())
    {
        l2.remove(it);
        it->goToNext();
    }

    for(auto it = l2.begin(); !it->equals(l2.end()); it->goToNext())
    {

//        cout << *(int *) it->getElement(sz) << " ";
        if (*(int *) it->getElement(sz) != i)
            return 0;
        i = i + 2;
    }
    cout << endl;

    return 1;
}