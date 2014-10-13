cmake_minimum_required(VERSION 2.8.7)

include_directories(.)
add_executable(test main.cpp cppnamespace.h)
enable_testing()
add_test(namespace.test COMMAND test)
