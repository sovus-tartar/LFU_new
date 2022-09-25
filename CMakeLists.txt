cmake_minimum_required(VERSION 3.0.0)
project(lfu VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(lfu ./source/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
