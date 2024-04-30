cmake_minimum_required(VERSION 3.28)
project(mhkc_key)

set(CMAKE_CXX_STANDARD 20)

add_executable(mhkc_key main.cpp
        key_generator.h)
