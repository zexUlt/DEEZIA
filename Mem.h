#pragma once
#include "MemoryManager.h"

// Простейший менеджер памяти, использует ::new и ::delete
// Менеджер памяти еще проще, чем предложенный П.А. Алисейчиком использует malloc и free
class Mem: public MemoryManager
{
public:
    explicit Mem(size_t sz): MemoryManager(sz) {}

    void* allocMem(size_t sz) final
    {
        void* ptr = (void*)malloc(sz);
        return ptr;
    }

    void freeMem(void* ptr) final
    {
        free(ptr);
    }
};
