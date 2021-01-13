cmake_minimum_required(VERSION 3.17)
project(MyVector)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyVector
        data/three/code.cpp
        exceptions.hpp
        utility.hpp
        vector.hpp)