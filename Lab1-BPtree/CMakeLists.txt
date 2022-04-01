cmake_minimum_required(VERSION 3.10)
project(BplusTree)

set(CMAKE_CXX_STANDARD)

add_executable(
    main.cpp
    BplusTree.cpp
    BplusTree.h
)
