cmake_minimum_required(VERSION 3.31)
project(KDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(KDB main.cpp
        SkipList/SkipList.cpp
        SkipList/SkipList.h)
