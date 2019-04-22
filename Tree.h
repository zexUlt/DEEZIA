//
// Created by zexult on 18.04.19.
//

#pragma once

#include "TreeAbstract.h"

class Tree : public AbstractTree {
public:
    explicit Tree(MemoryManager& mem): AbstractTree(mem){};
};

