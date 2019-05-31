cmake_minimum_required(VERSION 3.12)
PROJECT(DEEZIA)

SET(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(
        DEEZIA Mem.h MemoryManager.h
        main.cpp
        Set.cpp Set.h
        RBTree.h RBTree.cpp
        Container.h GroupContainer.h
        ContainerTest.h ContainerTest.cpp
        Exceptions.cpp Exceptions.h
)
