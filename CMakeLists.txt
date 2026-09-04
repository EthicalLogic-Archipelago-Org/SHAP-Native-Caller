
cmake_minimum_required(VERSION 4.3)
project(SHAPNativeCaller)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(SHAPNativeCaller SHARED SHAPNativeCaller.cpp)
