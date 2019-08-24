cmake_minimum_required(VERSION 3.2)
project(SCMLib_tests)

include_directories(${SCMLIB_HEADERS_DIR} ${PROJECT_SOURCE_DIR}/test/)

set(SOURCE_FILES TestMain.cpp)

add_executable(SCMLib_tests ${SOURCE_FILES})

set_target_properties (SCMLib_tests PROPERTIES LINK_FLAGS "-Wall")

target_link_libraries(SCMLib_tests SCMLib_lib)
