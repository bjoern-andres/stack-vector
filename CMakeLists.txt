cmake_minimum_required(VERSION 2.6)
project(stack-vector)
include_directories(include include/andres)
file(GLOB headers include/andres/*.hxx)

add_executable(test-stack-vector src/unittest/stack-vector.cxx ${headers})
add_test(test-stack-vector test-stack-vector)
