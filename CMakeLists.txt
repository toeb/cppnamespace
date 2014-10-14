cmake_minimum_required(VERSION 2.8.7)

project(cppnamespace)
file(GLOB_RECURSE files includes/**.h)

include_directories(includes)
add_executable(cppnamespace.test main.cpp ${files})
enable_testing()
add_test(cppnamespace.test COMMAND cppnamespace.test)
