cmake_minimum_required(VERSION 3.20)

project(
    StlContainersLib
    DESCRIPTION "C++ 2024"
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)