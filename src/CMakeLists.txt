cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp SwipeDirection.h SwipeEncoding.h CCondition.cpp CCondition.h CPuzzle.cpp CPuzzle.h CPuzzleSolver.cpp CPuzzleSolver.h)