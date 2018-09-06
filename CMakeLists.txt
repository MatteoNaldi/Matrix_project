cmake_minimum_required(VERSION 3.10)
project(Matrix_project)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(test)

set(SOURCE_FILES Matrix.h MatrixIntFactory.cpp MatrixIntFactory.h MatrixDoubleFactory.cpp MatrixDoubleFactory.h)
add_executable(Matrix_project main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(Matrix_project core)