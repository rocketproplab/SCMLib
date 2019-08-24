cmake_minimum_required(VERSION 3.2)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(SCMLIB_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SCMLIB_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SCMLIB_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(SCMLIB_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${SCMLIB_INSTALL_INCLUDE_DIR})
include_directories(${SCMLIB_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test (NAME all COMMAND SCMLib_tests)
