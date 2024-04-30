cmake_minimum_required(VERSION 3.28)
project(mhkc_encrypt)

set(CMAKE_CXX_STANDARD 20)

add_executable(mhkc_encrypt main.cpp
        encryptor.h)
