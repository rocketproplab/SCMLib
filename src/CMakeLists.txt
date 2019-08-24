cmake_minimum_required(VERSION 3.2)
project(SCMLib)

file(GLOB SOURCE_FILES *.c *.cpp)

add_library(SCMLib_lib STATIC ${SOURCE_FILES})
