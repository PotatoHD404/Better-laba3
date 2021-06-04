cmake_minimum_required(VERSION 3.20)
project(Lab3_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3_master
        BinarySearchTree.h
        main.cpp
        MainWindow.cpp
        MainWindow.h
        Set.h
        Test.h
        TestWindow.cpp
        TestWindow.h)
